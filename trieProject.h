#ifndef TRIE_PROJECT_H
#define TRIE_PROJECT_H

#include <iostream>
#include <memory>
#include <map>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <cctype>

using namespace std;

struct TrieNode {
    bool is_end = false;
    int freq = 0;
    map<char, unique_ptr<TrieNode>> children;
};

class Trie {
public:
    Trie();
    void insert(const string &word, int frequency = 1);
    bool contains(const string &word) const;
    vector<pair<string,int>> predict(const string &prefix, size_t limit = 10) const;
    bool loadFromFile(const string &filename);
private:
    unique_ptr<TrieNode> root;
    const TrieNode* findNode(const string &s) const;
    static void toLowerInLine(string &s);
    static void trim(string &s);
};

void printHelp();

#endif // TRIE_PROJECT_H