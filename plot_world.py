import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt
from matplotlib import colors
import os
from worldUtils import plotWorld,readWorld

def __main__():

    outDir = '/home/pv/Documents/code/cpp/life-is-a-wheel/outputs/'
    outFiles = os.listdir(outDir)

    for files in outFiles:
        world,worldName = readWorld(outDir,files)
        plotWorld(world,worldName)

__main__()
