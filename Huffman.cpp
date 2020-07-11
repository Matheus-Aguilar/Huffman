#include "Huffman.h"
#include<iostream>

//Default Constructor
HuffmanTree::HuffmanTree(const int freq[256]){
    build(freq);
}

//Copy Constructor
HuffmanTree::HuffmanTree(const HuffmanTree &other){
    build(other.freq);
}

//Assignment Operator
const HuffmanTree & HuffmanTree::operator=(const HuffmanTree &other){
    destroy(root);
    build(other.freq);
}

//Builds the Huffman Tree, frequency array and code array
void HuffmanTree::build(const int freq[256]){

    //Copying the frequencies
    for(int i = 0; i < 256; ++i)
        this->freq[i] = freq[i];

    //Priority queue of frequencies and roots to mantain the order of the trees
    priority_queue<pair<int, Node *>> pq;
    
    //Adding characters that appear at least once in the string
    for(int i = 0; i < 256; ++i){
        if(this->freq[i] > 0){
            //Priority and root the tree
            pq.push(make_pair(-freq[i], new Node(i)));
        }
    }

    //If the string is empty
    if(pq.size() == 0){
        root = NULL;
        return;
    }

    //Keeps merging trees until there is just one
    while(pq.size() > 1){
        
        //Remove the two ones without the highest priority
        pair<int, Node *> topTree1 = pq.top();
        pq.pop();
        pair<int, Node *> topTree2 = pq.top();
        pq.pop();

        /*Merge both nodes into a bigger tree*/

        //Add the frequencies of the smaller trees roots into the merged one
        pair<int, Node *> mergedTree = make_pair(topTree1.first + topTree2.first, new Node(0));
        //Highest priority tree becomes left child
        mergedTree.second->left = topTree1.second; 
        //Second highest becomes right child
        mergedTree.second->right = topTree2.second; 
        //Merged tree becomes the parent of the smaller ones
        topTree1.second->parent = topTree2.second->parent = mergedTree.second;

        //Add the merged node into the priority queue
        pq.push(mergedTree);
    }

    //Define the root of the Huffman Tree as the merge of all character trees
    root = pq.top().second;

    /*Build character codes*/

    /*File with only one type of character. This is a special case
    because the decompresion algorithm assumes that the root has at
    least one child*/
    if(root->left == NULL && root->right == NULL){
        code[root->character].push_back(0); //The code is 0 by default
        Node *aux = root; //Save the merged result
        root = new Node(0); //Set a new root of the tree
        root->left = aux; //Update the left child of the root
        return;
    }
    
    /*More than one type of character cases*/
    vector<bool> codeString;
    buildCodes(root, codeString); //Start from the root to build codes
}

//Destructor
HuffmanTree::~HuffmanTree(){
    destroy(root);
}

//Destroy the nodes of the tree recursively
void HuffmanTree::destroy(Node *node){
    if(node == NULL) return; //Leaf node
    destroy(node->left); //Destroys left child
    destroy(node->right); //Destroys right child
    delete node; //Free memory
}

//Build the codes, based on a Huffman Tree
void HuffmanTree::buildCodes(Node *node, vector<bool> &codeString){
    
    //Reached a leaf node
    if(node->left == NULL && node->right == NULL){
        code[node->character] = codeString; //Copy the code to codes array
        return; //End recursion
    }

    //If there is a left child
    if(node->left != NULL){
        codeString.push_back(0); //Adds a left move to the code, represented by a 0
        buildCodes(node->left, codeString); //Recursively call to left child
        codeString.pop_back(); //Remove the last move (backtracking)
    }

    if(node->right != NULL){
        codeString.push_back(1); //Adds a right move to the code, represented by a 1
        buildCodes(node->right, codeString); //Recursively call to right child
        codeString.pop_back(); //Remove the last move (backtracking)
    }
}

//Encodes the string into a binary codes vector
void HuffmanTree::compress(vector<bool> &out, const vector<char> &in) const{
    
    if(!out.empty()) out.clear(); //Clear the vector if not empty

    //Copying the codes to the vector
    for(int i = 0; i < in.size(); ++i){
        size_t pos = (unsigned char) in[i];
        for(int j = 0; j < code[pos].size(); j++)
            out.push_back(code[pos][j]);
    }
}

//Decodes a binary codes vector into a string
void HuffmanTree::descompress(vector<char> &out, const vector<bool> &in) const{
    
    if(!out.empty()) out.clear(); //Clear if not empty
    
    Node *node = root; //Start in the root node
    for(int i = 0; i < in.size(); ++i){
        if(!in[i]) //Left move (code 0)
            node = node->left;
        else //Right move (code 1)
            node = node->right;

        //Reached a leaf
        if(node->left == NULL && node->right == NULL){
            out.push_back(node->character); //Copy the caracther of the leaf
            node = root; //Return to the root
        }
    }
}