#include <iostream>
#include <string>
using namespace std;

class MinStack
{
private:
    int *main_stack;
    int *min_stack;
    int top_idx;
    int capacity;

public:
    MinStack(int cap)
    {
        capacity = cap;
        main_stack = new int[capacity];
        min_stack = new int[capacity];
        top_idx = -1;
    }

    ~MinStack()
    {
        delete[] main_stack;
        delete[] min_stack;
    }

    void push(int x)
    {
        top_idx++;
        main_stack[top_idx] = x;

        if (top_idx == 0)
        {
            min_stack[top_idx] = x;
        }
        else
        {
            min_stack[top_idx] = min(x, min_stack[top_idx - 1]);
        }
    }

    void pop()
    {
        top_idx--;
    }

    void top()
    {
        cout << main_stack[top_idx] << endl;
    }

    void getMin()
    {
        cout << min_stack[top_idx] << endl;
    }
};

int main()
{
    int q;
    cin >> q;
    MinStack sta(q);

    for (int i = 0; i < q; i++)
    {
        string op;
        cin >> op;//string的输入是直接到空格or换行结束，也就是截取一连串的字符
        if (op == "push")
        {
            int x;
            cin >> x;
            sta.push(x);
        }
        else if (op == "pop")
        {
            sta.pop();
        }
        else if (op == "top")
        {
            sta.top();
        }
        else if (op == "getMin")
        {
            sta.getMin();
        }
    }

    return 0;
}