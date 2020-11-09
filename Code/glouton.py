import sys
import time
from utils import isLegal, sortsurface

'''
Algorithme glouton déterministe.
'''
def glouton(points):
        
    tour = []
    sortedPoints = sorted(points, key = sortsurface, reverse=True)
    tourHeight = 0

    while (len(sortedPoints) != 0):
        b =sortedPoints[0]
        del sortedPoints[0]
        if(isLegal(b, tour)):
            tour.append(b)
            tourHeight += b[0]

    return tourHeight


def execute_glouton(points):
    start = time.time()
    tour = glouton(points)
    print(tour)
    end = time.time()
    return end-start, tour
