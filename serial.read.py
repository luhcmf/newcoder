import serial
ser = serial.Serial("com7",19200,timeout = 0.5)
data = [03, 00, 00]
ser.write(data)
