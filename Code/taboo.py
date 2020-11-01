import sys
import time

'''
Algorithme tabou
'''
def tabou(points):
    tour = points
    return tour


def execute_tabou(points):
    start = time.time()
    tour = tabou(points)
    end = time.time()
    return end-start, tour
