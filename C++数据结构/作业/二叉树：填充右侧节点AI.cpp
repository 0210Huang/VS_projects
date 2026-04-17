#include <iostream>

using namespace std;


struct Node
{
    int id; 
    int val;
    Node *left;
    Node *right;
    Node *next;

    
    Node() : id(0), val(0), left(NULL), right(NULL), next(NULL) {}
};

int main()
{
    int n;
    
    if (!(cin >> n))
    {
        return 0;
    }

    
    
    
    Node **nodes = new Node *[n + 1];
    int *in_degree = new int[n + 1];

    
    for (int i = 0; i <= n; i++)
    {
        nodes[i] = new Node();
        nodes[i]->id = i; 
        in_degree[i] = 0;
    }

    
    for (int i = 1; i <= n; i++)
    {
        int val, left, right;
        cin >> val >> left >> right;

        nodes[i]->val = val;

        if (left != 0)
        {
            nodes[i]->left = nodes[left];
            in_degree[left]++;
        }
        if (right != 0)
        {
            nodes[i]->right = nodes[right];
            in_degree[right]++;
        }
    }

    
    Node *root = NULL;
    for (int i = 1; i <= n; i++)
    {
        if (in_degree[i] == 0)
        {
            root = nodes[i];
            break;
        }
    }

    
    
    
    
    Node *que[2000]; 
    int head = 0, tail = 0;

    if (root != NULL)
    {
        que[tail++] = root; 
    }

    
    while (head < tail)
    {
        int level_size = tail - head; 

        
        for (int i = 0; i < level_size; i++)
        {
            Node *tmp = que[head++]; 

            
            if (i < level_size - 1)
            {
                tmp->next = que[head];
            }

            
            if (tmp->left != NULL)
                que[tail++] = tmp->left;
            if (tmp->right != NULL)
                que[tail++] = tmp->right;
        }
    }

    
    
    
    for (int i = 1; i <= n; i++)
    {
        if (nodes[i]->next != NULL)
        {
            cout << nodes[i]->next->id << endl; 
        }
        else
        {
            cout << 0 << endl; 
        }
    }

    
    for (int i = 0; i <= n; i++)
    {
        delete nodes[i];
    }
    delete[] nodes;
    delete[] in_degree;

    return 0;
}