//
// Created by dvankov on 14.06.2019.
//

#ifndef SPELLCHECKER_ALGORITHM_H
#define SPELLCHECKER_ALGORITHM_H

#include "TWord.h"
#include "Trie.h"
#include <cmath>

class Algo_structure{
public:
    double probably = 0; // вероятность фразы
    int64_t prev_index = 0; // индекс предыдущего слова
    std::shared_ptr<TWord> word; // текущее слово
};

class Algo{
public:
    int64_t Pre_analysis(Trie &trie, std::string &buff);
    int64_t Analysis(Alphabet &alphabet, Trie &trie, std::string &buff);
    void Print();
    void Answer(std::ofstream &os);
    void Clear();

private:
    int64_t index = 0; // текущий столбец в векторе
    int64_t prev_size = 0; // количество вариантов слова на предыдущем шаге
    std::vector<std::vector<Algo_structure>> Data;
    std::map<std::shared_ptr<TWord>, int64_t> tmp_answer; // временный(текущий) ответ
};

#endif //SPELLCHECKER_ALGORITHM_H
