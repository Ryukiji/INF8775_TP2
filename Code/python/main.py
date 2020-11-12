#!/usr/local/bin/python3
import random
import math
import sys
import time
import csv
import csv
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns
import sys

from pathlib import Path

'''
Fonction qui calcule le test de rapport
'''
def test_rapport(tablePath):
    data = pd.read_csv(tablePath)
##        On change fx n**2 pour brute et nlog(n) pour recursif et seuil
    data["Temps"] = data["Temps"]/(data["Taille"]**2)
    colors = ["b", "r", "g"]
    plt.clf()
    fig = plt.figure()   
    ax = fig.add_subplot(1,1,1)
    x = np.array(data["Taille"])
    y = np.array(data["Temps"])
    ax.scatter(x, y, c = colors[0])
    print(np.polyfit(x, y, 1))

    ax.legend(loc="lower right")
    plt.show()
    fig.savefig("Rapport progdyn")


def test_constante(tablePath):
    data = pd.read_csv(tablePath)
    colors = ["b", "r", "g"]
    plt.clf()
    fig = plt.figure()   
    ax = fig.add_subplot(1,1,1)
##        On change fx n**2 pour brute et nlog(n) pour recursif et seuil
    fx=(data["Taille"])**2
    x = np.array(fx)
    y = np.array(data["Temps"])
    ax.scatter(x, y, c = colors[0])
    ax.plot(x, np.poly1d(np.polyfit(x, y, 1))(x),c= colors[0])
    #print(np.poly1d(np.polyfit(x, y, 1))(x))

    ax.legend(loc="lower right")
    plt.show()
    fig.savefig("constante progdyn")
        

if __name__ == "__main__":
    test_constante("./progdyn.csv")