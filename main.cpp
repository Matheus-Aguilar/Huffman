#include <iostream>
#include <fstream>
#include "Huffman.h"
using namespace std;

void compressFile(char *in, char *out){
	
	ifstream fin; //Input file
	fin.open(in, ios::binary); 

	ofstream fout; //Output file
	fout.open(out, ofstream::out);

	vector<char> content; //Content of the file
	vector<bool> bits; //Encoded bits

	int freq[256] = {0}; //Frequency array

	//Copying each caracter to vector and calculating the frequencies
	unsigned char character;
	for(int i = 0; fin.peek() != -1; ++i){
		fin.read(reinterpret_cast<char *>(&character), sizeof(unsigned char));
		content.push_back(character);
		++freq[character];
	}

	HuffmanTree tree(freq); //Build the tree
	tree.compress(bits, content); //Save the huffman encoded bits into the vector

	//Saving the frequency dictionary into the file
	fout.write(reinterpret_cast<const char *>(freq), sizeof(freq));
	//Copying the number of bits of the huffman encoding
	int HuffmanSize = bits.size();
	fout.write(reinterpret_cast<const char *>(&HuffmanSize), sizeof(int));
	
	//Completing the bits of the encoding to make a complete byte
	while(bits.size() % 8 != 0) bits.push_back(false);
	
	//Writing the enconding in the output file
	for(int i = 0; i < bits.size(); i += 8){
		//Merging the bits into a byte
		unsigned char byte = (unsigned char)(bits[i] << 7) + (unsigned char)(bits[i + 1] << 6) + 
		(unsigned char)(bits[i + 2] << 5) + (unsigned char)(bits[i + 3] << 4) + (unsigned char)(bits[i + 4] << 3) +
		(unsigned char)(bits[i + 5] << 2) + (unsigned char)(bits[i + 6] << 1) + (unsigned char)(bits[i + 7]);
		fout.write(reinterpret_cast<char *>(&byte), sizeof(unsigned char)); //Write the byte
	}

	//Close files
	fin.close();
	fout.close();
}

//Split a byte into bits and appends to the end of the vector
void splitByte(const unsigned char byte, vector<bool> &bits){
	//Auxiliar usado para retirar o bit mais significativo
	unsigned char pos = 1 << 7;
	while(pos){ 
		bits.push_back(((byte & pos) ? 1 : 0)); //Get the Least Significant Digit
		pos >>= 1; //Shift to the right
	}
}

void descompressFile(char *in, char *out){
	
	ifstream fin; //Input file
	fin.open(in, ios::binary); 

	ofstream fout; //Output file
	fout.open(out, ofstream::out);

	vector<bool> bits; //Bits of the input file
	vector<char> content; //Decoded content

	int freq[256] = {0}; //Frequency array

	//Getting the frequencies of the huffman encoding
	fin.read(reinterpret_cast<char *>(freq), sizeof(freq));

	//Get the encoding size (to ignore extra bits)
	int HuffmanSize;
	fin.read(reinterpret_cast<char *>(&HuffmanSize), sizeof(int));

	//Reading bytes and conveting to bits
	unsigned char byte;
	while(fin.peek() != -1){
		fin.read(reinterpret_cast<char *>(&byte), sizeof(unsigned char));
		splitByte(byte, bits); //Split byte and append to the end of bits
	}

	//Remove extra bits
	while(bits.size() > HuffmanSize) bits.pop_back(); 

	HuffmanTree tree(freq); //Build the tree
	tree.descompress(content, bits); //Decodes the bits into a string

	for(int i = 0; i < content.size(); ++i)
		fout.write(reinterpret_cast<char *>(&content[i]), sizeof(char)); //Save the decoded content into file

	//Close files
	fin.close();
	fout.close();
}

int main(int argc, char **argv) {

	//c to compress, d to decompress
	if(argv[1][0] == 'c'){
		compressFile(argv[2], argv[3]);
	}
	else if(argv[1][0] == 'd'){
		descompressFile(argv[2], argv[3]);
	}
	else{
		throw("Invalid Flag!");
	}
}
