grades = []
_sum = 0
for i in range(1,6):
    num = input("number {} =".format(i))
    _sum += int(num)
    grades.append(num)
print("average = {},{}".format(_sum/5,5))
