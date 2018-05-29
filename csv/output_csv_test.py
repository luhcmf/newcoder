import csv

myfilepath = 'D:/papa/python/csv/temp/outputtest.csv'
'''
# output csv
myfilepath = 'D:/papa/python/csv/temp/outputtest.csv'
with open(myfilepath,'w',newline = '') as csvfile:
    file = csv.writer(csvfile,delimiter = ',',quotechar='|')

    file.writerow(['11','12','13'])
    file.writerow(['21','22','23','24'])
    file.writerow(['31','32','33','34',])


#read csv
with open('testfile.csv',newline='') as csvfile:
    file = csv.reader(csvfile,delimiter = ',')
    for row in file:
        print(row)
'''

with open(myfilepath,'a',newline='') as csvfile:    # a for append
    file = csv.writer(csvfile,delimiter = ',')  #default delimiter = ','
    
    file.writerow(['2','22'])
    print('done')
