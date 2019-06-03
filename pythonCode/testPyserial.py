import serial
import time

def testU1():
    tiva = serial.Serial()
    tiva.baudrate = 230400
    tiva.port = 'COM13'
    tiva.timeout = 1
    start_time = time.time()
    tiva.open()

    while (True):
        print("start reading")
        tiva.timeout = None
        print(tiva.readline().decode('utf-8'));
        tiva.flush()

def SimRS():
    # Spin up the Serial Port
    tiva = serial.Serial()
    tiva.baudrate = 9600#230400
    tiva.port = 'COM12'
    tiva.timeout = 1
    start_time = time.time()
    tiva.open()
    tiva.timeout = None
    i = 0.5
    while(True):
        tiva.write(("0IC\r").encode('utf-8'))
        tiva.flush()
        # print(tiva.read(1).decode('utf-8'))
        buffer = ""
        while True:
            oneByte = tiva.read(1)
            if oneByte == b"\r":  # method should returns bytes
                break
            else:
                buffer += oneByte.decode("ascii")
        print("read:",buffer)


if __name__ == '__main__':
    # testU1()
    SimRS()

