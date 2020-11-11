#ifndef TABU_H
#define TABU_H
#include <iostream>
#include <list>
#include <tuple>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include "utils.h"

using namespace std;

list<tuple<int, int, int>> fitVoisinsInSolution(list<tuple<int, int, int>>* localSolution, list<tuple<int, int, int>>* blocsRemoved, tuple<int, int, int> bloc) {
	list<tuple<int, int, int>> candidate = *localSolution;
	bool fit = false;

	while (!fit) {
		if (isLegal(bloc, &candidate)) {
			candidate.push_back(bloc);
			fit = true;
		} else {
			blocsRemoved->push_back(candidate.back());
			candidate.remove(candidate.back());
		}
	}
    list<tuple<int, int, int>>::reverse_iterator it = blocsRemoved->rbegin();
	for (int i = 0; i < blocsRemoved->size(); i++) {
		if (isLegal(*it, &candidate)) {
			candidate.push_back(*it);
			//*it = blocsRemoved->erase(next(it).base());
            it = decltype(it)(blocsRemoved->erase(std::next(it).base()));
			i--;
        }
        else {
            ++it;
        }
            

	}
	return candidate;
}

list<tuple<int, int, int>> deleteFromTabou(list<tuple<int, int, int, int>>* tabuList) {
	list<tuple<int, int, int>> freeNeighbors = {};
	list<tuple<int,int,int, int>>::iterator it = tabuList->begin();
	for (int i = 0; i < tabuList->size(); i++) {
		get<3>(*it) -= 1;
		if (!get<3>(*it)) {

			freeNeighbors.push_back(make_tuple(get<0>(*it), get<1>(*it), get<2>(*it)));
            it = tabuList->erase(it);
		}
        else {
            ++it;
        }
		
	}
	return freeNeighbors;
}

void addToTabou(list<tuple<int, int, int, int>>* tabuList, list<tuple<int, int, int>> blocsRemovedFinal) {
	for (tuple<int,int,int> bloc : blocsRemovedFinal) {
		tabuList->push_back(make_tuple(get<0>(bloc), get<1>(bloc), get<2>(bloc), rand()%(10-7 + 1) + 7));
	}
}

list<tuple<int, int, int>> maximize(list<tuple<int, int, int>>* solutionLocal, list<tuple<int, int, int, int>>* listTabou, list<tuple<int, int, int>>* listVoisins) {
	list<tuple<int, int, int>> solutionMaximized = {};
	list<tuple<int, int, int>> blocksRemovedFinal = {};
	tuple<int, int, int> maximizingBlocs;

	for (tuple<int, int, int> bloc : *listVoisins) {
		list<tuple<int, int, int>> solutionCandidate;
		list<tuple<int, int, int>> blocsRemoved;
		solutionCandidate = fitVoisinsInSolution(solutionLocal, &blocsRemoved, bloc);

		if (totalHeight(&solutionCandidate) > totalHeight(&solutionMaximized)) {
			solutionMaximized = solutionCandidate;
			blocksRemovedFinal = blocsRemoved;
			maximizingBlocs = bloc;
		}

	}
	list<tuple<int, int, int>> voisinsLibre = deleteFromTabou(listTabou);
	if (voisinsLibre.size()) {
		for (tuple<int, int, int> bloc : voisinsLibre) {
			listVoisins->push_back(bloc);
		}
	}

	if (blocksRemovedFinal.size()) {
		addToTabou(listTabou, blocksRemovedFinal);
	}

	if (true) {
		listVoisins->remove(maximizingBlocs);
	}
	if (solutionMaximized.size()) {
		solutionLocal = &solutionMaximized;
        
	}
    return solutionMaximized;
}

list<tuple<int, int, int>> tabou(std::list<tuple<int, int, int>>* points) {
    
    list<tuple<int, int, int>> solutionGlobale = {};
    list<tuple<int, int, int>> solutionLocale = {};
    list<tuple<int, int, int>> listvoisins = *points;
    list<tuple<int, int, int, int>> listTabou = {};
	int iterationWithoutAmelioration = 0;

	while (iterationWithoutAmelioration < 100) {
        solutionLocale = maximize(&solutionLocale, &listTabou, &listvoisins);
		if (totalHeight(&solutionGlobale) < totalHeight(&solutionLocale)) {
			solutionGlobale = solutionLocale;
			iterationWithoutAmelioration = 0;
		}
		else {
			iterationWithoutAmelioration += 1;
		}
	}
	cout << totalHeight(&solutionGlobale) << endl;
    return solutionGlobale;
}
#endif


//int main() {
//    std::list<tuple<int, int, int>> points = generatePoints("./Exemplaires/b100_2.txt");
//	cout << "hi" << endl;
//    int height = tabou(&points);
//    //std::list<tuple<int, int, int>> tower = vorace(&points);
//
//    cout << height << endl;
//
//    //list<tuple<int, int, int>> tower = dynamicProgramming(&points);
//    //for (tuple<int, int, int> box : tower) {
//    //    cout << get<0>(box) << " " << get<1>(box) << " " << get<2>(box) << endl;
//    //}
//    return 0;
//}