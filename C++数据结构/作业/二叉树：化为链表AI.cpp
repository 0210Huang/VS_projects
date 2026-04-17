#include <iostream>

using namespace std;


class binaryTree
{
public:
    
    struct Node
    {
        Node *left, *right; 
        int data;           

        
        Node() : left(NULL), right(NULL) {}
        Node(int item, Node *L = NULL, Node *R = NULL) : data(item), left(L), right(R) {}
        ~Node() {}
    };

    Node *root; 

    
    binaryTree() : root(NULL) {}

    
    ~binaryTree()
    {
        clear(root);
    }

    
    void clear(Node *&t)
    {
        if (t == NULL)
            return;
        clear(t->left);
        clear(t->right);
        delete t;
        t = NULL;
    }
};





void preOrderGather(binaryTree::Node *t, binaryTree::Node **arr, int &index)
{
    if (t == NULL)
        return;
    arr[index++] = t;                     
    preOrderGather(t->left, arr, index);  
    preOrderGather(t->right, arr, index); 
}




int main()
{
    int n;
    
    if (!(cin >> n) || n == 0)
    {
        return 0;
    }

    
    binaryTree tree;

    
    binaryTree::Node **nodes = new binaryTree::Node *[n + 1];
    int *left_child = new int[n + 1];
    int *right_child = new int[n + 1];
    int *in_degree = new int[n + 1];

    
    for (int i = 0; i <= n; i++)
    {
        nodes[i] = NULL;
        left_child[i] = 0;
        right_child[i] = 0;
        in_degree[i] = 0;
    }

    
    for (int i = 1; i <= n; ++i)
    {
        int val, left, right;
        cin >> val >> left >> right;
        nodes[i] = new binaryTree::Node(val); 
        left_child[i] = left;
        right_child[i] = right;

        if (left != 0)
            in_degree[left]++;
        if (right != 0)
            in_degree[right]++;
    }

    
    int root_idx = 1;
    for (int i = 1; i <= n; ++i)
    {
        if (in_degree[i] == 0)
        {
            root_idx = i;
            break;
        }
    }

    
    for (int i = 1; i <= n; ++i)
    {
        if (left_child[i] != 0)
            nodes[i]->left = nodes[left_child[i]];
        if (right_child[i] != 0)
            nodes[i]->right = nodes[right_child[i]];
    }

    tree.root = nodes[root_idx]; 

    
    
    binaryTree::Node **preOrderArray = new binaryTree::Node *[n];
    int index = 0;

    
    preOrderGather(tree.root, preOrderArray, index);

    
    for (int i = 0; i < n - 1; i++)
    {
        preOrderArray[i]->left = NULL;                  
        preOrderArray[i]->right = preOrderArray[i + 1]; 
    }
    
    preOrderArray[n - 1]->left = NULL;
    preOrderArray[n - 1]->right = NULL;

    
    binaryTree::Node *curr = tree.root;
    while (curr != NULL)
    {
        cout << curr->data; 
        if (curr->right != NULL)
            cout << " ";
        curr = curr->right;
    }
    cout << endl;

    
    delete[] nodes;
    delete[] left_child;
    delete[] right_child;
    delete[] in_degree;
    delete[] preOrderArray;

    return 0;
}