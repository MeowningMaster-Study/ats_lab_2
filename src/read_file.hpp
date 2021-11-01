#include <fstream>
#include <vector>
#include <string>
#include "to_lower.hpp"
using namespace std;

vector<string> read_file(string path) {
    ifstream fin(path);
    string buff;

    vector<string> lines;
    while(getline(fin, buff)) {
        lines.push_back(to_lower(buff));
    }
    return lines;
}