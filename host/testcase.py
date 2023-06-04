
import os
import re
import gzip
import json
import struct
import sqlite3
import os.path
import traceback


TESTDB = "tests/testdb/68000/"
TESTSUITE = "tests/ProcessorTests/680x0/68000/v1/"

class TestFile:
    COLUMNS = ["name", "number", "opcode", "instruction", "is_valid", "has_run", "result", "initial_state", "expected_state", "actual_state"]

    def __init__(self, name, testdb=TESTDB, testsuite=TESTSUITE):
        self.dbfilename = os.path.join(testdb, name + ".db")
        if not os.path.exists(self.dbfilename):
            print(f"initializing db for {name}")
            self.db = self.initialize_db(name, testsuite)
        else:
            self.db = sqlite3.connect(self.dbfilename)
        self.load_all()

    def initialize_db(self, name, testsuite=TESTSUITE):
        testjson = os.path.join(testsuite, name + ".json.gz")
        with gzip.open(testjson) as f:
            tests = json.load(f)

        db = sqlite3.connect(self.dbfilename)
        try:
            cursor = db.cursor()
            cursor.execute("CREATE TABLE tests({})".format(', '.join(TestFile.COLUMNS)))

            for test in tests:
                print("ingesting test {}".format(test['name']))
                name = test['name']
                m = re.fullmatch(r"([0-9A-Fa-f]+) \[(.+)\] (\d+)", name)
                opcode = m[1]
                instruction = m[2]
                number = m[3]
                is_valid = "unknown"
                initial_state = json.dumps(test['initial'])
                expected_state = json.dumps(test['final'])

                cursor = db.cursor()
                cursor.execute("""
                    INSERT INTO tests VALUES
                        (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)
                    """,
                        (name, number, opcode, instruction, is_valid, False, None, initial_state, expected_state, ""))
            db.commit()

        except:
            os.remove(self.dbfilename)
            traceback.print_exc()

        return db

    def load_all(self):
        self.tests = []

        cursor = self.db.cursor()
        result = cursor.execute("SELECT * FROM tests")
        for values in result.fetchall():
            data = { key: value for (key, value) in zip(TestFile.COLUMNS, values) }
            data['initial_state'] = TestState(json.loads(data['initial_state']))
            data['expected_state'] = TestState(json.loads(data['expected_state']))
            data['instruction_len'] = data['expected_state'].state['pc'] - data['initial_state'].state['pc']
            if data['actual_state']:
                data['actual_state'] = TestState(json.loads(data['actual_state']))
            else:
                data['actual_state'] = None
            testcase = TestCase(data)
            self.tests.append(testcase)

    def update(self, case):
        columns = ["is_valid", "has_run", "result", "actual_state"]
        values = []
        for key in columns:
            if 'state' in key:
                values.append(json.dumps(getattr(case, key).state))
            else:
                values.append(getattr(case, key))
        values.append(case.name)

        pairs = [ key + ' = ?' for key in columns ]

        cursor = self.db.cursor()
        cursor.execute("""
            UPDATE tests
            SET {}
            WHERE name = ?""".format(
                ', '.join(pairs)), values)

    def run_tests(self, client):
        try:
            for testcase in self.tests:
                #if test.is_valid == 'unknown':
                #    test.validate()
                if not testcase.validate():
                    print("Test is invalid.  Skipping...")
                    continue
                if testcase.has_run:
                    print("Test has already been run.  Skipping...")
                    continue
                result = client.run_test(testcase)
                self.update(testcase)
        finally:
            self.db.commit()


class TestCase:
    def __init__(self, data):
        for (key, value) in data.items():
            setattr(self, key, value)

    def validate(self):
        # TODO check if the test is expected to generate an interrupt, or some other condition we can't handle atm
        state = self.initial_state.state
        if len(state['ram']) > 2 or self.instruction_len < 0 or self.instruction_len > 4:
            valid = False
        else:
            valid = True
        # TODO don't update the validity for now
        #self.is_valid = valid
        return valid

    def serialize(self):
        return self.initial_state.serialize(self.instruction_len)

    def read_test_response(self, payload):
        self.actual_state = self.initial_state.copy()
        self.actual_state.deserialize_diff(payload)

    def display(self):
        print("Initial:")
        print(self.initial_state)
        print("Expected:")
        print(self.expected_state)
        print("Actual:")
        print(self.actual_state)

    def validate_response(self):
        if self.expected_state.limited_compare(self.actual_state):
            result = 'pass'
        else:
            self.display()
            result = 'fail'
        self.has_run = True
        self.result = result
        return result


class TestState:
    def __init__(self, state):
        self.state = state

    def copy(self):
        return TestState(self.state.copy())

    def __str__(self):
        output = ""
        for i in range(0, 7):
            output += "D{}: {:08x}  A{}: {:08x}\n".format(i, self.state[f'd{i}'], i, self.state[f'a{i}'])
        output += "D7: {:08x} SSP: {:08x}\n".format(self.state['d7'], self.state['ssp'])
        output += "USP: {:08x}\n".format(self.state['usp'])
        output += "PC: {:08x}\n".format(self.state['pc'])
        output += "SR: {:04x}\n".format(self.state['sr'])
        return output

    def serialize(self, instruction_len):
        output = b""
        output += struct.pack('>LLLLLLLL', *(self.state['d{}'.format(i)] for i in range(0, 8)))
        output += struct.pack('>LLLLLLL', *(self.state['a{}'.format(i)] for i in range(0, 7)))
        #output += struct.pack('>L', self.state['ssp'])
        output += struct.pack('>H', self.state['sr'])

        # TODO only 1 to 2 word instructions will be run for now
        if instruction_len == 4:
            output += struct.pack('B', 4)
            output += struct.pack('>HH', self.state['prefetch'][0], self.state['prefetch'][1]);
        else:
            output += struct.pack('B', 2)
            output += struct.pack('>H', self.state['prefetch'][0]);
        return output

    def deserialize_diff(self, payload):
        i = 0
        while i < len(payload):
            if payload[i] in range(0, 8):
                key = payload[i]
                (value,) = struct.unpack('>L', payload[i+1:i+5])
                self.state['d{}'.format(key)] = value
                i += 5
            elif payload[i] in range(8, 15):
                key = payload[i] - 8
                (value,) = struct.unpack('>L', payload[i+1:i+5])
                self.state['a{}'.format(key)] = value
                i += 5
            elif payload[i] == 16:
                (value,) = struct.unpack('>H', payload[i+1:i+3])
                i += 3
                self.state['sr'] = value
            else:
                print("Unrecognized tag: {}".format(payload[i]))
                i += 1

    def limited_compare(self, other):
        keys = [ 'd{}'.format(i) for i in range(0, 8) ] + [ 'a{}'.format(i) for i in range(0, 7) ] + ["sr"]
        for key in keys:
            if self.state[key] != other.state[key]:
                return False
        return True

    """
    def diff(self):
        diff = {}
        for key in self.data['initial_state'].keys():
            if key in ['prefetch']:
                continue
            elif key == 'ram':
                diff['ram'] = [
                    [addr, value]
                    for (addr, value) in self.data['initial_state']['ram']
                    if value != [
                            pair
                            for pair in self.data['expected_state']['ram']
                            if addr == pair[0]
                        ][0][1]
                ]
            else:
                if self.data['initial_state'][key] != self.data['expected_state'][key]:
                    diff[key] = self.data['expected_state'][key]
        return diff
    """
