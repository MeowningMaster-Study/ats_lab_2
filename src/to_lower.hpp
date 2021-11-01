#pragma once
#include <string>
using namespace std;

char to_lower(char ch) {
    if (ch <= 'Z' && ch >= 'A') {
        return ch - ('Z' - 'z');
    }
    return ch;
}

string to_lower(string s) {
    string res = "";
    for (char ch : s) {
        res += to_lower(ch);
    }
    return res;
}