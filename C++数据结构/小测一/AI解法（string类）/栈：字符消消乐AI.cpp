#include <iostream>
#include <string> // 引入 string 库
using namespace std;

class mystack
{
public:
    char *data;
    int top_index;

    mystack(int num)
    {
        data = new char[num];
        top_index = -1;
    }

    ~mystack()
    {
        delete[] data;
    }

    bool isempty()
    {
        return top_index == -1;
    }

    void push(char ch)
    {
        top_index++;
        data[top_index] = ch;
    }

    void pop()
    {
        top_index--;
    }

    void see()
    {
        if (isempty())
        {
            cout << "EMPTY" << endl; // 增加 endl 换行
            return;
        }
        // 修改：从 0 开始正向遍历，保证输出字符串的顺序是正确的
        // 注意不要去修改 top_index 本身的值
        for (int i = 0; i <= top_index; i++)
        {
            cout << data[i];
        }
        cout << endl; // 增加 endl 换行
    }
};

int main()
{
    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s; // 一次读取一整段由英文字母组成的字符串（到换行符截止并自动跳过换行符）

        mystack sta(s.size()); // 根据字符串实际长度动态开辟空间，更省内存

        // 遍历字符串 s 中的每一个字符
        for (char ch : s)//这个遍历写法非常常见！一定要会，可以把：理解成in
        {
            if (!sta.isempty() && ch == sta.data[sta.top_index])
            {
                sta.pop(); // 如果栈顶元素和当前字符相同，相消
            }
            else
            {
                sta.push(ch); // 否则压入栈
            }
        }
        sta.see(); // 输出并换行
    }
    return 0;
}