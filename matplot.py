import matplotlib.pylab as plt
import seaborn as sns
import numpy as np

sns.set()

plt.subplot(311)
plt.plot(range(1,6), np.random.randint(1,30,5))

plt.subplot(312)
x = np.linspace(0,5,100)
plt.plot(x,np.sin(x),c = 'r')

plt.subplot(313)
t = np.linspace(-2*np.pi,2*np.pi,500)
r = np.sin(6*t)
x = r*np.cos(t)
y = r*np.sin(t)
plt.plot(x,y)
#軸控制項
axs = plt.gca()
axs.set_aspect('equal')
'''
axs.set_facecolor(' ')
axs.set_xlim(xmin,xmax)
axs.set_ylim(ymin,ymax)
axs.spines['right,top,bottom,left'].set_color('none')
axs.spines['right,top,bottom,left'].set_position(('data',0))
axs.set_aspect('equal')

'''

plt.show()
