#include <iostream>
#include <stdexcept>

using namespace std;

class Node {
    friend class BinTree;
    int key;
    Node *left, *right;

public:
    Node(int k = 0, Node *l = NULL, Node *r = NULL) {
        key = k;
        left = l;
        right = r;
    }

    ~Node() {
        key = 0;
        left = NULL;
        right = NULL;
    }
};

struct elem{
    Node * p;// на уузел
    elem * next;// на следующий элемент
};


class BinTree {
protected:
    Node *root;
    void print_tree(int, Node *);
    void delete_tree(Node *);
    Node* add_node(Node *, Node *);///копирование дерева

public:
    BinTree() {
        root == NULL;
    }

    BinTree(int len) {
        root = NULL;
        for (int i = 0; i < len; i++) {
            int k = rand() % 100;
            this->add(k);
        }
    }

    BinTree(int len, int *arr) {
        root = NULL;
        for (int i = 0; i < len; i++) {
            this->add(arr[i]);
        }
    }

    BinTree(const BinTree &tree) {
        root = add_node(root, tree.root);
    }

    ~BinTree(){
        delete_tree(root);
    }
    BinTree &operator=(const BinTree &);
    void add(int);
    Node *del(int);
    Node *del(Node *);
    void print();
    Node *find(int);
    int max();
    int min();
    elem* BFS();
    void LRK(Node* );

};

void BinTree::add(int k) {
    if (root == NULL) {
        root = new Node(k);
        return;
    }
    Node *node = root;
    while (node) {
        if (node->key > k && node->left == NULL) {
            node->left = new Node(k);
            return;
        } else if (node->key <= k && node->right == NULL) {
            node->right = new Node(k);
            return;
        }
        if (node->key > k)
            node = node->left;
        else
            node = node->right;

    }}
void BinTree::delete_tree(Node * node) {
    if (node){
        delete_tree(node->left);
        delete_tree(node->right);
        delete node;
    }
}
Node * BinTree::add_node(Node * n, Node * node) {
    if(!node){
        return  NULL;
    }
    n =new Node(node ->key);
    n -> left =add_node(n->left,node->left);
    n -> right = add_node(n->right, node->right);
    return n;
}

BinTree& BinTree::operator=(const BinTree & tree) {
    if(this != &tree){
        delete_tree(root);///удалить дерево
        root = add_node(root, tree.root);
    }
    return *this;
}

void BinTree::print() {
    print_tree(1, root);
    cout << endl;
}

void BinTree::print_tree(int k, Node* node) {

    if (node != NULL)
    {

        print_tree (k+5, node->right);
        for(int i = 0; i < k; i++) {
            cout << " ";
        }
        cout << node->key  << endl;
        print_tree (k+5, node->left);
    }

}

Node* BinTree ::find(int k) {
    if (root == NULL)
        return NULL;
    Node* n = root;
    while(n) {
        if (n->key == k){
            return n;
        } else if (n->key > k && n->left == NULL) {
            return NULL;
        } else if (n->key < k && n->right == NULL) {
            return NULL;
        }
        if (n->key > k)
            n = n->left;
        else
            n = n->right;
    }
}

int BinTree::min() {
    Node *curr = root;
    while (curr->left) {
        curr = curr->left;
    }
    if (curr) {
        return curr->key;
    }
    return -1;
}

int BinTree::max() {
    Node *curr = root;
    while (curr->right) {
        curr = curr->right;
    }
    if (curr) {
        return curr->key;
    }
    return -1;
}
////начинаем от сюда))))) 0_0
///                       \|/
///                       |
///                      /\
///
Node *BinTree::del(Node *s) {
    return del(s->key);
}

