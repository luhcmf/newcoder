#import sys
import csv


while True:
    indata = input("enter the data\n")
    if indata == "quit":
        break
    else:
        with open("csv/inputcsv.csv",'a',newline='') as csvfile:
            wr = csv.writer(csvfile,delimiter=',')
            data = str(int(indata))
            wr.writerow(data)
'''
try:
    print(sys.argv[1])    
    with open('/csv/temp/sysinput.csv','w',newline = '') as csvfile:
        myinput = csv.writer(csvfile,delimiter=',')
        myinput.wrtierow(sys.srgv[1])
        
except:
    print("no input in your commend line")
'''
