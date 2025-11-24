# AutocompleteProjectApp

For this project, I developed a Word Prediction/Search Autocomplete application. I made use of the Trie data structure to insert/store a dictionary of words and provide word suggestions. The predictions are found based on characters entered without having to scan the entire dictionary because each successive character directly narrows the search path through the tree.

The implementation involved the following components:
  - Trie Node Structure
      - A map of child nodes for each possible character (26 alphabet letters)
      - A boolean flag indicating whether the node represents the end of a valid word
      - A frequency counter for word prediction ranking
  - Core Operations
      - Insertion to add new words to the Trie from a given dictionary or user input
      - Search to check if a word exists in the Trie
      - Prefix Query where given a prefix, the user is able to retrieve all words that start with that prefix
  - Prediction Logic
      - Following user input of a prefix, a depth-first or breadth-first traversal of the Trie collects all completions that share the same prefix
      - In the frequency table, results are ranked by likelihood
  - User Interface
      - Simple command-line interface, including a menu with options, allowing users to interact with the application

------------------------------

To compile, build with the following commands:
  - g++ trieProject.cpp trieMain.cpp trieTest.cpp -o trieProgram
  - ./trieProgram
  - 
------------------------------

The interactive menu commands will look like the following:
  "Trie Autocomplete (type 'help' for commands)
  > help
  Commands:
    add <word> [freq]      - insert a word (freq default 1)
    predict <prefix> [n]   - show top n predictions (default 10)
    search <word>          - check if exact word exists
    load <filename>        - load words from file (word [freq] per line)
    test                   - run built-in unit tests
    exit                   - quit
    help                   - this message
  > > test
  === Running Trie Unit Tests ===
  [PASS] Contains apple
  [PASS] Contains app
  [PASS] Contains application
  [PASS] Missing word
  [PASS] Frequency accumulation
  [PASS] Predict with missing prefix
  [PASS] Predict with empty prefix includes existing words
  === Tests Complete ===
  Type 'help' for commands> > "

ENJOY!

  



