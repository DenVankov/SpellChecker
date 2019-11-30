CC = g++
FLAGS = -std=c++11 -O2 -pedantic -Wall -Werror -Wno-sign-compare -Wno-long-long -lm -c

OUT = spellchecker

all: main.o Trie.o TWord.o Algorithm.o TWord.h Trie.h Algorithm.h
	$(CC) -o $(OUT) main.o Trie.o TWord.o Algorithm.o

main.o: main.cpp Trie.h TWord.h
	$(CC) $(FLAGS) -o main.o main.cpp

Trie.o: Trie.cpp Trie.h TWord.h
	$(CC) $(FLAGS) -o  Trie.o Trie.cpp

TWord.o: TWord.cpp TWord.h
	$(CC) $(FLAGS) -o TWord.o TWord.cpp

Algorithm.o: Algorithm.cpp Algorithm.h Trie.h TWord.h
	$(CC) $(FLAGS) -o Algorithm.o Algorithm.cpp
