#include "trieProject.h"

Trie::Trie() : root(make_unique<TrieNode>()) {}

// Insert a word with optional frequency (default 1). If word already present, frequency is accumulated.
void Trie::insert(const string &word, int frequency) {
    TrieNode *node = root.get();
    for (char c : word) {
        if (node->children.find(c) == node->children.end())
            node->children[c] = make_unique<TrieNode>();
        node = node->children[c].get();
    }
    node->is_end = true;
    node->freq += frequency;
}

// Return whether exact word exists in trie
bool Trie::contains(const string &word) const {
    const TrieNode *node = findNode(word);
    return node && node->is_end;
}

// Given a prefix, return up to 'limit' suggestions sorted by frequency desc then lexicographically
vector<pair<string,int>> Trie::predict(const string &prefix, size_t limit) const {
    vector<pair<string,int>> results;
    const TrieNode *node = findNode(prefix);
    if (!node) return results;

    // DFS stack: pair(node pointer, current suffix)
    vector<pair<const TrieNode*, string>> stack;
    stack.emplace_back(node, string());

    while (!stack.empty()) {
        auto [nptr, suffix] = stack.back();
        stack.pop_back();

        if (nptr->is_end) {
            results.emplace_back(prefix + suffix, nptr->freq);
        }

        // iterate children in reverse order so that when we pop we get lexicographic order after sorting ties
        for (auto it = nptr->children.rbegin(); it != nptr->children.rend(); ++it) {
            stack.emplace_back(it->second.get(), suffix + it->first);
        }
    }

    // sort by frequency descending, then lexicographically ascending
    sort(results.begin(), results.end(), [](const pair<string,int> &a, const pair<string,int> &b) {
        if (a.second != b.second) return a.second > b.second;
        return a.first < b.first;
    });

    if (results.size() > limit) results.resize(limit);
    return results;
}

// Load dictionary file: each line either "word" or "word freq"
bool Trie::loadFromFile(const string &filename) {
    ifstream in(filename);
    if (!in.is_open()) return false;
    string line;
    while (getline(in, line)) {
        trim(line);
        if (line.empty()) continue;
        istringstream iss(line);
        string word;
        int freq = 1;
        iss >> word;
        if (iss >> freq) {
            // ok
        }
        toLowerInLine(word);
        insert(word, freq);
    }
    return true;
}


const TrieNode* Trie::findNode(const string &s) const {
    const TrieNode *node = root.get();
    for (char c : s) {
        auto it = node->children.find(c);
        if (it == node->children.end()) return nullptr;
        node = it->second.get();
    }
    return node;
}

// utility helpers
void Trie::toLowerInLine(string &s) {
    for (char &c : s) c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
}

void Trie::trim(string &s) {
    size_t i = 0;
    while (i < s.size() && isspace(static_cast<unsigned char>(s[i]))) ++i;
    size_t j = s.size();
    while (j > i && isspace(static_cast<unsigned char>(s[j-1]))) --j;
    s = s.substr(i, j - i);
}

void printHelp() {
    cout << "Commands:\n";
    cout << "  add <word> [freq]      - insert a word (freq default 1)\n";
    cout << "  predict <prefix> [n]   - show top n predictions (default 10)\n";
    cout << "  search <word>          - check if exact word exists\n";
    cout << "  load <filename>        - load words from file (word [freq] per line)\n";
    cout << "  test                   - run built-in unit tests\n";
    cout << "  exit                   - quit\n";
    cout << "  help                   - this message\n";
    cout.flush();
}

// --- end of trieProject file ---


