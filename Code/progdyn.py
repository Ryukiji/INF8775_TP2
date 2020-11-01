import sys
import time

'''
Algorithme programmation dynamique.
'''
def progdyn(points):
    tour = points
    return tour


def execute_progdyn(points):
    start = time.time()
    tour = progdyn(points)
    end = time.time()
    return end-start, tour
