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
/usr/bin/g++ -std=c++17 -O3 src/main.cpp -o main
./main $ALGO $PATH $P $T
