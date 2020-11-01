import sys
import time

'''
Algorithme glouton déterministe.
'''
def glouton(points):
    tour = points
    return tour


def execute_glouton(points):
    start = time.time()
    tour = glouton(points)
    end = time.time()
    return end-start, tour
