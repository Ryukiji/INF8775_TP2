import sys
import time
from utils import isLegal, sortsurface

'''
Algorithme programmation dynamique.
'''
def progdyn(points):
    sortedPoints = sorted(points, key = sortsurface, reverse=True)
    n = len(sortedPoints)
    blocs = {}
    max_height = [0]*n
    for i in range(n):
        max_height[i] = sortedPoints[i][0]

    for i in range(n):
        for j in range(i):
            if (sortedPoints[i][1] < sortedPoints[j][1] and sortedPoints[i][2] < sortedPoints[j][2]):
                if max_height[i] < max_height[j] + sortedPoints[i][0]:
                    max_height[i] = max_height[j] + sortedPoints[i][0]
                    blocs[sortedPoints[i]] = sortedPoints[j]
    
    answer = []
    tempBlocs = sorted(blocs, key = sortsurface, reverse=False)
    currentBloc = tempBlocs[0]
    while currentBloc in blocs.keys():
        answer.append(currentBloc)
        currentBloc = blocs[currentBloc]
    answer.append(currentBloc)
    answer = sorted(answer, key = sortsurface, reverse=True)
    return answer


def execute_progdyn(points):
    start = time.time()
    tour = progdyn(points)
    print(tour)
    end = time.time()
    return end-start, tour
