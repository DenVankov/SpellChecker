//
// Created by dvankov on 14.06.2019.
//

#ifndef SPELLCHECKER_TRIE_H
#define SPELLCHECKER_TRIE_H

#include "TWord.h"


class Node{
public:
    std::map<char, std::shared_ptr<Node>> edge;
    std::shared_ptr<TWord> end = nullptr;
};

class Trie{
public:
    Trie() {
        current = root;
    };
    void Add_to_trie(const std::string str, int64_t size, std::shared_ptr<TWord> connection);
    void Find(std::string &str, std::shared_ptr<Node> node, int64_t pos, int64_t mistake, std::map<std::shared_ptr<TWord>, int64_t > &ans);
    // поиск возможных исправлений символа в слове str, находящегося в позиции pos, с учетом уже совершенных ошибок mistake, а answer - найденные возможные исправления
    void Clear(std::shared_ptr<Node> node);
    void Print(std::shared_ptr<Node> node, int64_t n);
    bool Save(std::shared_ptr<Node> node, std::ofstream &os);
    bool Load(std::shared_ptr<Node> node, std::ifstream &is);
    std::shared_ptr<Node> Get_root();
    ~Trie(){
        current = nullptr;
        root->edge.clear();
    };
private:
    std::shared_ptr<Node> root{new Node};
    std::shared_ptr<Node> current;
};

#endif //SPELLCHECKER_TRIE_H
