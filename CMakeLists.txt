cmake_minimum_required(VERSION 3.12)
project(SpellChecker)

set(CMAKE_CXX_STANDARD 11)

add_executable(SpellChecker main.cpp TWord.h TWord.cpp Algorithm.h Trie.h Trie.cpp Algorithm.cpp)