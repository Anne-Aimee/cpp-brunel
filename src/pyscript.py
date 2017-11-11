import numpy as np
import matplotlib.pyplot as pl
data = np.genfromtxt('graphfile.txt' )
select= np.array([d for d in data if d[1] < 30])
data1=select.transpose()
pl.subplot(2,1,1)
pl.scatter(data1[0]*0.1,data1[1],alpha=0.8, edgecolors='none');
pl.xlabel('time ms');
pl.ylabel('neuron');
#pl.show();

data2 =data.transpose()
pl.subplot(2,1,2)
n, bins, patches = pl.hist(data2[0]*0.1,1000,normed=0, alpha=0.75)

pl.show();
