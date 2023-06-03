
import os
import re
import gzip
import json
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
            testcase = TestCase(data)
            self.tests.append(testcase)

    def update(self, case):
        columns = ["is_valid", "has_run", "result", "actual_state"]
        values = []
        for key in columns:
            values.append(key)
            values.append(case.data[key])
        values.append(case.data['name'])

        cursor = self.db.cursor()
        cursor.execute("""
            UPDATE tests
            SET {}
            WHERE name = ?""".format(
                ', '.join(['? = ?'] * len(columns))))
        self.db.commit()

    def run_tests(self, client):
        for test in self.tests:
            if test.data['is_valid'] == 'unknown':
                test.validate()
            if test.data['has_run']:
                continue
            client.send_test(test)


class TestCase:
    def __init__(self, data):
        self.data = data

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

    def validate(self):
        # TODO check if the test is expected to generate an interrupt, or some other condition we can't handle atm
        pass

    def initial_state(self):
        return self.data['initial_state']

    def serialize(self):
        return b""

