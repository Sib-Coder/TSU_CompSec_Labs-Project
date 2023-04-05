#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <queue>
#include <unordered_map>


using namespace std;

class Node { ///узел дерева
public:
    string key;
    unsigned long long size;
    Node *R;
    Node *L;

    bool operator()(const Node &x, const Node &y) {///объединение узлов
        return x.size >= y.size;
    }

    Node(const string &value = "", unsigned long long cast = 0, Node *left = NULL, Node *right = NULL) {///конструктор
        key = value;
        size = cast;
        L = left;
        R = right;
    }

    Node *join(Node node) {
        return new Node(node.key + key, node.size + size, new Node(node), this);
    }
};

Node *builder(priority_queue<Node, vector<Node>, Node> leafs) {///построение дерева
    while (leafs.size() > 1) {
        Node *n = new Node(leafs.top());
        leafs.pop();
        leafs.push(*n->join(*new Node(leafs.top())));
        leafs.pop();
    }
    return new Node(leafs.top());
}

void huffmanCodes(Node *root, string code, unordered_map<string, string> &huffmanCode) {///делаем коды
    if (root == nullptr)
        return;
    if (!root->L && !root->R) {
        huffmanCode[root->key] = code;
    }
    huffmanCodes(root->L, code + "0", huffmanCode);
    huffmanCodes(root->R, code + "1", huffmanCode);
}

void decoder(const char* input_name="encoded.txt", const char* output_name="output.txt"){ ///функция декодирования
    unsigned long long * alfabet = new unsigned long long [256];
    for(int i=0; i<256; i++){
        alfabet[i] = 0;
    }
    FILE* input_file = fopen(input_name, "rb"); // Open input file
    if (input_file == nullptr) {
        throw invalid_argument("File not found.");
    }
    unsigned char col = 0;
    unsigned int col_letters = 0;
    col = fgetc(input_file);
    if(!feof(input_file)){
        col_letters =(int) col;
    }

    unsigned char character = 0;
    for(int i = 0; i< col_letters; i++){ ///считываем букву и колличество
        character = fgetc(input_file);
        if(!feof(input_file)){
            unsigned long long col_of;
            fread(reinterpret_cast<char*>(&alfabet[character]), sizeof(unsigned long long), 1, input_file);
            cout<< character<< ':'<< alfabet[character]<<endl;
        }
        else{
            throw invalid_argument("Can't decompress file.");
        }
    }

    priority_queue<Node, vector<Node>, Node> tree;
    for(int i=0; i<256; i++){
        if(alfabet[i] != 0){
            string s(1, (char)i);

            Node new_leaf(s, alfabet[i]);
            tree.push(new_leaf);
        }
    }
    character = 0;
    Node *n = builder(tree);

    FILE* output_file = fopen(output_name, "wb+");
    Node *nodes = n;
    unsigned char letter = 0;
    while (!feof(input_file)) { // Decompressing the file
        character = fgetc(input_file);
        if(!feof(input_file)){
            for (int i = 7; i > -1; i--){
                if(((character >> i) & 1) == 1){
                    if(nodes->R == NULL){
                        letter = nodes->key[0];
                        if(alfabet[letter]>0){
                            alfabet[letter]--;
                            fputc(letter, output_file);
                            nodes = n->R;
                        }
                    }
                    else{
                        nodes = nodes->R;
                    }
                }

                else if(((character >> i) & 1) == 0){
                    if(nodes->L == NULL){
                        letter = nodes->key[0];
                        if(alfabet[letter]>0){
                            fputc(letter, output_file);
                            nodes = n->L;
                            alfabet[letter]--;
                        }
                    }
                    else{
                        nodes = nodes->L;
                    }
                }
            }
        }
    }

    fclose(input_file);
    fclose(output_file);
}


void checker(const char* before_name="input.txt", const char* after_name="output.txt"){ // Checking for file matches
    unsigned int same = 0;
    FILE* before_file = fopen(before_name, "rb");
    FILE* after_file = fopen(after_name, "rb");

    unsigned char after_l = 0;
    unsigned char before_l = 0;
    while (!feof(after_file) && !feof(before_file)) {
        after_l = fgetc(after_file);
        before_l = fgetc(before_file);
        if(!feof(after_file) && !feof(before_file)){
            if(after_l != before_l){
                same++;
            }
        }
    }

    while (!feof(after_file))
    {
        after_l = fgetc(after_file);
        if(!feof(after_file)){
            same++;
        }
    }

    while (!feof(before_file))
    {
        before_l = fgetc(before_file);
        if(!feof(before_file)){
            same++;
        }
    }
    fclose(after_file);
    fclose(before_file);
    if (same==0) cout<<"Bill_Harington_is_ALive"; else cout<<"gachi_mems";
}




int main() {
    decoder();
    checker();
}
