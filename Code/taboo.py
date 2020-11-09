import sys
import time
import random
from random import randrange
from utils import isLegal, sortsurface, totalheight

'''
Algorithme tabou
'''
def tabou(points):
    # test = [(4, 6, 7), (6, 4, 7), (7, 4, 6), (1, 2, 3), (2, 1 ,3), (3, 1 ,2), (4, 5, 6), (5, 4, 6), (6, 4 ,5), (10, 12, 32), (12, 10, 32), (32, 10, 12)]
    # tower = []
    # print(totalheight(test))
    # print(totalheight(tower))
    # for i in range(10):
    #     if not len(tower):
    #         tower.append(random.choice(test))
    #     neighbors = getNeighbors(tower, test)
    #     print(neighbors)
    #     bestNeighbor = getBestNeighbor(neighbors)
    #     print(bestNeighbor)
    #     tower = bestNeighbor
    # return tower

    listVoisins = points.copy()
    solutionLocal = []
    solutionGlobal = []
    listTabou = []
    iterationSansAmelioration = 0

    while(iterationSansAmelioration < 100):
        
        solutionLocal, listTabou, listVoisins = maximize(solutionLocal, listTabou, listVoisins)
        if(totalheight(solutionGlobal) < totalheight(solutionLocal)):
            solutionGlobal = solutionLocal
            iterationSansAmelioration = 0
        else:
            iterationSansAmelioration += 1

    totalheighttower = totalheight(solutionGlobal)
    return totalheighttower

def maximize(solutionLocal, listTabou, listVoisins):
    solutionMaximized = []
    blocksRemovedFinal = []
    maximizingBlockPos = -1

    pos = 0

    for i in listVoisins:
        solutionCandidate = []
        blocksRemoved = []
        solutionCandidate, blocksRemoved = fitVoisinInSolution(solutionLocal, i)


        if(totalheight(solutionCandidate) > totalheight(solutionMaximized)):
            solutionMaximized = solutionCandidate
            blocksRemovedFinal = blocksRemoved
            maximizingBlockPos  = pos

        pos += 1

    listTabou, voisinsLibre = deleteFromTabou(listTabou)
    if(voisinsLibre != []):
        for j in voisinsLibre:
            listVoisins.append(j)

    if(blocksRemovedFinal != []):
        listTabou  = addToTabou(listTabou,blocksRemovedFinal)

    if(maximizingBlockPos != -1):
        del listVoisins[maximizingBlockPos]
    if(solutionMaximized != []):
        solutionLocal = solutionMaximized

    return solutionLocal, listTabou, listVoisins



def fitVoisinInSolution(solutionLocal, blockCandidat):
    solutionCandidate = solutionLocal.copy()
    blocksRemoved = [] 
    
    
    solutionCandidate,blocksRemoved = deConstruct(solutionCandidate, blockCandidat)
    solutionCandidate,blocksRemoved = reConstruct(solutionCandidate, blocksRemoved)

    return solutionCandidate, blocksRemoved

def deConstruct(solutionLocal, blockCandidat):
    r = []
    s = solutionLocal.copy()
    fit = False

    while(fit == False):
        if(isLegal(blockCandidat,s)):
            s.append(blockCandidat)
            fit = True
        else:
            r.append(s[-1])
            del s[-1]
    return s,r


def reConstruct(s, r):
    index = len(r) - 1

    while(index > 0):
        if(isLegal(r[index],s)):
            s.append(r[index])
            del r[index]
        index -= 1
    return s, r


def addToTabou(t,b):

    for i in b:
        t.append([i,random.randint(7,10)])

    return t

def deleteFromTabou(t):

    voisinsLibre = []
    j = 0
    for i in range(len(t)):
        
        t[j][1] -= 1
        if(t[j][1] == 0):
            voisinsLibre.append(t[j][0])
            del t[j]
            j -= 1
        j += 1

    return t,voisinsLibre


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
