import serial
from time import sleep

try:
    ser = serial.Serial('com4',19200)
    while ser.name:
        ser.write("H".encode())
        sleep(1)
        ser.write("L".encode())
        sleep(1)
except IOError:
    print("not connecting")
