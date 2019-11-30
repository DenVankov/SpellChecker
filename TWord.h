//
// Created by dvankov on 11.06.2019.
//
#ifndef SPELLCHECKER_TWORD_H
#define SPELLCHECKER_TWORD_H

#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include <string.h>
#include <fstream>

/*
struct TWord{
    TWord(){};
    TWord(std::string &data, int64_t counting): word(data), counting(counting) {};
    std::string word;
    int64_t counting = 1;

std::map<std::string, TWord> next;
};
*/

class TWord{
public:
    TWord(){};
    TWord(std::string &data, int64_t counting):
        word(data), counting(counting) {};
    std::string word;
    int64_t counting = 1; // количество повторений слова
    std::map<std::string, TWord> next;
    ~TWord(){};
};

class Alphabet{
public:
    Alphabet();
    std::map<std::string, TWord> alpha; // словарь из строки и элемента словаря(слово)
    std::shared_ptr<TWord> Add_new_word(std::string &data);
    int64_t Size();
    double Number_of_pair(std::string &first, std::string &second);
    bool Save(std::ofstream &os);
    bool Load(std::map<std::string, TWord> &elem, std::ifstream &is);

    void Free_buff();
    void Clear();
    void Print();
    ~Alphabet(){};

private:
    std::string buff;
};
#endif //SPELLCHECKER_TWORD_H
