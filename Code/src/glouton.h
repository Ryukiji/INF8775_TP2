#ifndef VORACE_H
#define VORACE_H
#include <iostream>
#include <list>
#include <tuple>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include "utils.h"

using namespace std;

int vorace(std::list<tuple<int, int, int>>* points) {
    points->sort(sortSurface);
    std::list<tuple<int, int, int>> tour;
    for (std::list<tuple<int, int, int>>::iterator it = points->begin(); it != points->end(); ++it) {
        if (isLegal(*it, &tour))
        {
            tour.push_back(*it);
        }
    }

    return totalHeight(&tour);
}
#endif