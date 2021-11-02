#pragma once
#include <array>
#include <vector>
#include <string>
using namespace std;

const size_t k = 26;
struct vertex {
    array<vertex*, k> to = {0}, go = {0};
    vertex* link = 0;
    vertex* p;
    size_t pch, len;
    bool leaf = false;

    vertex(size_t _pch, vertex* _p, size_t _len): pch(_pch), p(_p), len(_len) {}
};

struct dictionary_automaton {
    vertex* root;

    void init() {
        root = new vertex(-1, 0, 0);
    }

    dictionary_automaton() {
        init();
    }

    void fill(vector<string>& dictionary) {
        for (string word : dictionary) {
            add_word(word);
        }
    }

    dictionary_automaton(vector<string>& dictionary) {
        init();
        fill(dictionary);
    }
    
    void add_word(string& word) {
        vertex* v = root;
        for (char ch : word) {
            size_t c = ch - 'a';
            if (!v->to[c]) {
                v->to[c] = new vertex(c, v, v->len + 1);
            }  
            v = v->to[c];
        }
        v->leaf = true;
    }

    vertex* link(vertex* v) {
        if (!v->link) {
            if (v == root || v->p == root) {
                v->link = root;
            } else {
                v->link = go(link(v->p), v->pch + 'a');
            }
        }
        return v->link;
    }

    vertex* go(vertex* v, char ch) {
        if (ch < 'a' || ch > 'z') {
            return root;
        }

        size_t c = ch - 'a';
        if (!v->go[c]) {
            if (v->to[c]) {
                v->go[c] = v->to[c];
            } else if (v == root) {
                v->go[c] = root;
            } else {
                v->go[c] = go(link(v), c);
            }     
        }
        return v->go[c];
    }
};

search_result aho_corasik_search(const string& text, dictionary_automaton dictionary) {
    search_result entries;
    vertex* v = dictionary.root;
    for (size_t i = 0; i < text.length(); i++) {
        v = dictionary.go(v, text[i]);
        vertex* x = v;
        while (x->leaf) {
            size_t pos = i - x->len + 1;
            entries.push_back(make_tuple(pos, text.substr(pos, x->len)));
            x = dictionary.link(x);
        }
    }
    return entries;
}