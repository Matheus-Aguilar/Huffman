CC = g++
CFLAGS = -O3

huffman: main.o Huffman.o
	$(CC) main.o Huffman.o $(CFLAGS) -o huffman

Huffman.o: Huffman.cpp
	$(CC) Huffman.cpp $(CFLAGS) -c

main.o: main.cpp
	$(CC) main.cpp $(CFLAGS) -c
	
clear:
	rm main.o Huffman.o huffman
