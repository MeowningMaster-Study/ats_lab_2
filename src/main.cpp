#include <iostream>
#include <vector>
#include <string>
#include "read_file.hpp"
#include "join.hpp"
#include "to_lower.hpp"
#include "timer.hpp"
#include "dumb_search.hpp"
#include "aho_corasik.hpp"
using namespace std;

int main() {
    string text = to_lower(join(read_file("../assets/text.txt"), '\n'));
    vector<string> dictionary = read_file("../assets/dictionary.txt");

    cout << measure_nanoseconds([&](){ dumb_search(text, dictionary); }) << '\n';
    cout << measure_nanoseconds([&](){ aho_corasik_search(text, dictionary_automaton(dictionary)); }) << '\n';
}