Node *BinTree::del(int k) {
    Node *current = root;///узел работы
    Node *parent = NULL;
    Node *s;
    Node *r;
    Node d;
    while (current && current->key != k) {///выбираем куда идти
        parent = current;
        if (current->key > k)
            current = current->left;
        else
            current = current->right;
    }
    if (!current)
        throw invalid_argument("Ti sho? Key not found.");///ключ не найден

    else if (current->left == NULL)///есть ли левые потомки
        if (parent && parent->left == current) {///родитель справа
            parent->left = current->right;
            delete current;//дроп узел и сдвигаем вверх
            return  parent->left;
        } else if (parent && parent->right == current){/// родитель слева
            parent->right = current->right;
            delete current;//дроп узел и сдвиг вверх
            return parent->right;
        }
        else {/// попадаю в корень
            s = current->right;//сдвигаю корень
            root = s;
            return root;
        }
        else if (current -> right == NULL){/// правые потомки 0 тоже самое но зеркально
            if (parent && parent->left == current){
                parent->left = current->left;
                delete current;
                return parent->left;
            } else if (parent && parent->right == current){
                parent->right = current->left;
                delete current;
                return parent->right;
            } else {
                s= current->left;
                root =s;
                return root;
            }
        }
        s = current->right;/// если есть потомки , то идем в право
        if (s->left == NULL){//смотрим левые потомки
            current->key = s->key;// перенесли ключ
            current->right = s->right;// сдвиг вверх
            delete s;
            return current;
        }
    while (s->left != NULL){// бежим в крайний левый
        r =s;
        s=s->left;//выбрали левый
    }
    current->key = s->key;
    r->left=s->right;//выбраным узлом заменяем удаляемый
    delete s;
    return current;
}

elem* BinTree::BFS() {
    elem* runner;
    elem* h=new elem;
    elem* t;
    h->p = root;
    h->next = NULL;
    t = h;
    runner = h;
    while (h != NULL) {
        if (h->p->left != NULL) {
            elem* left_child = new elem;
            left_child->p = h->p->left;// учли 1 ребёнка
            left_child->next = NULL;// следующий пока нулевой
            runner->next = left_child;
            runner = runner->next;
        }
        if (h->p->right != NULL) {
            elem* right_child = new elem;
            right_child->p = h->p->right;// учитываем одного правого
            right_child->next = NULL;// следующий пустой
            runner->next = right_child;
            runner = runner->next;
        }
        cout << h->p->key << " " ;// Выводим 1 элемент
        h = h->next;//перехожу на следующий элем
    }
    cout << endl;
    return t;
}
void BinTree:: LRK (Node * r =NULL){
    if ( r == NULL) r = root;
    if (r->left) LRK(r->left);
    if (r->right) LRK(r->right);
    cout << r -> key<< " ";
}

int test() {
    int a[] = {13, 1, 45, 3, 4, 56, 13, };
    BinTree hah(10);
    BinTree heh(hah);
    BinTree hoh(6);
    BinTree hih(10, a);
    hoh = hah;

    hah.print();
    cout<< "////////////////////////////////////////////////////////////////"<< endl;
    heh.print();
    cout<< "////////////////////////////////////////////////////////////////"<< endl;
    hoh.print();
    cout<< "////////////////////////////////////////////////////////////////"<< endl;
    hih.print();
    cout<< "////////////////////////////////////////////////////////////////"<< endl;

    cout<< "min="<< hih.min()<< endl;
    cout<< "max="<< hih.max()<< endl;
    cout<< "search 3="<< hih.find(3)<< endl;
    cout<< "search 1000="<< hih.find(1000)<< endl;
    cout<< "delete 3="<< endl;
    hih.print();
    cout<<"//////////////////////////////////////////////////////////////////////////////////"<<endl;
    hih.del(3);
    hih.print();
    hih.LRK();
    cout <<endl;
    hih.BFS();

    BinTree hzh(12);
    int keys;
    hzh.print();
    cout<< "vvod key"<< endl;
    cin >> keys;
    hzh.del(keys);
    hzh.print();
}
int main(){
   test();
}