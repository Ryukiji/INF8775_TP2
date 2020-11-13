#ifndef UTILS_H
#define UTILS_H
#include <list>
#include <tuple>

using namespace std;

int sortSurface(tuple<int,int,int> point1, tuple<int,int,int> point2) {
    return get<1>(point1) * get<2>(point1) > get<1>(point2) * get<2>(point2);
}

int reverseSortSurface(tuple<int,int,int> point1, tuple<int,int,int> point2) {
    return get<1>(point1) * get<2>(point1) < get<1>(point2) * get<2>(point2);
}

int totalHeight(std::list<tuple<int, int, int>>* points) {
    int height = 0;

    for (std::list<tuple<int, int, int>>::iterator it = points->begin(); it != points->end(); ++it) {
        height += get<0>(*it);
    }

    return height;
}

bool isLegal(tuple<int, int, int> b, std::list<tuple<int, int, int>>* tour) {
    tuple<int, int, int> s;

    if (tour->size() == 0) {
        return true;
    }
    else if (tour->size() > 0) {
        list<tuple<int, int, int>>::iterator it = tour->end();
        it--;
        if (get<1>(*it) > get<1>(b) && get<2>(*it) > get<2>(b)) {
            return true;
        }
        else {
            return false;
        }
    }
    return true;
}

bool canBlockFit(tuple<int, int, int> topBlock, tuple<int, int, int> bottomBlock) {
    return get<1>(bottomBlock) > get<1>(topBlock) && get<2>(bottomBlock) > get<2>(topBlock);
}

int findHighestFittingIndex(list<tuple<int, int, int>>& towerBlocks, tuple<int, int, int>* block) {
    std::list<tuple<int, int, int>>::iterator it = towerBlocks.begin();
    for (int i = 0; i < towerBlocks.size(); ++i) {
        if (!canBlockFit(*block, *it)) {
            return i;
        }
        ++it;
    }
    return 0;
}

bool isTowerValid(list<tuple<int, int, int>> towerBlocks) {
    tuple<int, int, int> lastRemembered = { make_tuple(0, 0, 0) };
    for (std::list<tuple<int, int, int>>::iterator it = towerBlocks.begin(); it != towerBlocks.end(); ++it) {
        if (lastRemembered != make_tuple(0, 0, 0)) {
            if (!canBlockFit(*it, lastRemembered)) {
                return false;
            }
        }
        lastRemembered = *it;
    }
    return true;
}

#endif