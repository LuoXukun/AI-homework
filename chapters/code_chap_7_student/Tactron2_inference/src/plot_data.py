import matplotlib
matplotlib.use('agg')
import matplotlib.pylab as plt
import numpy as np
from PIL import Image
 
def plot_data(idx,data,figsize=(16,4)):
    #fig,axes = plt.subplots(1,1,figsize=figsize)
    fig,axes = plt.subplots(1,len(data),figsize=figsize)
    for i in range(len(data)):
    #for i in range(1):
        #axes.imshow(data[i],aspect='auto',origin='lower',interpolation='none')
        axes[i].imshow(data[i],aspect='auto',origin='lower',interpolation='none')
        png_name = str(idx)+"_"+str(i) + '.png'
        #tmp_file = axes.figure
        tmp_file = axes[i].figure
        tmp_file.savefig(png_name)
