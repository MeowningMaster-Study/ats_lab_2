#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>
#include "read_file.hpp"
#include "join.hpp"
#include "timer.hpp"
#include "dumb_search.hpp"
#include "aho_corasik.hpp"
using namespace std;

bool compare_results(vector<size_t>& a, vector<size_t> b) {
    if (a.size() != b.size()) {
        return false;
    }
    for (int i = 0; i < a.size(); i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    string text = join(read_file("../assets/text.txt"), '\n');
    vector<string> dictionary = read_file("../assets/dictionary.txt");

    vector<size_t> dumb_search_res, aho_corasik_search_res;
    cout << measure_nanoseconds([&](){ dumb_search_res = dumb_search(text, dictionary); }) << '\n';
    cout << measure_nanoseconds([&](){ aho_corasik_search_res = aho_corasik_search(text, dictionary_automaton(dictionary)); }) << '\n';
    sort(dumb_search_res.begin(), dumb_search_res.end());
    assert(compare_results(dumb_search_res, aho_corasik_search_res));
}