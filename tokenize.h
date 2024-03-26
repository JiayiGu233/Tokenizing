#include <string>
#include <forward_list>
#include <utility>
#include <vector>
#include <iostream>

template<typename K, typename V>
class HashTable {
public:
    HashTable(size_t size) : m(size), table(new std::forward_list<std::pair<K, V>>[size]) {}

    ~HashTable() {}

    bool insert(const K& key, const V& value) {
        size_t index = hash(key);
        table[index].emplace_front(key, value);
        return true;
    }

    V get(const K& key) const {
        size_t index = hash(key);
        for (const auto& pair : table[index]) {
            if (pair.first == key) {
                return pair.second;
            }
        }
    }

    void print(int k) const {
        bool printed = false;
        for (const auto& pair : table[k]) {
            if (std::cout << pair.first << " ") printed = true;
        }
        if (!printed) return;
        std::cout << std::endl;
    }

    size_t m; // Size of the hash table

    void resize() {
        auto oldSize = m;
        m = 2*m;
        std::forward_list<std::pair<K, V>>* newTable = new std::forward_list<std::pair<K, V>>[m];

        for (auto i=0; i<oldSize; i++) {
            for (auto pair: table[i]) insert(pair.first, pair.second);
        }

        auto temp = table;

        delete[] temp;
        table = newTable;
    }
private:
    std::forward_list<std::pair<K, V>>* table; // Dynamically allocated array for external chaining
    size_t hash(const std::string& str) const { // Changed to const method
        size_t ans = 0;
        for (char ch : str) { // Simplified loop
            ans = ans * 29 + ch;
        }
        return ans % m;
    }

    friend class Tokenize;
};

class Tokenize {
public:
    Tokenize();
    ~Tokenize();
    void create(size_t size);
    bool insert(const std::string& word);
    bool load(const std::string& filename);
    bool find(const std::string& word) const;
    int tok(const std::string& word) const;
    std::string ret(int token) const;
    std::vector<int> tok_all(const std::vector<std::string>& words) const;
    std::vector<std::string> ret_all(const std::vector<int>& tokens) const;
    void print(int k) const;
    HashTable<std::string, int>* wordsToTokens; // Hash table for words ⇒ tokens mapping

    bool isAlphabetic(const std::string &word)
    {
        for (char ch : word)
        {
            if (!std::isalpha(static_cast<unsigned char>(ch)))
                return false;
        }
        return true;
    }
    bool detector() {
        return ((wordsArray.size()-1)/wordsToTokens->m>=0.8);
    }
private:
    std::vector<std::string> wordsArray; // Array for tokens ⇒ words mapping
};