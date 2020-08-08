# Huffman Coding

This project is C++ implementation of a simple lossless compression algorithm, based on the Huffman Coding. It was made as a practical exam for the Data Structures (INF 213) course of the Computer Science major of the Federal University of Viçosa (UFV).

## Compiling

 To compile the code, just run the Makefile:

```bash
~$ make
```

 If it doesn't work, try to compile the files mannualy with the following commands:
  
```bash
~$ g++ main.cpp -std=c++11 -O3 -c
~$ g++ Huffman.cpp -std=c++11 -O3 -c
~$ g++ main.o Huffman.o -std=c++11 -O3 -o huffman
```

 If you updated the code and got a 'up to date' message when trying to run the Makefile, try:
  
 ```bash
~$ make clear
```

 or
  
```bash
~$ rm main.o Huffman.o huffman
```

## Running

### Compressing files

To compress a file just run:

```
~$ ./huffman c input_file_name compressed_output_name
```

### Decompressing files

To decompress a file just run:

```
~$ ./huffman d compressed_file_name decompressed_output_name
```

## Algorithm and Implementation

Proposed by David A. Huffman in 1951<sup>1</sup>, the Huffman Coding an optimal prefix code commonly used for lossless data compression. It generates a variable-length code to represent each symbol a of sequence, based on their frequency of occurrence in the given stream or on their probability of appearing in it. The implementation receives a file as input, counts the number of occurrences of each one of the 256 ASCII symbols, builds a tree of frequencies and generates a set of binary codes based on such tree. After that, it creates a file composed by the frequencies of each symbol and the encoded symbols of the original file. To decompress the created files, the implementation uses the frequencies to rebuild the tree and reverse engineers the symbols using the codes.

## Compression Example

A simple example of how the algorithm would encode the string "ABBBABBBCBDB"

<table>
  <thead>
    <th> Symbol </th>
    <th> Frequency </th>
    <th> ASCII Code </th>
    <th> Huffman Code </th>
  </thead>
  <tbody>
    <tr>
       <td> A </td>
       <td> 2 </td>
       <td> 1000001 </td>
    </tr>
    <tr>
       <td> B </td>
       <td> 8 </td>
       <td> 1000010 </td>
    </tr>
    <tr>
       <td> C </td>
       <td> 1 </td>
       <td> 1000011 </td>
    </tr>
    <tr>
       <td> D </td>
       <td> 1 </td>
       <td> 1000100 </td>
    </tr>
  </tbody>
</table>
