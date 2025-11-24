// Connecting to project and test files
#include "trieProject.h"
#include "trieTest.h"


// Interactive main
int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.setf(ios::unitbuf); // flush cout after every insertion

    Trie trie;
    cout << "Trie Autocomplete (type 'help' for commands)\n";

    string line;
    while (true) {
        cout << "> ";
        if (!getline(cin, line)) break;
        istringstream iss(line);
        string cmd;
        if (!(iss >> cmd)) continue;

        // normalize command to lower
        for (char &c : cmd) c = static_cast<char>(tolower(static_cast<unsigned char>(c)));

        if (cmd == "help") {
            printHelp();
        } else if (cmd == "exit" || cmd == "quit") {
            break;
        } else if (cmd == "add") {
            string word;
            int freq = 1;
            if (!(iss >> word)) {
                cout << "Usage: add <word> [freq]\n";
                continue;
            }
            if (iss >> freq) { /* parsed */ }
            for (char &c : word) c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
            trie.insert(word, freq);
            cout << "Added: " << word << " (+" << freq << ")\n";
        } else if (cmd == "search") {
            string word;
            if (!(iss >> word)) {
                cout << "Usage: search <word>\n";
                continue;
            }
            for (char &c : word) c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
            cout << (trie.contains(word) ? "Found\n" : "Not found\n");
        } else if (cmd == "predict") {
            string prefix;
            size_t limit = 10;
            if (!(iss >> prefix)) {
                cout << "Usage: predict <prefix> [n]\n";
                continue;
            }
            if (iss >> limit) { /* parsed */ }
            for (char &c : prefix) c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
            auto results = trie.predict(prefix, limit);
            if (results.empty()) {
                cout << "No completions.\n";
            } else {
                for (size_t i = 0; i < results.size(); ++i) {
                    cout << (i+1) << ". " << results[i].first << " (freq=" << results[i].second << ")\n";
                }
            }
        } else if (cmd == "test") {
            cout << "=== Running Trie Unit Tests ===\n";
            testInsertAndContains();
            testFrequencyAccumulation();
            testPredict;
            testLoadFromFile;
            testEmptyAndMissingCases();
            cout << "=== Tests Complete ===\n";
            cout << "Type 'help' for commands";
        } 
        else if (cmd == "load") {
            string filename;
            if (!(iss >> filename)) {
                cout << "Usage: load <filename>\n";
                continue;
            }
            if (trie.loadFromFile(filename)) {
                cout << "Loaded from " << filename << "\n";
            } else {
                cout << "Failed to open " << filename << "\n";
            }
        } else {
            cout << "Unknown command. Type 'help'.\n";
        }
        cout << "> " << flush; // making sure a new prompt always shows after every command
    }

    cout << "Goodbye.\n";
    cout << "Press Enter to exit...";
    cin.get();
    return 0;
}