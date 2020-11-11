
""" 
Trie les points par surface
sortedPoints = sorted(POINTS, key = sortsurface, reverse=True)
 """
def sortsurface(val): 
    return val[1]*val[2] 

'''
Vérifie si la brique peut se poser sur la tour
'''
def isLegal(brique, tour):
    s = [0,0,0]

    if(tour == []):
        s = brique
    elif (brique[1] < tour[len(tour)-1][1] and brique[2] < tour[len(tour)-1][2]):
        s = brique
    return s != [0,0,0]


'''
Calcule la hauteur totale d'une solution
'''

def totalheight(listBlocs):
    height = 0
    for i in listBlocs:
        height += i[0]
    return height


