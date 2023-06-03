
import time
import serial
import struct
import threading

class SerialClient:
    CMD_SEND_TEST = 2

    def __init__(self, device, baud):
        self.device = device
        self.baud = baud
        self.tty = None

        self.connect()
        self.thread = threading.Thread(None, self._run, 'SerialThread')
        self.thread.start()

    def connect(self):
        self.tty = serial.Serial(self.device, self.baud, rtscts=True)

    def close(self):
        if self.tty:
            self.tty.close()
        self.tty = None

    def send_test(self, testcase):
        data = testcase.serialize()
        header = struct.pack(">hB", len(data) + 3, self.CMD_SEND_TEST)
        self.tty.write(header + data)

    """
    def _run(self):
        while True:
            line = self.tty.readline()
            print(line)
    """
