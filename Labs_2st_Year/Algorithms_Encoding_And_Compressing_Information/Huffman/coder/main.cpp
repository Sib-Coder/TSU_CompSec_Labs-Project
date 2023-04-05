#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <sys/stat.h>

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

double Ksusha(const char *input_name = "text.txt", const char *output_name = "codetext.txt") {
    FILE *input_file = fopen("text.txt", "r");
    unsigned long long *alfavit = new unsigned long long[256];
    for (int i = 0; i < 256; i++) {
        alfavit[i] = 0;
    }
    unsigned char simvol = 0;
    while (!feof(input_file)) {
        simvol = fgetc(input_file);
        if (!feof(input_file)) {
            alfavit[simvol]++;
        }
    }
    for (int i = 0; i < 256; i++) {
        //cout<<alfavit[i]<<endl;
    }
    fclose(input_file);

    priority_queue<Node, vector<Node>, Node> leafs; ///Создаём листья
    for (int i = 0; i < 256; i++) {
        if (alfavit[i] != 0) {
            string s(1, (char) i);
            Node new_leaf(s, alfavit[i]);
            //cout<<s<<" : "<<alfavit[i]<<" : "<<new_leaf.size<<endl;
            leafs.push(new_leaf);
        }
    }
    Node *tree = builder(leafs); ///создание дерева

    unordered_map<string, string> huffmanCode;
    huffmanCodes(tree, "", huffmanCode); ///генерация

    cout << "Huffman Codes are :\n" << '\n'; ///вывод кодов
    for (auto pair: huffmanCode) {
        cout << pair.first << " " << pair.second << '\n';
    }
    FILE *output_file = fopen(output_name, "w +");
    input_file = fopen(input_name, "r");


    simvol = 0;
    unsigned char k = 0;
    unsigned int len = 0;
    unsigned int bit_len = 0;
    unsigned char letter = 0;
    char col_letters = leafs.size();
    fputc(col_letters, output_file);

    for (int i = 0; i < 256; i++) { ///букв + колличество
        if (alfavit[i] != 0) {
            fputc((char) i, output_file);
            fwrite(reinterpret_cast<const char *>(&alfavit[i]), sizeof(unsigned long long), 1, output_file);
        }
    }

    while (!feof(input_file)) { /// Сжатие в файле
        simvol = fgetc(input_file);
        if (!feof(input_file)) {
            string s(1, simvol);
            if (bit_len + huffmanCode[s].length() <= 8) {
                for (int i = 0; i < huffmanCode[s].length(); i++) {
                    letter = letter << 1 | (huffmanCode[s][i] - '0');
                }
                bit_len += huffmanCode[s].length();
            } else {
                for (int i = 0; i < 8 - bit_len; i++) {
                    letter = letter << 1 | (huffmanCode[s][i] - '0');
                }
                if (huffmanCode[s].length() - 8 + bit_len >= 8) {
                    int i = 8 - bit_len;
                    while (i + 7 < huffmanCode[s].length()) {
                        k = 0;
                        for (int j = 0; j < 8; j++) {
                            k = k << 1 | (huffmanCode[s][i + j] - '0');
                        }
                        i += 8;
                        fputc(letter, output_file);
                        letter = k;
                    }
                    k = 0;
                    len = 0;

                    for (int j = i; j < huffmanCode[s].length(); j++) {
                        k = k << 1 | (huffmanCode[s][j] - '0');
                        len++;
                    }
                } else {
                    len = 0;
                    for (int i = 8 - bit_len; i < huffmanCode[s].length(); i++) {
                        k = k << 1 | (huffmanCode[s][i] - '0');
                        len++;
                    }
                }
                bit_len = 8;
            }
            if (bit_len == 8) {

                fputc(letter, output_file);

                letter = k;
                bit_len = len;
                k = 0;
                len = 0;
            }
        } else if (bit_len < 8) {
            letter = letter << 8 - bit_len;
            fputc(letter, output_file);
        }
    }

    fclose(input_file);
    fclose(output_file);

    unsigned long long file_full_size = 0;
    unsigned long long commpres_size = 0;
    struct stat sb{};
    struct stat se{};
    if (!stat(input_name, &sb)) { ///определение степени сжатия
        file_full_size = sb.st_size;
    } else {
        perror("stat");
    }
    if (!stat(output_name, &se)) {
        commpres_size = se.st_size;
    } else {
        perror("stat");
    }
    cout<< "compress="<< (commpres_size + 0.0) / file_full_size*100<<"%";
}

int main() {
    Ksusha();
}