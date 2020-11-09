import sys
import time
import random
'''
Algorithme tabou
'''
def tabou(points):
    test = [(4, 6, 7), (6, 4, 7), (7, 4, 6), (1, 2, 3), (2, 1 ,3), (3, 1 ,2), (4, 5, 6), (5, 4, 6), (6, 4 ,5), (10, 12, 32), (12, 10, 32), (32, 10, 12)]
    tower = []
    for i in range(10):
        if not len(tower):
            tower.append(random.choice(test))
        neighbors = getNeighbors(tower, test)
        print(neighbors)
        bestNeighbor = getBestNeighbor(neighbors)
        print(bestNeighbor)
        tower = bestNeighbor
    return tower

def getNeighbors(tower, points):
    neighbors = {}
    neighborBlocs = points.copy()
    for blocs in tower:
        neighborBlocs.remove(blocs)

    for i, blocs in enumerate(neighborBlocs):
        tempTower = []
        indexBloc = []
        for j, blocTower in enumerate(tower):
            tempTower.append(blocTower)
            if blocs[1] < blocTower[1] and blocs[2] < blocTower[2]:
                indexBloc.append((j, blocs))
        if len(indexBloc):
            print(i)        
            highestIndexBloc = max(indexBloc)
            if highestIndexBloc[0] == len(tempTower) - 1:
                tempTower.append(highestIndexBloc[1])
            else:
                tempTower[highestIndexBloc[0]+1] = highestIndexBloc[1]
                tempTower = tempTower[:highestIndexBloc[0]+1]
                tempTower.append(highestIndexBloc[1])
        neighbors[i] = tempTower

    return neighbors

def getBestNeighbor(neighbors):
    maxDistance = 0
    bestNeighbor = []
    for index in neighbors:
        height = 0
        for tower in neighbors[index]:
            height += tower[0]
        if height > maxDistance:
            maxDistance = height
            bestNeighbor = neighbors[index]
    return bestNeighbor




def execute_tabou(points):
    start = time.time()
    tour = tabou(points)
    end = time.time()
    return end-start, tour
