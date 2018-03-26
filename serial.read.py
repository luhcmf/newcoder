import serial
from time import sleep


try:
    ser = serial.Serial("com8",19200,timeout = 0.1)
except:
    print('port unconnected')
sleep(0.5)
while ser.name:
    while ser.inWaiting():
        val = ser.read(ser.inWaiting())
        print(val)
        #print(int.from_bytes(val,byteorder='big'))        
        
