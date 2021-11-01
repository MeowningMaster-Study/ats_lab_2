#include <fstream>
#include <vector>
#include <string>
using namespace std;

vector<string> read_file(string path) {
    ifstream fin(path);
    string buff;

    vector<string> lines;
    while(getline(fin, buff)) {
        lines.push_back(buff);
    }
    return lines;
}