#include <iostream>
#include <list>
#include <tuple>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <filesystem>
#include "progdyn.h"
#include "tabu.h"
#include "glouton.h"

using namespace std;
namespace fs = std::filesystem;

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

void execute(int argc, char* argv[]) {
	vector<string> algos = {"vorace", "progdyn", "tabou"};
	string algo = "";
	bool printBlocs = false;
	bool printTime = false;
	list<tuple<int,int,int>> points;

	for (int i = 0; i < argc; i++) {
		string arg(argv[i]);
		if (!strcmp(argv[i],  "vorace")) {
			algo = algos[0];
		}
		else if (!strcmp(argv[i],  "progdyn")) {
			algo = algos[1];
		}
		else if (!strcmp(argv[i],  "tabou")) {
			algo = algos[0];
		}
		else if (arg.find(".txt") != string::npos) {
			points = generatePoints(arg);

		}
		else if (!strcmp(argv[i], "-p")) {
			printBlocs = true;
		}
		else if (!strcmp(argv[i], "-t")) {
			printTime = true;
		}
	}

    list<tuple<int,int,int>> tower = {};
    clock_t tStart = clock();
	if (algo == algos[0]) {
    	tower = vorace(&points);
	}
	else if (algo == algos[1]) {
    	tower = dynamicProgramming(&points);
	}
	else if (algo == algos[2]) {
        tower = tabou(&points);
	}
    if (printTime) {
        cout << ((double)(clock() - tStart)/CLOCKS_PER_SEC)*(1e3) << endl;
    }
    if (printBlocs) {
        for (tuple<int,int,int> box : tower) {
            cout << get<0>(box) << " " << get<1>(box) << " " << get<2>(box) << endl;
        }
    }
}

int main(int argc, char *argv[]) {
	execute(argc, argv);
    return 0;
}
