#!/usr/bin/python3
import random
import math
import sys
import time
import csv
import os


from glouton import execute_glouton
from progdyn import execute_progdyn
from taboo import execute_tabou
from pathlib import Path
from utils import isLegal, sortsurface

PATH = "./"

'''
Un point est représenté par un tuple (position_x, position_y)
La fonction generate_points génère une liste de N points.
'''
def generate_points(FILE):
    with open(FILE) as f:
        mylist = [tuple(map(float, i.split(' '))) for i in f]
    return mylist


def analyseDesResultats(program):
    #Il faut modifier le retour des fonctions pour qu'ils ne retournent que le max height pour l'analyse
    path_exemplaires = "../Exemplaires"
    exemplaires = os.listdir(path_exemplaires)
    newFilePath = "../Exemplaires/results/"+program+".csv"
    newFile = os.path.isfile(newFilePath)
    print(exemplaires)
    with open(newFilePath, "w") as f: 
        if not newFile : 
            f.write("exemplaires,temps,height")
        for exemplaire in exemplaires : 
            d = generate_points("../Exemplaires/"+exemplaire)
            start_time = time.time()
            if program == "dynamic":
                height = str(execute_progdyn(d))
            elif program == "glouton":
                height = str(execute_glouton(d))
            elif program == "taboo":
                height = str(execute_glouton(d))              
            execution_time = str(time.time() - start_time)
            print(exemplaire, execution_time, height)
            f.write(exemplaire + ',' + execution_time + ',' + height)


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
    POINTS = generate_points('../Exemplaires/test.txt')
    time, tour = execute_progdyn(POINTS)