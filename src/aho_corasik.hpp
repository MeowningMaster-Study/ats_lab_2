#pragma once
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

const int k = 256;
struct Vertex {
    int next[k];
    bool leaf = false;
    int p = -1;
    char pch;
    int link = -1;
    int go[k];
    string word;

    Vertex(int p, char ch) : p(p), pch(ch) {
        fill(begin(next), end(next), -1);
        fill(begin(go), end(go), -1);
    }
};

struct dictionary_automaton {
    vector<Vertex> t = {{-1, 0}};

    void fill(vector<string>& dictionary) {
        for (string word : dictionary) {
            add_word(word);
        }
    }

    dictionary_automaton(vector<string>& dictionary) {
        fill(dictionary);
    }
    
    void add_word(string const& s) {
        int v = 0;
        for (char ch : s) {
            if (t[v].next[ch] == -1) {
                t[v].next[ch] = t.size();
                t.emplace_back(v, ch);
            }
            v = t[v].next[ch];
        }
        t[v].leaf = true;
        t[v].word = s;
    }

    int get_link(int v) {
        if (t[v].link == -1) {
            if (v == 0 || t[v].p == 0)
                t[v].link = 0;
            else
                t[v].link = go(get_link(t[v].p), t[v].pch);
        }
        return t[v].link;
    }

    int go(int v, char ch) {
        if (t[v].go[ch] == -1) {
            if (t[v].next[ch] != -1)
                t[v].go[ch] = t[v].next[ch];
            else
                t[v].go[ch] = v == 0 ? 0 : go(get_link(v), ch);
        }
        return t[v].go[ch];
    } 
};

search_result aho_corasik_search(const string& text, dictionary_automaton d) {
    search_result entries;
    auto v = 0;
    for (size_t i = 0; i < text.length(); i++) {
        char c = text[i];
        v = d.go(v, c);
        for (int u = v; u != 0; u = d.get_link(u)) {
            if (d.t[u].leaf) {
                string word = d.t[u].word;
                size_t len = word.length();
                size_t pos = i - len + 1;

                entries.push_back(make_tuple(pos, word));
            }
        }
    }
    return entries;
}