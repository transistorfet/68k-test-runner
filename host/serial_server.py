
import time
import serial

class SerialClient:
    def __init__(self, device, baud):
        self.device = device
        self.baud = baud
        self.tty = None

    def start(self):
        try:
            self.tty = serial.Serial(self.device, self.baud, rtscts=True)
        except serial.serialutil.SerialException as exc:
            print("serial error: " + str(exc))
            return

        while True:
            line = f.readline()
            print(line)


    def other(self):
        print("Opening {}".format(args.filename))
        with open(args.filename, 'r') as f:
            while True:
                ch = f.read(1)
                if not ch:
                    break
                if args.limit:
                    time.sleep(0.001)
                #time.sleep(0.05)
                tty.write(bytes(ch, 'ascii'))

    def stop(self):
        self.tty.close()

