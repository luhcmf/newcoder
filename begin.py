a = [1,3,5,7,9]
for i in range(0,len(a)):
    print(a[i]**2, end = ' ')
    a[i] = a[i]**2
print('\n')
print(a)
