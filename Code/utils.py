
""" 
Trie les points par surface
sortedPoints = sorted(POINTS, key = sortsurface, reverse=True)
 """
def sortsurface(val): 
    return val[0]*val[1] 

'''
Calcule la distance entre deux points
'''
def isLegal(brique, tour):
    s = [0,0,0]

    if(tour == []):
        s = brique
    elif (brique[0] < tour[len(tour)-1][0] and brique[1] < tour[len(tour)-1][1]):
        s = brique
    return s != [0,0,0]
