
import gzip
import json
import os.path


TESTSUITE = "tests/ProcessorTests/680x0/68000/v1/"

class TestFile:
    def __init__(self, name, testsuite=TESTSUITE):
        filename = os.path.join(testsuite, name)
        with gzip.open(filename) as f:
            self.tests = json.load(f)

        diff = TestCase(self.tests[0]).diff()
        print(diff)


class TestCase:
    def __init__(self, data):
        self.data = data

    def diff(self):
        diff = {}
        for key in self.data['initial'].keys():
            if key in ['prefetch']:
                continue
            elif key == 'ram':
                diff['ram'] = [
                    [addr, value]
                    for (addr, value) in self.data['initial']['ram']
                    if value != [
                            pair
                            for pair in self.data['final']['ram']
                            if addr == pair[0]
                        ][0][1]
                ]
            else:
                if self.data['initial'][key] != self.data['final'][key]:
                    diff[key] = self.data['final'][key]
        return diff

