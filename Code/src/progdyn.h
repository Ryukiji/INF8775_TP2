#include <iostream>
#include <list>
#include <tuple>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

using namespace std;

int sortSurface(tuple<int,int,int> point1, tuple<int,int,int> point2) {
    return get<1>(point1) * get<2>(point1) > get<1>(point2) * get<2>(point2);
}

int reverseSortSurface(tuple<int,int,int> point1, tuple<int,int,int> point2) {
    return get<1>(point1) * get<2>(point1) < get<1>(point2) * get<2>(point2);
}

list<tuple<int,int,int>> dynamicProgramming(list<tuple<int,int,int>>* points) {
    points->sort(sortSurface);
    int n = points->size();
    int height[n];
    map<tuple<int,int,int>, tuple<int,int,int>> blocs;
    list<tuple<int,int,int>>::iterator it = points->begin();
    for (int i = 0; i < n; i++) {
        height[i] = get<0>(*it);
        ++it;
    }
    list<tuple<int,int,int>>::iterator it1 = points->begin();
    for (int i = 1; i < n; i++ ) {
        it1++;
        list<tuple<int,int,int>>::iterator it2 = points->begin();
        for (int j = 0; j < i; j++ ) {
            if ( get<1>(*it1) < get<1>(*it2) && 
                get<2>(*it1) < get<2>(*it2) && 
                height[i] < height[j] + get<0>(*it1) 
            )
            {
                height[i] = height[j] + get<0>(*it1);
                blocs[*it1] = *it2;
            }
            it2++;
        }
    }

    std::list<tuple<int,int,int>> key, answer;
 /*   for(std::map<tuple<int,int,int>, tuple<int,int,int>>::iterator it = blocs.begin(); it != blocs.end(); ++it) {
        key.push_back(it->first);
    }
    key.sort(reverseSortSurface);
    tuple<int,int,int> currentBloc = *key.begin();
    while (blocs.count(currentBloc)) {
        answer.push_back(currentBloc);
        currentBloc = blocs[currentBloc];
    }
    answer.push_back(currentBloc);
    answer.sort(sortSurface);
*/
    int max = -1; 
    for ( int i = 0; i < n; i++ ) 
        if ( max < height[i] ) 
            max = height[i];
    cout << max << endl;

    return answer;
}