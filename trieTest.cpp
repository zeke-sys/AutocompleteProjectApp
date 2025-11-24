#include "trieTest.h"
#include "trieProject.h"

// Helper for printing results in a structured manner
void printResult(const string &testName, bool passed) {
    cout << (passed ? "[PASS] " : "[FAIL] ") << testName << "\n";
}

// Tests for insertion and search
void testInsertAndContains() {
    Trie trie;
    trie.insert("apple", 5);
    trie.insert("app", 2);
    trie.insert("application", 3);

    printResult("Contains apple", trie.contains("apple"));
    printResult("Contains app", trie.contains("app"));
    printResult("Contains application", trie.contains("application"));
    printResult("Missing word", !trie.contains("apples"));
}

// Validate that frequencies accumulate correctly
void testFrequencyAccumulation() {
    Trie trie;
    trie.insert("banana", 2);
    trie.insert("banana", 3); // total should be 5
    auto results = trie.predict("ban", 5);

    bool found = false;
    for (auto &r : results) {
        if (r.first == "banana" && r.second == 5) found = true;
    }
    printResult("Frequency accumulation", found);
}

// Test predictions (prefix-based)
void testPredict() {
    Trie trie;
    trie.insert("car", 2);
    trie.insert("cat", 5);
    trie.insert("carbon", 4);
    trie.insert("castle", 1);

    auto results = trie.predict("ca", 10);
    bool orderCorrect = (results[0].first == "cat" && results[0].second == 5);
    bool sizeCorrect = (results.size() == 4);

    printResult("Predict order by frequency", orderCorrect);
    printResult("Predict returns all matches", sizeCorrect);
}

// Test loading from a file which creates a small temp file
void testLoadFromFile() {
    const string fname = "temp_dict.txt";
    ofstream out(fname);
    out << "alpha 10\n";
    out << "beta 5\n";
    out << "alphabet 2\n";
    out.close();

    Trie trie;
    bool loaded = trie.loadFromFile(fname);
    bool hasAlpha = trie.contains("alpha");
    bool hasAlphabet = trie.contains("alphabet");

    printResult("Load file success", loaded);
    printResult("Contains alpha from file", hasAlpha);
    printResult("Contains alphabet from file", hasAlphabet);
    
    auto preds = trie.predict("a", 10);
    bool correctFreq = false;
    for (auto &r : preds) if (r.first == "alpha" && r.second == 10) correctFreq = true;
    printResult("Frequency from file correct", correctFreq);
    remove("tmp_dict.txt");
}

// Edge case: empty prefix and no matches
void testEmptyAndMissingCases() {
    Trie trie;
    trie.insert("dog", 3);
    auto results = trie.predict("cat", 5);
    bool empty = results.empty();

    printResult("Predict with missing prefix", empty);

    results = trie.predict("", 5);
    bool includesDog = false;
    for (auto &r : results) if (r.first == "dog") includesDog = true;
    printResult("Predict with empty prefix includes existing words", includesDog);
}