#ifndef VORACE_H
#define VORACE_H
#include <list>
#include <tuple>
#include "utils.h"

using namespace std;

list<tuple<int, int, int>> vorace(std::list<tuple<int, int, int>>* points) {
    points->sort(sortSurface);
    list<tuple<int, int, int>> tour;
    for (std::list<tuple<int, int, int>>::iterator it = points->begin(); it != points->end(); ++it) {
        if (isLegal(*it, &tour))
        {
            tour.push_back(*it);
        }
    }

    return tour;
}
#endif