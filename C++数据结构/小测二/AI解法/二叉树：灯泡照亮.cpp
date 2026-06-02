#include <iostream>

using namespace std;

const int MAXN = 1000; // 假设数据比较小
int cost[MAXN];

// 用来存储双向连接关系
int head[MAXN];
int to[MAXN * 2]; // 因为是双向的，所以边数乘2
int next_node[MAXN * 2];
int edge_cnt = 0;

// 记录每个房间有没有安装灯泡
bool has_bulb[MAXN];

// 记录最小花费，初始设为一个极大的数
int min_ans = 2147483647;
int n;

// 添加双向边
void add_edge(int u, int v)
{
    // u 连接到 v
    edge_cnt++;
    to[edge_cnt] = v;
    next_node[edge_cnt] = head[u];
    head[u] = edge_cnt;

    // v 连接到 u
    edge_cnt++;
    to[edge_cnt] = u;
    next_node[edge_cnt] = head[v];
    head[v] = edge_cnt;
}

// 检查当前这种装灯泡的方案，能不能把所有房间都照亮
bool check_all_lit()
{
    for (int i = 1; i <= n; i++)
    {
        bool lit = false;

        // 1. 如果自己装了灯泡，那就亮了
        if (has_bulb[i] == true)
        {
            lit = true;
        }
        else
        {
            // 2. 如果自己没装，去看看相连的邻居（父节点或子节点）有没有装
            for (int e = head[i]; e != 0; e = next_node[e])
            {
                int neighbor = to[e];
                if (has_bulb[neighbor] == true)
                {
                    lit = true;
                    break; // 只要有一个邻居装了，这个房间就亮了，不用往下看了
                }
            }
        }

        // 如果发现哪怕有一个房间没亮，这个方案就是失败的
        if (lit == false)
        {
            return false;
        }
    }
    return true; // 所有房间都亮了
}

// 递归探索每一个房间：装还是不装
// room_idx: 当前正在决定的房间编号
// current_cost: 走到当前这一步，已经花了多少钱
void dfs_search(int room_idx, int current_cost)
{

    // 剪枝小技巧：如果现在的花费已经比我们之前找到的最小花费还要大了，
    // 那就没必要往下算了，直接回头
    if (current_cost >= min_ans)
    {
        return;
    }

    // 边界条件：如果 1 到 n 号房间都决定完了 (room_idx > n)
    if (room_idx > n)
    {
        // 检查所有房间是否都被照亮了
        if (check_all_lit() == true)
        {
            // 如果比目前记录的最小花费还小，就更新它
            if (current_cost < min_ans)
            {
                min_ans = current_cost;
            }
        }
        return;
    }

    // 选择一：这个房间【不装】灯泡
    has_bulb[room_idx] = false;
    dfs_search(room_idx + 1, current_cost);

    // 选择二：这个房间【装】灯泡
    has_bulb[room_idx] = true;
    dfs_search(room_idx + 1, current_cost + cost[room_idx]);

    // 撤销状态，为了退回去尝试别的可能（回溯）
    has_bulb[room_idx] = false;
}

int main()
{
    if (!(cin >> n))
        return 0;

    for (int k = 1; k <= n; ++k)
    {
        int u, c, m;
        cin >> u >> c >> m;
        cost[u] = c;
        for (int i = 0; i < m; ++i)
        {
            int v;
            cin >> v;
            // 建立双向连接，因为灯泡光线是双向的
            add_edge(u, v);
        }
    }

    // 从 1 号房间开始做决定，初始花费为 0
    dfs_search(1, 0);

    // 输出最终找到的最小花费
    cout << min_ans << endl;

    return 0;
}