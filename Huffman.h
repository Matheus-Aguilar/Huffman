#ifndef _HUFFMAN_H
#define _HUFFMAN_H

#include <algorithm>
#include <vector>
#include <queue>

using std::make_pair;
using std::pair;
using std::vector;
using std::priority_queue;

class Node{
    friend class HuffmanTree;

    //Necessary for the priority queue
    public:
        bool operator<(const Node *other){ return this->character < other->character; }

    //Only HuffmanTree class can access the nodes data
    private:
        Node(const char character_): character(character_), 
        left(NULL), right(NULL), parent(NULL){}; //Default Constructor
        Node *left; //Pointer to left child
        Node *right; //Pointer to right child
        Node *parent; //Pointer to parent
        unsigned char character; //Character of the node
};

class HuffmanTree{
    public:
        HuffmanTree(const int freq[256]); //Default Constructor
        HuffmanTree(const HuffmanTree &); //Copy Constructor
        const HuffmanTree & operator=(const HuffmanTree &); //Assignment Operator
        ~HuffmanTree(); //Destructor
        void compress(vector<bool> &, const vector <char> &) const; //Encodes a string into a compressed binary representation
        void descompress(vector <char> &, const vector<bool> &) const; //Decodes a compressed binary representation into a string
    private:
        Node *root; //Root of the Tree
        int freq[256]; //Frequency of each character
        vector<bool> code[256]; //Codes of each character
        void buildCodes(Node *, vector<bool> &); //Build the codes based on the tree
        void build(const int freq[256]); //Build the tree based on the frequency array and returns the root
        void destroy(Node *); //Destroy the tree starting from the root
};

#endif