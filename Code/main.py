#!/usr/bin/python3
import random
import math
import sys
import time
import csv

from glouton import execute_glouton
from progdyn import execute_progdyn
from taboo import execute_tabou
from pathlib import Path

PATH = "./"

'''
Un point est représenté par un tuple (position_x, position_y)
La fonction generate_points génère une liste de N points.
'''
def generate_points(FILE):
    with open(FILE) as f:
        mylist = [tuple(map(float, i.split(' '))) for i in f]
    return mylist


'''
--------------------------------------------------------------------
ATTENTION : Dans votre code vous devez utiliser le générateur gen.py
pour générer des points. Vous devez donc modifier ce code pour importer
les points depuis les fichiers générés.
De plus, vous devez faire en sorte que l'interface du tp.sh soit
compatible avec ce code (par exemple l'utilisation de flag -e, -a, (p et -t)).
--------------------------------------------------------------------
 '''
 
def main(argv):

    algos = ["vorace", "progdyn", "tabou"]
    
    if Path(argv[1]).is_file():
        POINTS = generate_points(argv[1])
    else:
        print("Les paramètres ne sont pas correcte ou vous n'avez pas entré un fichier valide.")
        sys.exit()
    if not argv[0].lower() in algos:
        print("Les paramètres ne sont pas correcte Veuillez vous assurer d'avoir entrer l'une des options suivante en respéctant la casse")
        print("vorace | progdyn | tabou")
        sys.exit()    

        

    if argv[0].lower() == "vorace":
        #Exécuter l'algorithme glouton
        time_glouton, tour_glouton = execute_glouton(POINTS)
        if '-t' in argv:
            print("Temps : ", time_glouton)
        if '-p' in argv:
            print("Tour: ", tour_glouton)
        
    
    elif argv[0].lower() == "progdyn":
        #Exécuter l'algorithme programmation dynamique
        time_progdyn, tour_progdyn = execute_progdyn(POINTS)
        if '-t' in argv:
            print("Temps : ", time_progdyn)
        if '-p' in argv:
            print("Tour: ", tour_progdyn)
        
        
    elif argv[0].lower() == "tabou":
        #Exécuter l'algorithme recherche tabou
        time_tabou, tour_tabou = execute_tabou(POINTS)
        if '-t' in argv:
            print("Temps : ", time_tabou)
        if '-p' in argv:
            print("Plus petite distance: ", tour_tabou)
        

if __name__ == "__main__":
##    main(sys.argv[1:])
    POINTS = generate_points('../Exemplaires/b100_1.txt')
    time, tour = execute_glouton(POINTS)
print('wait')