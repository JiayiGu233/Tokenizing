// implement classes' member functions here...
#include "tokenize.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

// Constructor for Tokenize
Tokenize::Tokenize() {
    wordsArray.push_back("");
    wordsToTokens = nullptr;
}

// Destructor for Tokenize
Tokenize::~Tokenize() {
    delete wordsToTokens;
}

bool Tokenize::find(const std::string& word) const {
    if (!wordsToTokens) return false;  // 确保wordsToTokens已初始化
    for (const auto& pair : wordsToTokens->table[wordsToTokens->hash(word)]) {
        if (word == pair.first) return true;
    }
    return false;
}


void Tokenize::create(size_t size) {
    delete wordsToTokens; // Clean up existing hash table if any
    wordsToTokens = new HashTable<std::string, int>(size);
}

bool Tokenize::insert(const std::string& word) {
    if (detector()) wordsToTokens->resize();
    if ((!find(word)) && isAlphabetic(word)) {
        wordsArray.push_back(word);
        return wordsToTokens->insert(word, wordsArray.size()-1);
    }
    return false;
}

bool Tokenize::load(const std::string& filename) {
    std::ifstream file(filename);
    std::string word;
    bool inserted = false;
    while (file >> word) {
        if (insert(word)) {
            inserted = true;
        }
    }
    return inserted;
}

int Tokenize::tok(const std::string& word) const {
    if (!find(word)) return -1;
    return wordsToTokens->get(word);
}

std::string Tokenize::ret(int token) const {
    if (token > 0 && token < wordsArray.size()) {
        return wordsArray[token];
    }
    return "N/A";
}

std::vector<int> Tokenize::tok_all(const std::vector<std::string>& words) const {
    std::vector<int> tokens;
    for (const std::string& word : words) {
        tokens.push_back(tok(word));
    }
    return tokens;
}

std::vector<std::string> Tokenize::ret_all(const std::vector<int>& tokens) const {
    std::vector<std::string> words;
    for (int token : tokens) {
        words.push_back(ret(token));
    }
    return words;
}

void Tokenize::print(int k) const {
    wordsToTokens->print(k);
}