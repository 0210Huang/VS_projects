#include <iostream>
using namespace std;

int cost[10];
int head[10];
int to[20];
int next_node[20];
int edge_cnt;

bool has_bulb[10];

// 记录最小花费，初始设为一个极大的数
int min_ans = 10000000;
int n;

// 添加双向连接
void add_edge(int u, int v)
{
    edge_cnt++;
    to[edge_cnt] = v;
    next_node[edge_cnt] = head[u];
    head[u] = edge_cnt;

    edge_cnt++;
    to[edge_cnt] = u;
    next_node[edge_cnt] = head[v];
    head[v] = edge_cnt;
}

// 检查是否所有房间都被照亮
bool check_all_lit()
{
    for (int i = 1; i <= n; i++)
    {
        bool lit = false;
        if (has_bulb[i] == true)
        { // 如果自己装了灯泡，那就亮了
            lit = true;
        }
        else
        {
            // 如果自己没装，去看看相连的邻居有没有装
            for (int e = head[i]; e != 0; e = next_node[e])
            {
                int neighbor = to[e];
                if (has_bulb[neighbor] == true)
                {
                    lit = true;
                    break;
                }
            }
        }

        if (lit == false)
        { // 只要有一个没亮，就返回失败
            return false;
        }
    }
    return true;
}

// 递归遍历所有的装灯泡组合
void dfs_search(int room_idx, int current_cost)
{
    if (current_cost >= min_ans)
    { // 剪枝：如果当前花费已经超过最小值，不用继续算了
        return;
    }

    if (room_idx > n)
    { // 所有的房间都决定完了，开始检查
        if (check_all_lit() == true)
        {
            // 如果所有房间都亮了，更新最小花费
            if (current_cost < min_ans)
            {
                min_ans = current_cost;
            }
        }
        return;
    }

    // 选择一：这个房间不装灯泡
    has_bulb[room_idx] = false;
    dfs_search(room_idx + 1, current_cost);

    // 选择二：这个房间装灯泡
    has_bulb[room_idx] = true;
    dfs_search(room_idx + 1, current_cost + cost[room_idx]);

    // 恢复现场（回溯）
    has_bulb[room_idx] = false;
}

int main()
{
    cin >> n;
    for (int k = 1; k <= n; ++k)
    { // 读取每个节点和它的花费、子节点
        int u;
        int c;
        int m;
        cin >> u >> c >> m;
        cost[u] = c;
        for (int i = 0; i <= m; ++i)
        {
            int v;
            cin >> v;
            add_edge(u, v); // 建立双向连接
        }
    }

    // 从1号房间开始做决定，初始花费为0
    dfs_search(1, 0);

    cout << min_ans << endl;

    return 0;
}