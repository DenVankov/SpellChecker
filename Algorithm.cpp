//
// Created by dvankov on 14.06.2019.
//

#include "Algorithm.h"

int64_t Algo::Pre_analysis(Trie &trie, std::string &buff) {
    trie.Find(buff, trie.Get_root(), 0, 0, tmp_answer);
    if (tmp_answer.size() == 0)
        return 1;
    double tmp_count = 0.0;
    for (auto &iter: tmp_answer) {
        tmp_count += iter.first->counting;
    }
    std::vector<Algo_structure> vector;
    for (auto &iter: tmp_answer) {
        Algo_structure unit;
        unit.probably = log(iter.first->counting / tmp_count);
        if (iter.second == 2)
            unit.probably -= 2;
        if (iter.second == 1)
            unit.probably -= 1;
        unit.word = iter.first;
        vector.push_back(unit);
    }
    prev_size = tmp_answer.size();
    Data.push_back(vector);
    tmp_answer.clear();
    return 0;
}

int64_t Algo::Analysis(Alphabet &alphabet, Trie &trie, std::string &buff) {
    trie.Find(buff, trie.Get_root(), 0, 0, tmp_answer);
    if (tmp_answer.size() == 0)
        return 1;
    std::vector<Algo_structure> vector;
    for (auto &iter: tmp_answer) {
        int64_t max_index = 0;
        double tmp_max = 1.0;
        for (size_t i = 0; i < prev_size; ++i) {
            if (alphabet.Number_of_pair(Data[index][i].word->word, iter.first->word) != 0) {
                double tmp_max_pair = log(alphabet.Number_of_pair(Data[index][i].word->word, iter.first->word) / Data[index][i].word->counting);
                if (iter.second == 2)
                    tmp_max_pair -= 2;
                if (iter.second == 1)
                    tmp_max_pair -= 1;
                if (tmp_max == 1 || tmp_max_pair > tmp_max) {
                    tmp_max = tmp_max_pair;
                    max_index = i;
                }
            }
        }
        if (tmp_max != 1) {
            Algo_structure unit;
            unit.probably = tmp_max;
            unit.prev_index = max_index;
            unit.word = iter.first;
            vector.push_back(unit);
        }
    }
    if (vector.size() == 0)
        return 1;
    Data.push_back(vector);
    prev_size = vector.size();
    index++;
    tmp_answer.clear();
    return 0;
}

void Algo::Answer(std::ofstream &os) {
    if (Data.size() == 0) {
        os << "Equal not found\n";
        return;
    }
    int64_t index_a = Data.size() - 1;
    int64_t index_b = 0;
    double tmp_prod = Data[index_a][0].probably;
    for (size_t i = 1; i < Data[index_a][0].probably; ++i) {
        if (Data[index_a][i].probably > tmp_prod) {
            index_b = i;
            tmp_prod = Data[index_a][i].probably;
        }
    }
    std::vector<std::string> ans;
    ans.push_back(Data[index_a][index_b].word->word);
    while (index_a > 0) {
        index_b = Data[index_a][index_b].prev_index;
        index_a--;
        ans.push_back(Data[index_a][index_b].word->word);
    }
    for (int64_t i = ans.size() - 1; i >= 0; --i) {
        os << ans[i] << " ";
    }
    std::cout << "\n";
}

void Algo::Print() {
    for (size_t i = 0; i < Data.size(); ++i) {
        for (size_t j = 0; j < Data[i].size(); ++j) {
            std::cout << "[ " << i << "; " << j << "]\n";
            std::cout << "Word " << Data[i][j].word->word << " probably = " << Data[i][j].probably << "\t";
        }
        std::cout << "\n";
    }
}

void Algo::Clear() {
    index = 0;
    prev_size = 0;
    Data.clear();
    tmp_answer.clear();
}
