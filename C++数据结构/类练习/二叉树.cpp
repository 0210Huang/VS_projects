#include<iostream>
using namespace std;

class binaryTree{
public:
    struct Node{
        Node *left, *right;
        int data;

        Node():left(NULL),right(NULL){}
        Node(int item, Node *L = NULL, Node *R = NULL) : data(item), left(L), right(R) {}
        ~Node(){}
    };

    Node *root;

    binaryTree():root(NULL){}//构造函数
    ~binaryTree(){
        clear(root);
    }

    void clear(Node *&t){//递归实现清空二叉树，传入的是指针的引用

        clear(t->left);
        clear(t->right);
        delete t;
        t = NULL;
    }
};

int main(){
    int n;
    cin >> n;

    binaryTree tree;

}