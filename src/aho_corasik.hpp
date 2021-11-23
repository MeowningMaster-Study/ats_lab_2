#pragma once
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

const int k = 256;
// вершина графу автомата
struct Vertex {
    int next[k]; // прямі переходи
    bool leaf = false; // чи э кінцем слова
    int p = -1; // батьківська вершина
    char pch; // символ переходу
    int link = -1; // суфіксне посилання
    int go[k]; // збережені переходи
    string word; // слово

    Vertex(int p, char ch) : p(p), pch(ch) {
        fill(begin(next), end(next), -1);
        fill(begin(go), end(go), -1);
    }
};

// автомат пошуку
struct dictionary_automaton {
    // спочатку має тільки кореневу вершину
    vector<Vertex> t = {{-1, 0}};

    // додавання словника
    void fill(vector<string>& dictionary) {
        for (string word : dictionary) {
            add_word(word);
        }
    }

    dictionary_automaton(vector<string>& dictionary) {
        fill(dictionary);
    }
    
    // додавання слова
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

    // ліниве обчислення суфіксного посилання
    int get_link(int v) {
        if (t[v].link == -1) {
            if (v == 0 || t[v].p == 0)
                t[v].link = 0;
            else
                t[v].link = go(get_link(t[v].p), t[v].pch);
        }
        return t[v].link;
    }

    // ліниве обчислення переходу
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

// проходження тексту та застосування автомату пошуку для знаходження слів словника
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