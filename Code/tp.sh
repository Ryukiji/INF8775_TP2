#!/bin/sh

while [ "$1" != "" ]; do
    case $1 in
        -a )    shift
                ALGO=$1
                ;;
        -e )    shift
                PATH=$1
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

if [ ! $ALGO ]
then
    echo "No algorithm supplied"
    exit 1
fi

if [ $ALGO != "vorace" ] && [ $ALGO != "progdyn" ] && [ $ALGO != "tabou" ]
then
    echo "$ALGO is not a valid algorithm"
    exit 1
fi

if [ ! -f $PATH ]
then
    echo "File not found!"
    exit 1
fi

/usr/bin/g++ -std=c++17 -O3 src/main.cpp -o main
./main $ALGO $PATH $P $T
