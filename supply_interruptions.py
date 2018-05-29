import matplotlib.pyplot as plt
import numpy as np

x = np.arange(0,350,0.01)
y = []
Usmin = 9
for i in x:
    if i <= 10:
        vol = Usmin
    if i > 10:
        t1 = int((i-10)/15) + 1
        while 1:
            t2 = (i-10)%15
            if t2 >= 15:
                t2 %= 15
            else:
                break;
        if t1 > 20:
            vol = Usmin
        else:
            if t2 < 5:
                delta = t1*0.05
                vol = Usmin*(1-delta)
            elif t2 >= 5:
                vol = Usmin
    y.append(vol)
    #print(delta)

plt.plot(x,y)
plt.grid()
plt.show()
