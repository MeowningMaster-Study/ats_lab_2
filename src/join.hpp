#pragma once
#include <vector>
#include <string>
using namespace std;

// об'єднує строки в одну
string join(const vector<string>& v, char c) {
    string s = "";
    auto i = v.begin();
    s += *i;
    for (i++; i != v.end(); i++) {
        s += c + *i;
    }
    return s;
}