// include libraries here (STL not allowed)
#include <iostream>
#include <string>
#include "tokenize.h"
#include <fstream>
#include <sstream>
#include <cctype> // for std::isalpha


int main()
{
    Tokenize theTokenize;

    while (!std::cin.eof())
    {
        std::string command;
        getline(std::cin, command);
        if (command[0] == 'c')
        {
            size_t size;
            size = std::stoi(command.substr(7));
            theTokenize.create(size);
            std::cout << "success" << std::endl;
            
        }
        else if (command[0] == 'i')
        {
            std::string word;
            word = command.substr(7);
            if (theTokenize.isAlphabetic(word) && theTokenize.insert(word))
            {
                std::cout << "success" << std::endl;
            }
            else
            {
                std::cout << "failure" << std::endl;
            }
        }
        else if (command[0] == 't'&& command[4] == 'a')
        {
            std::string wordlist = command.substr(8);
            std::istringstream iss(wordlist);
            std::vector<std::string> words;
            std::string word;
            while (iss >> word)
            {
                words.push_back(word);
            }
            std::vector<int> tokens = theTokenize.tok_all(words);

            // Output the tokens
            for (int token : tokens)
            {
                std::cout << token << " ";
            }
            std::cout << std::endl;
        }
        else if (command[0] == 't')
        {
            std::string word;
            word = command.substr(4);
            int token = theTokenize.tok(word);
            if (token != -1)
            {
                std::cout << token << std::endl;
            }
            else
            {
                std::cout << "-1" << std::endl;
            }
        }
        else if (command[0] == 'l')
        {
            std::string filename;
            filename = command.substr(5);
            if (theTokenize.load(filename))
            {
                std::cout << "success" << std::endl;
            }
            else
            {
                std::cout << "failure" << std::endl;
            }
        }
        else if (command[0] == 'r' && command[4]=='a')
        {   
            std::string tokenString = command.substr(8);
            std::istringstream iss(tokenString);
            std::vector<int> tokens;
            int token;
            while (iss >> token)
            {
                tokens.push_back(token);
            }

            // Use ret_all to retrieve the words for the given tokens
            std::vector<std::string> words = theTokenize.ret_all(tokens);

            // Output the words
            for (const std::string &word : words)
            {
                std::cout << word << " ";
            }
            std::cout << std::endl;
        }
        else if (command[0]=='r')
        {
            int token;
            token = std::stoi(command.substr(4));
            std::string word = theTokenize.ret(token);
            if (word != "N/A")
            {
                std::cout << word << std::endl;
            }
            else
            {
                std::cout << "N/A" << std::endl;
            }
        }
       
        
        else if (command[0] == 'p')
        {
            int k;
            k = std::stoi(command.substr(6));
            if (!(k>=0 && k<theTokenize.wordsToTokens->m)) continue;
            else theTokenize.print(k);
        }
        else if (command[0] == 'e')
        {
            break;
        }
    }
}
