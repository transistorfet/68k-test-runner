
import argparse
import traceback

from host.serial_server import SerialServer
from host.testcase import TestFile

def main():
    parser = argparse.ArgumentParser(prog='host', description='Test hosting program for a serial-based test runner')
    parser.add_argument('-d', '--device', action='store_true', help='Device file to connect to', default='/dev/ttyUSB1')
    parser.add_argument('-b', '--baud', action='store_true', help='Baud rate for serial connection', default='38400')
    parser.add_argument('-l', '--limit', action='store_true', help='Limit the speed of transmission')
    args = parser.parse_args()

    tests = TestFile("ABCD.json.gz")

    try:
        client = SerialClient()
        client.start_test(tests[0])
    except KeyboardInterrupt:
        print("Exiting")
    except:
        traceback.print_exc()

    server.stop()

if __name__ == '__main__':
    main()

