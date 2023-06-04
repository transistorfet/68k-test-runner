
import time
import serial
import struct
import threading

class SerialClient:
    CMD_SEND_TEST = 2
    CMD_RESPOND_TEST = 3

    def __init__(self, device, baud):
        self.device = device
        self.baud = baud
        self.tty = None

        self.connect()
        #self.thread = threading.Thread(None, self._run, 'SerialThread')
        #self.thread.start()

    def connect(self):
        print("connecting to test runner on {} {}".format(self.device, self.baud))
        self.tty = serial.Serial(self.device, self.baud, rtscts=True)

    def close(self):
        if self.tty:
            self.tty.close()
        self.tty = None

    def run_test(self, testcase):
        print("sending test {}", testcase.name)
        self.send_message(self.CMD_SEND_TEST, testcase.serialize())
        print("waiting for response...")
        (cmd, payload) = self.receive_message()
        if cmd != 3:
            print(f"received unexpected return {cmd}")
            return 'invalid'
        else:
            testcase.read_test_response(payload[1:])
            result = testcase.validate_response()
            print(f"Result: {result}")
            return result

    def send_message(self, cmd, payload):
        header = struct.pack('>hBB', len(payload) + 2, cmd, 0)
        self.tty.write(header + payload)

    def receive_message(self):
        (length,) = struct.unpack('>h', self.tty.read(2))
        data = self.tty.read(length)
        cmd = data[0]
        return (cmd, data[1:])

