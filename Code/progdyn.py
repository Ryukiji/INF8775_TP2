import sys
import time

class Box:
    def __init__(self, h, l, p):
        self.h = h
        self.l = l
        self.p = p

'''
Algorithme programmation dynamique.
'''
def progdyn(points):
    boxes = {}
    result = []
    for i in points:
        boxes[i[1]*i[2]] = i
    keys = sorted(boxes.keys(), reverse=True)
    for key in keys:
        result.append(boxes[key])
    print(result)
    n = len(result)
    max_height = [0]*n
    for i in range(n):
        for j in range(i):
            if (result[i][1] < result[j][1] and result[i][2] < result[j][2]):
                max_height[i] = max(max_height[i], max_height[j])
        max_height[i] += result[i][0]


    return max(max_height)


def execute_progdyn(points):
    start = time.time()
    tour = progdyn(points)
    print(tour)
    end = time.time()
    return end-start, tour
