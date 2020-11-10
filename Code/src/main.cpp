#include <iostream>
#include <list>
#include <tuple>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include "progdyn.h"

using namespace std;

list<tuple<int,int,int>> generatePoints(string fileName) {
    string line;
    ifstream myfile (fileName);
    list<tuple<int, int, int>> boxes;
    if (myfile.is_open()) {
        while ( getline (myfile,line) ) {
            vector<int> coords;
            stringstream ss(line);
            string item;
            while (getline(ss, item, ' ' )) {
                coords.push_back(stoi(item));
            }
            boxes.push_back({make_tuple(coords[0], coords[1], coords[2])});
        }
        myfile.close();
    }

    return boxes; 
}

int main() {
    list<tuple<int,int,int>> points = generatePoints("../Exemplaires/b100_1.txt");
    clock_t tStart = clock();
    list<tuple<int,int,int>> tower = dynamicProgramming(&points);
    printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
/*    for (tuple<int,int,int> box : tower) {
        cout << get<0>(box) << " " << get<1>(box) << " " << get<2>(box) << endl;
    } */
    return 0;
}
