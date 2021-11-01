#pragma once
#include <vector>
#include <string>
using namespace std;

vector<size_t> dumb_search(string& text, vector<string>& dictionary) {
    vector<size_t> entries;
    for (string word : dictionary) {
        size_t i = 0;
        while ((i = text.find(word, i)) != string::npos) {
            entries.push_back(i);
            i += word.length();
        }
    }
    return entries;
}