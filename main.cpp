#include <stdio.h>
#include <cstring>
#include "Trie.h"
#include "TWord.h"
#include "Algorithm.h"

void Read_data(std::string &str, std::vector<std::string> &input_string, std::string &buff) {
    int64_t begin = 0;
    int64_t end = 0;
    for (size_t i = 0; i < buff.size(); ++i) {
        if (i == buff.size() - 1 || buff[i] == ' ') {
            if (i == buff.size() - 1)
                end = i + 1;
            if (buff[i] == ' ')
                end = i;
            if (begin != 0)
                input_string.push_back(buff.substr(begin,end - begin));
            else
                str = buff.substr(begin, end - begin);
            begin = i + 1;
        }
    }
}

size_t Compare(std::string &str,std::string &prev_str, size_t pos1, size_t pos2, size_t mistake) {
    size_t answer = 3;
    if (str.size() < prev_str.size() || str.size() > prev_str.size() + 2)
        return answer;

    if (pos1 >= str.size() || pos2 >= prev_str.size() || (pos1 == str.size() - 1 && pos2 == str.size() - 1))
        return mistake;
    if (pos1 < str.size() && pos2 < prev_str.size()) {
        if (str[pos1] == prev_str[pos2]) {
            size_t tmp = Compare(str, prev_str, pos1 + 1, pos2 + 1, mistake);
            if (answer > tmp)
                answer = tmp;
        }
    }
    if (mistake < 2) {
        size_t tmp = Compare(str, prev_str, pos1, pos2 + 1, mistake + 1);
        if (answer > tmp)
            answer = tmp;
        tmp = Compare(str, prev_str, pos1 + 1, pos2, mistake + 1);
        if (answer > tmp)
            answer = tmp;
        tmp = Compare(str, prev_str, pos1 + 1, pos2 + 1, mistake + 1);
        if (answer > tmp)
            answer = tmp;
    }
    return answer;
}

int main(int argc, char**argv) {
    Trie trie;
    Alphabet alphabet;
    int operation = 0;
    if (argc < 2){
        std::cout << "Error: Not enough arguments\n";
        return 1;
    }
    if (strcmp(argv[1], "learn") == 0)
        operation = 1;
    if (strcmp(argv[1], "correct") == 0)
        operation = 2;
    std::cout << "Use operation " << operation;
    (operation == 1) ? std::cout << " - learn\n" : std::cout << " - correct\n";

    switch(operation) {
        case 1: {
            char symb;
            int64_t _in = 0;
            int64_t _out = 0;
            std::string buff;
            for (size_t i = 2; i < argc - 1; ++i) {
                if (strcmp(argv[i], "--input") == 0)
                    _in = i + 1;
                if (strcmp(argv[i], "--output") == 0)
                    _out = i + 1;
            }
            if (_in == 0 || _out == 0) {
                std::cout << "Error: wrong arguments\n";
                return 1;
            }

            std::string infile(argv[_in]);
            std::string outfile(argv[_out]);
            std::ifstream in(infile, std::ifstream :: in);

            if (!in) {
                std::cout << "Error: Can`t open the file (in)\n";
                return 1;
            }
            in.get(symb);
            while (in) {
                while (!in.eof() && symb != '\t') {
                    in.get(symb);
                }

                do {
                    std::string str;
                    in >> buff;
                    str = buff;
                    std::shared_ptr <TWord> connect = alphabet.Add_new_word(str);
                    if (connect != nullptr)
                        trie.Add_to_trie(buff, buff.size(), connect);
                    in.get(symb);
                } while (symb != '\t' && !in.eof());

                while (!in.eof() && symb != '\n'){
                    in.get(symb);
                }

                in.get(symb);
                alphabet.Free_buff();
                buff.clear();
            }
            in.close();
            std::ofstream out(argv[_out], std::ofstream :: out | std::ofstream :: app);
            if (!out) {
                std::cout << "Error: Can`t open the file (out)\n";
                return 1;
            }

            alphabet.Save(out);
            std::cout << "Alphabet was saved\n";
            trie.Save(trie.Get_root(), out);
            std::cout << "Trie was saved\n";
            out.close();
            break;
        }

        case 2: {
            int64_t _in = 0;
            int64_t _out = 0;
            int64_t _stat = 0;
            std::string buff;
            for (size_t i = 2; i < argc - 1; ++i) {
                if (strcmp(argv[i], "--input") == 0)
                    _in = i + 1;
                if (strcmp(argv[i], "--output") == 0)
                    _out = i + 1;
                if (strcmp(argv[i], "--stat") == 0)
                    _stat = i + 1;
            }
            if (_in == 0 || _stat == 0) {
                std::cout << "Error: wrong arguments\n";
                return 1;
            }
            std::ifstream stats(argv[_stat], std::ifstream :: in);
            if (!stats) {
                std::cout << "Error: Can`t open the file (stat)\n";
                return 1;
            }
            std::ofstream out(argv[_out], std::ofstream :: out);
            if (!out) {
                std::cout << "Error: Can`t open the file (out)\n";
                return 1;
            }
            alphabet.Clear();
            alphabet.Load(alphabet.alpha, stats);
            trie.Clear(trie.Get_root());
            trie.Load(trie.Get_root(), stats);
            stats.close();
            std::ifstream in(argv[_in], std::ifstream :: in);
            if (!in) {
                std::cout << "Error: Can`t open the file (in)\n";
                return 1;
            }
            std::cout << alphabet.alpha.size() << "\n";
            Algo _algo;
            while (std::getline(in, buff, '\n')) {
                int64_t check = 0;
                std::string str;
                std::vector<std::string> input_str;
                Read_data(str, input_str, buff);
                check = _algo.Pre_analysis(trie, str);
                for (auto &iter: input_str) {
                    if (check == 1)
                        break;
                    if (!iter.empty())
                        check = _algo.Analysis(alphabet, trie, iter);
                }
                if (check != 1)
                    _algo.Answer(out);
                else
                    std::cout << "Answer not found";
                _algo.Clear();
                input_str.clear();
            }
            in.close();
            out.close();
            break;
        }
        default: {
            std::cout << "Error: Wrong parameter\n";
            break;
        }
    }
    alphabet.Clear();
    return 0;
}