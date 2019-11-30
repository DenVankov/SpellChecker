//
// Created by dvankov on 11.06.2019.
//

#include "TWord.h"
Alphabet::Alphabet() {
    buff.clear();
}

void Alphabet::Print() {
    for (auto &iter: alpha){
        std::cout << iter.second.word << " / " << iter.second.counting << '\n';
        for (auto &iter_2: alpha[iter.first].next){
            std::cout << '\t' << iter_2.second.word << " / " << iter_2.second.counting << '\n';
        }
    }
}

bool Alphabet::Save(std::ofstream &os) {
    os << alpha.size() << "\n";
    for(auto &iter: alpha) {
        os << iter.second.word << " " << iter.second.counting << " " << std::endl;
        os << alpha[iter.first].next.size()<<" ";
        for(auto &in: alpha[iter.first].next){
            os << in.second.word << " " << in.second.counting << " " << in.second.next.size() << " ";
        }
    }
    return true;

}

bool Alphabet::Load(std::map<std::string, TWord> &elem, std::ifstream &is) {
    std::string current_str;
    int64_t current_count = 0;
    int current_size = 0;
    is >> current_size;
    for(size_t  i = 0; i < current_size; ++i) {
        is >> current_str;
        is >> current_count;
        TWord current_tword(current_str, current_count);
        elem[current_str] = current_tword;
        Load(elem[current_str].next, is);
    }
    return true;
}

std::shared_ptr<TWord> Alphabet::Add_new_word(std::string &data) {
    if (data.empty())
        return nullptr;
    TWord tmp;
    std::shared_ptr<TWord> link = nullptr;
    std::map<std::string, TWord> :: const_iterator iter, iter_2;
    iter = alpha.find(data);
    if (iter != alpha.end())
        alpha[iter->first].counting++;
    else {
        tmp.word = data;
        alpha[data] = tmp;
        link = std::make_shared<TWord>(alpha[data]);
    }
    if (!buff.empty()) {
        TWord new_word;
        iter = alpha.find(buff);
        if (iter != alpha.end()) {
            iter_2 = iter->second.next.end();
            if (iter_2 != iter_2->second.next.end())
                alpha[iter->first].next[iter_2->first].counting++;
            else {
                alpha[iter->first].next[data] = new_word;
                alpha[iter->first].next[data].word = data;
            }
        }
    }
    buff = data;
    return link;
}

double Alphabet::Number_of_pair(std::string &first, std::string &second) {
    std::map<std::string, TWord> :: const_iterator iter,is;
    iter = alpha.find(first);
    if (iter != alpha.end()) {
        is = iter->second.next.find(second);
        if (is != iter->second.next.end()) {
            return is->second.counting;
        }
    }
    return 0;
}

void Alphabet::Clear() {
    alpha.clear();
    buff.clear();
}

void Alphabet::Free_buff() {
    buff.clear();
}

int64_t Alphabet::Size() {
    return buff.size();
}