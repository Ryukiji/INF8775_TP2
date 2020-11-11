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

// void execute(int argc, char* argv[]) {
// 	vector<string> algos = {"vorace", "progdyn", "tabou"};
// 	string algo = "";
// 	bool printBlocs = false;
// 	bool printTime = false;
// 	list<tuple<int,int,int>> points;
// 	for (int i = 0; i < argc; i++) {
// 		string arg(argv[i]);
// 		cout << arg << endl;
// 		if (!strcmp(argv[i],  "vorace")) {
// 			algo = algos[0];
// 		}
// 		else if (!strcmp(argv[i],  "progdyn")) {
// 			algo = algos[1];
// 		}
// 		else if (!strcmp(argv[i],  "tabou")) {
// 			algo = algos[0];
// 		}
// 		else if (arg.find(".txt") != string::npos) {
// 			points = generatePoints(arg);

// 		}
// 		else if (!strcmp(argv[i], "-p")) {
// 			printBlocs = true;
// 		}
// 		else if (!strcmp(argv[i], "-t")) {
// 			printTime = true;
// 		}
// 	}

// 	if (algo == algos[0]) {
// 		clock_t tStart = clock();
//     	list<tuple<int,int,int>> tower = vorace(&points);
// 		if (printTime) {
//     		cout << (clock() - tStart)/CLOCKS_PER_SEC;
// 		}
// 		if (printBlocs) {
//     		for (tuple<int,int,int> box : tower) {
//         		cout << get<0>(box) << " " << get<1>(box) << " " << get<2>(box) << endl;
//     		}
// 		}
// 	}
// 	else if (algo == algos[1]) {
// 		clock_t tStart = clock();
//     	list<tuple<int,int,int>> tower = dynamicProgramming(&points);
// 		if (printTime) {
//     		cout << (clock() - tStart)/CLOCKS_PER_SEC;
// 		}
// 		if (printBlocs) {
//     		for (tuple<int,int,int> box : tower) {
//         		cout << get<0>(box) << " " << get<1>(box) << " " << get<2>(box) << endl;
//     		}
// 		}
// 	}
// 	else if (algo == algos[2]) {
// 		clock_t tStart = clock();
//     	list<tuple<int,int,int>> tower = tabou(&points);
// 		if (printTime) {
//     		cout << (clock() - tStart)/CLOCKS_PER_SEC;
// 		}
// 		if (printBlocs) {
//     		for (tuple<int,int,int> box : tower) {
//         		cout << get<0>(box) << " " << get<1>(box) << " " << get<2>(box) << endl;
//     		}
// 		}
// 	}
// }

// int main() {
// 	//std::list<tuple<int, int, int>> points = {make_tuple(4, 6, 7), make_tuple(6, 4, 7), make_tuple(7, 4, 6), make_tuple(1, 2, 3), make_tuple(2, 1 ,3), make_tuple(3, 1 ,2), make_tuple(4, 5, 6), make_tuple(5, 4, 6), make_tuple(6, 4 ,5), make_tuple(10, 12, 32), make_tuple(12, 10, 32), make_tuple(32, 10, 12)};
//    std::list<tuple<int, int, int>> points = generatePoints("../Exemplaires/b100_1.txt");
//    list<tuple<int, int, int>> tower = tabou(&points);
//    //std::list<tuple<int, int, int>> tower = vorace(&points);

//    for (tuple<int, int, int> box : tower) {
//       cout << get<0>(box) << " " << get<1>(box) << " " << get<2>(box) << endl;
//    }

//    //list<tuple<int, int, int>> tower = dynamicProgramming(&points);
//    //for (tuple<int, int, int> box : tower) {
//    //    cout << get<0>(box) << " " << get<1>(box) << " " << get<2>(box) << endl;
//    //}
//    return 0;
// }

int main(int argc, char *argv[]) {
	//execute(argc, argv);
	string exemplaires_path = "../Exemplaires/";
 	for (const auto & file : fs::directory_iterator(exemplaires_path)) {
 		printf("exemplaire : %s, ", file.path().c_str());
 		list<tuple<int,int,int>> boxes = generatePoints(file.path());
 		clock_t tStart = clock();
		int max = vorace(&boxes);
 		printf("hauteur : %d, Time : %2fs\n", max, (double)(clock() - tStart)/CLOCKS_PER_SEC);
 
 	}
    return 0;
}
