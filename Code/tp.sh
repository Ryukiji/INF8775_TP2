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
/usr/bin/g++ -std=c++17 /Users/mouradyounes/AUT2020_V1/INF8775/INF8775_TP2/Code/src/main.cpp -o main
./main $ALGO $PATH $P $T
