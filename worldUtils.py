import os
import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt
from matplotlib import colors

def readWorld(outDir,fileIn):

    worldName = fileIn[0:-4]

    with open(outDir + fileIn) as f:

        iLine = 0

        lines = f.readlines()
        cells = [int(x) for x in lines[0].split()]

        nRows = len(lines)
        nCol = len(cells)

        world = np.zeros((nRows,nCol),dtype=int)

        for line in lines:
            cells = [int(x) for x in line.split()]
            nCol = len(cells)

            world[iLine,:] = cells
            iLine += 1

    return world, worldName


def plotWorld(worldIn,worldNameIn):
    [s1,s2] = worldIn.shape

    c = plt.pcolor(range(0,s2),range(0,s1),worldIn,cmap='Blues')
    ax = plt.colorbar(c)
    ax.set_label('Cell status', rotation=270)
    ax.set_ticks([0,1])
    ax.set_ticklabels(['Dead','Alive'])
    plt.xlabel('X dimension')
    plt.ylabel('Y dimension')
    plt.title(worldNameIn)
    plt.savefig('/home/pv/Documents/code/cpp/life-is-a-wheel/figs/'+worldNameIn+'.png',dpi=300)
    plt.close()