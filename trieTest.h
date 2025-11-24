#ifndef TRIE_TEST_H
#define TRIE_TEST_H

#include <string>

void printResult(const std::string &testName, bool passed);
void testInsertAndContains();
void testFrequencyAccumulation();
void testPredict();
void testLoadFromFile();
void testEmptyAndMissingCases();

#endif