#include <iostream>
#include <vector>
#include <string>
#include "read_file.hpp"
#include "join.hpp"
#include "timer.hpp"
#include "dumb_search.hpp"
using namespace std;

int main() {
    string text = join(read_file("../assets/text.txt"), '\n');
    vector<string> dictionary = read_file("../assets/dictionary.txt");

    cout << measure_nanoseconds([&](){ dumb_search(text, dictionary); });
}