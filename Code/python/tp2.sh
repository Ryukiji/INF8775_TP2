#!/bin/sh

programname=$0

function usage {
	echo "Vous avez mal entré les paramètres. Veuillez réessayer avec les options suivantes:"
    echo "usage: $programname -a [brute | recursif | seuil] -e [path_vers_exemplaire]"
    echo "  -a      accepte l'une des options suivantes: brute | recursif | seuil"
    echo "  -e      path_vers_exemplaire peut être un chemin absolu,"
	echo "  relatif ou seulement le nom du fichier si ce dernier est dans le même directory"
    exit 1
}
while [ "$1" != "" ]; do
    case $1 in
        -a )    shift
                ALGO=$1
                ;;
        -e )    shift
				file=$(basename $1)
				dir=$(dirname $1)
                PATH="$dir/$file"
                ;;
        -p )    P=$1
                ;;
        -t )    T=$1
                ;;
        * )     usage
                exit 1
    esac
    shift
done
 
/usr/local/bin/python3 main.py $ALGO $PATH $P $T

