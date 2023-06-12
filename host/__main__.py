
import argparse
import traceback

from host.serial import SerialClient
from host.testcase import TestFile

def main():
    parser = argparse.ArgumentParser(prog='host', description='Test hosting program for a serial-based test runner')
    subparsers = parser.add_subparsers()

    cmd = subparsers.add_parser("test", help="Run the tests using the test runner")
    cmd.add_argument('-d', '--device', action='store_true', help='Device file to connect to', default='/dev/ttyUSB1')
    cmd.add_argument('-b', '--baud', action='store_true', help='Baud rate for serial connection', default='38400')
    cmd.add_argument('instruction', help='Instruction to test')
    #cmd.add_argument("instruction", nargs='+', help='Instruction to test')
    cmd.set_defaults(command=run_tests)

    cmd = subparsers.add_parser("report", help="Show a report of the results")
    cmd.add_argument('instruction', help='Instruction to test')
    #cmd.add_argument("files", nargs='+')
    cmd.set_defaults(command=show_report)

    args = parser.parse_args()
    args.command(args)


def run_tests(args):
    tests = TestFile(args.instruction)

    client = None
    try:
        client = SerialClient(args.device, args.baud)
        tests.run_tests(client)
        client.close()

    except KeyboardInterrupt:
        print("Exiting")

    except:
        traceback.print_exc()
        if client:
            client.close()


def show_report(args):
    count = 0
    tests = TestFile(args.instruction)
    for testcase in tests.tests:
        if testcase.result == 'fail':
            print(testcase.name)
            print("Initial: {}".format(testcase.initial_state))
            print("Expected: {}".format(testcase.expected_state))
            print("Actual: {}".format(testcase.actual_state))
            count += 1
    print("Failed: {}".format(count))
    print("Total: {}".format(len(tests.tests)))


if __name__ == '__main__':
    main()

