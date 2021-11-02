#pragma once
#include <vector>
#include <string>
#include "search_result.hpp"
using namespace std;

search_result dumb_search(string& text, vector<string>& dictionary) {
    search_result entries;
    for (string word : dictionary) {
        size_t i = 0;
        while ((i = text.find(word, i)) != string::npos) {
            entries.push_back(make_tuple(i, word));
            i += word.length();
        }
    }
    return entries;
}