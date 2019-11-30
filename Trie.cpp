//
// Created by dvankov on 14.06.2019.
//

#include"Trie.h"

void Trie::Add_to_trie(const std::string str, int64_t size, std::shared_ptr<TWord> connection) {
    for (size_t i = 0; i < size; ++i){
        std::map<char, std::shared_ptr<Node>> :: const_iterator iter;
        iter = current->edge.find(str[i]);
        if (iter != current->edge.end())
            current = iter->second;
        else {
            std::shared_ptr<Node> leaf{new Node};
            current->edge[str[i]] = leaf;
            current = leaf;
        }
    }
    if (current->end == nullptr)
        current->end = connection;
    current = root;
}

void Trie::Find(std::string &str, std::shared_ptr<Node> node, int64_t pos, int64_t mistake,
                std::map<std::shared_ptr<TWord>, int64_t> &ans) {
    if (node->end != nullptr && pos >= str.size()) {
        std::map<std::shared_ptr<TWord>, int64_t> :: const_iterator iter;
        iter = ans.find(node->end);
        if (iter == ans.end())
            ans[node->end] = mistake;
        if (ans[node->end] > mistake)
            ans[node->end] = mistake;
    }
    if (pos == str.size() +1 ) {
        return;;
    }
    std::map<char, std::shared_ptr<Node>> :: const_iterator iter;
    if (pos < str.size()) {
        iter = node->edge.find(str[pos]);
        if (iter != node->edge.end())
            Find(str, iter->second, pos + 1, mistake, ans); // На этом этапе мы нашли нужную букву букву

    }
        if (mistake < 2) {
            Find(str, node, pos + 1, mistake + 1, ans); // Пропустили букву
            for (iter = node->edge.begin(); iter != node->edge.end(); ++iter) {
                Find(str, iter->second, pos    , mistake, ans); // Добавляем еще 1 букву
                Find(str, iter->second, pos + 1, mistake, ans); // Совершили ошибку
            }
        }
}

void Trie::Print(std::shared_ptr<Node> node, int64_t n) {
    if (node == nullptr)
        return;
    for (auto &i: node->edge) {
        Print(i.second, n + 1);
        for (size_t j = 0; j < n; ++j)
            std::cout << "\t";
        std::cout << i.first;
        if (i.second->end == nullptr)
            std:: cout << "~" << i.second->end->word;
        std::cout << "\n";
    }
}

std::shared_ptr<Node> Trie::Get_root() {
    return root;
}

void Trie::Clear(std::shared_ptr<Node> node) {
    node->edge.clear();
}

bool Trie::Save(std::shared_ptr<Node> node, std::ofstream &os) {
    if (node == nullptr)
        return false;
    os << node->edge.size() << "\n";
    for (auto &i: node->edge) {
        os << i.first << " ";
        if (i.second != nullptr)
            os << i.second->end->word << " " << i.second->end->counting << "\n";
        else
            os << "0 0\n";
        Save(i.second, os);
    }
    return true;
}

bool Trie::Load(std::shared_ptr<Node> node, std::ifstream &is) {
    char cur_char;
    int64_t edge_size;
    int64_t cur_end_capacity;
    std::string cur_end_word;
    is >> edge_size;
    for (size_t i = 0; i < edge_size; ++i) {
        is >> cur_char >> cur_end_word >> cur_end_capacity;
        std::shared_ptr<Node> tmp_node{new Node};
        if (cur_end_word != "0") {
            std::shared_ptr<TWord> end{new TWord};
            end->counting = cur_end_capacity;
            end->word = cur_end_word;
            tmp_node->end = end;
        } else
            tmp_node->end = nullptr;
        node->edge[cur_char] = tmp_node;
        Load(tmp_node, is);
    }
    return true;
}