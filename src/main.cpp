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

// порівнює результати виконання тестів
bool compare_results(search_result& a, search_result& b) {
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
    // зчитуємо тест та словник за файлів
    string text = join(read_file("../assets/text.txt"), '\n');
    vector<string> dictionary = read_file("../assets/dictionary.txt");

    search_result dumb_search_res, aho_corasik_search_res;
    // виконуємо простий пошук
    cout << measure_nanoseconds([&](){ dumb_search_res = dumb_search(text, dictionary); }) << '\n';

    // будуємо автомат пошуку та використовуємо його
    auto dictionary_trie = dictionary_automaton(dictionary);
    cout << measure_nanoseconds([&](){ aho_corasik_search_res = aho_corasik_search(text, dictionary_trie); }) << '\n';

    // порівнюємо результати
    sort(dumb_search_res.begin(), dumb_search_res.end());
    sort(aho_corasik_search_res.begin(), aho_corasik_search_res.end());
    assert(compare_results(dumb_search_res, aho_corasik_search_res));
}