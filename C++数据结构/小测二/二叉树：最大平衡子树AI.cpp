#include <iostream>
using namespace std;

int left_child[10005];
int right_child[10005];

// 所有平衡子树中最大的节点数量
int max_ans = 0;

// 求绝对值
int my_abs(int a)
{
    if (a < 0)
        return -a;
    return a;
}

// 求最大值
int my_max(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    return b;
}

// 递归遍历，用引用传递
void dfs(int u, int &height, int &size, bool &is_bal)
{
    if (u == 0)
    { // 到最后的节点时，开始返回，叶子结点是平衡的，给一个初始化
        height = 0;
        size = 0;
        is_bal = true;
        return;
    }

    // 左孩子
    int left_h;
    int left_s;
    bool left_b;
    dfs(left_child[u], left_h, left_s, left_b);

    // 右孩子
    int right_h;
    int right_s;
    bool right_b;
    dfs(right_child[u], right_h, right_s, right_b);

    // 更新当前节点的高度和大小
    height = my_max(left_h, right_h) + 1;
    size = left_s + right_s + 1;

    // 判断当前节点这棵树是否是平衡二叉树：左右子树平衡，他们的高度差不超过1
    if (left_b == true && right_b == true && my_abs(left_h - right_h) <= 1)
    {
        is_bal = true;

        // 如果当前是平衡树，更新最大值
        if (size > max_ans)
        {
            max_ans = size;
        }
    }
    else
    { // 如果不是，就改flag
        is_bal = false;
    }
}

int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i)//注意从1开始，方便找到相应的左右孩子
    { // 编号为i的节点，输进来左右孩子的编号
        cin >> left_child[i] >> right_child[i];
    }
    // 根节点初始化
    int root_height = 0;
    int root_size = 0;
    bool root_is_bal = true;
    dfs(1, root_height, root_size, root_is_bal); // 从1编号开始递归
    cout << max_ans << endl;

    return 0;
}