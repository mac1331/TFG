import serial
import time
if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyACM1', 57600, timeout=1)
    ser.flush()
    while True:
        ser.write(b"vec,-0,0\n")
        line = ser.readline().decode('utf-8').rstrip()
        print(line)
        time.sleep(0.01)
