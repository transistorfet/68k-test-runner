
import argparse
import traceback

from host.serial import SerialClient
from host.testcase import TestFile

def main():
    parser = argparse.ArgumentParser(prog='host', description='Test hosting program for a serial-based test runner')
    parser.add_argument('-d', '--device', action='store_true', help='Device file to connect to', default='/dev/ttyUSB1')
    parser.add_argument('-b', '--baud', action='store_true', help='Baud rate for serial connection', default='38400')
    parser.add_argument('-l', '--limit', action='store_true', help='Limit the speed of transmission')
    args = parser.parse_args()

    tests = TestFile("ASL.b")

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

if __name__ == '__main__':
    main()

