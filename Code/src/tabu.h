#ifndef TABU_H
#define TABU_H
#include <list>
#include <tuple>
#include "utils.h"

using namespace std;

int calculHeightCandidat(list<tuple<int, int, int>>* localSolution,
                         tuple<int, int, int> bloc) {
    list<tuple<int, int, int>> candidate = *localSolution;
    int solutionHeight = totalHeight(localSolution);
    int RemovedblocHeight = 0;
    int posIndexMaxFound = 0;

    posIndexMaxFound = findHighestFittingIndex(candidate, &bloc);

    list<tuple< int, int, int >>::iterator it1 = candidate.begin();
    advance(it1, posIndexMaxFound);

    for (int i = posIndexMaxFound + 1; i < candidate.size(); i++) {
        if (!canBlockFit(*it1, bloc)) {
            // Enlever de la tour
            RemovedblocHeight = RemovedblocHeight + get<0>(*it1);
            ++it1;
        }
        else
            break;
    }

    solutionHeight = solutionHeight + get<0>(bloc) - RemovedblocHeight;
    return solutionHeight;
}



list<tuple<int, int, int>> fitVoisinsInSolution(list<tuple<int, int, int>>* localSolution, list<tuple<int, int, int>>* blocsRemoved, tuple<int, int, int> bloc) {
    list<tuple<int, int, int>> candidate = *localSolution;
    int posIndexMaxFound = 0;

    posIndexMaxFound = findHighestFittingIndex(candidate, &bloc);

    list<tuple< int, int, int >>::iterator it1 = candidate.begin();
    advance(it1, posIndexMaxFound);
    if (candidate.size() == 0) {
        candidate.push_back(bloc);
    }
    else {
        candidate.insert(it1, bloc);
    }

    for (int i = posIndexMaxFound + 1; i < candidate.size(); i++) {
        if (!canBlockFit(*it1, bloc)) {
            // Enlever de la tour
            blocsRemoved->push_back(*it1);
            candidate.erase(it1);
            it1 = candidate.begin();
            advance(it1, posIndexMaxFound + 1);
            //cout << "hi" << endl;
            --i;
        }
        else
            break;
    }
    return candidate;
}

list<tuple<int, int, int>> deleteFromTabou(list<tuple<int, int, int, int>>* tabuList) {
    list<tuple<int, int, int>> freeNeighbors = {};
    list<tuple<int, int, int, int>>::iterator it = tabuList->begin();
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
    for (tuple<int, int, int> bloc : blocsRemovedFinal) {
        tabuList->push_back(make_tuple(get<0>(bloc), get<1>(bloc), get<2>(bloc), rand() % (10 - 7 + 1) + 7));
    }
}

list<tuple<int, int, int>> maximize(list<tuple<int, int, int>>* solutionLocal,
                                    list<tuple<int, int, int, int>>* listTabou,
                                    list<tuple<int, int, int>>* listOfNeighbors) {
    list<tuple<int, int, int>> solutionMaximized = {};
    list<tuple<int, int, int>> blocksRemovedFinal = {};
    tuple<int, int, int> maximizingBlocs;
    int newTotalHeightMax = 0;

    for (tuple<int, int, int> bloc : *listOfNeighbors) {
        list<tuple<int, int, int>> solutionCandidate;
        int newTotalHeight = calculHeightCandidat(solutionLocal, bloc);

        if (newTotalHeight > newTotalHeightMax) {
            newTotalHeightMax = newTotalHeight;
            maximizingBlocs = bloc;
        }

    }

    solutionMaximized = fitVoisinsInSolution(solutionLocal, &blocksRemovedFinal, maximizingBlocs);
    if (blocksRemovedFinal.size()) {
        addToTabou(listTabou, blocksRemovedFinal);
    }
    list<tuple<int, int, int>> voisinsLibre = deleteFromTabou(listTabou);
    if (voisinsLibre.size()) {
        for (tuple<int, int, int> bloc : voisinsLibre) {
            listOfNeighbors->push_back(bloc);
        }
    }
    if (true) {
        listOfNeighbors->remove(maximizingBlocs);
    }
    if (solutionMaximized.size()) {
        solutionLocal = &solutionMaximized;
    }

    return solutionMaximized;
}

list<tuple<int, int, int>> tabou(std::list<tuple<int, int, int>>* points) {
    
    list<tuple<int, int, int>> globalSolution = {};
    list<tuple<int, int, int>> localSolution = {};
    list<tuple<int, int, int>> listOfNeighbors = *points;
    list<tuple<int, int, int, int>> listTabou = {};
	int iterationWithoutAmelioration = 0;

	while (iterationWithoutAmelioration < 100) {
        localSolution = maximize(&localSolution, &listTabou, &listOfNeighbors);
		if (totalHeight(&globalSolution) < totalHeight(&localSolution)) {
			globalSolution = localSolution;
			iterationWithoutAmelioration = 0;
		}
		else {
			iterationWithoutAmelioration += 1;
		}
	}
    cout << totalHeight(&globalSolution) << endl;

    return globalSolution;
}
#endif