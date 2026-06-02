#include <iostream>

using namespace std;

int a[1005];
int b[1005];
int all[2005];
int both[1005];
int only[1005];

int main()
{
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    for (int i = 0; i < m; i++)
    {
        cin >> b[i];
    }

    int all_cnt = 0;
    for (int i = 0; i < n; i++)//把a[n]的塞进all里面
    {
        bool exist = false;
        for (int j = 0; j < all_cnt; j++)//先判断是否已经存在
        {
            if (all[j] == a[i])
            {
                exist = true;
            }
        }
        if (!exist)//若不存在就可以放入了
        {
            all[all_cnt] = a[i];
            all_cnt++;
        }
    }
    for (int i = 0; i < m; i++)//同样地，处理b[m]
    {
        bool exist = false;
        for (int j = 0; j < all_cnt; j++)
        {
            if (all[j] == b[i])
            {
                exist = true;
            }
        }
        if (!exist)
        {
            all[all_cnt] = b[i];
            all_cnt++;
        }
    }
//至此，all数组完成了去重
//做一个冒泡排序，使得顺序满足条件
    for (int i = 0; i < all_cnt - 1; i++)
    {
        for (int j = 0; j < all_cnt - 1 - i; j++)
        {
            if (all[j] > all[j + 1])
            {
                int temp = all[j];
                all[j] = all[j + 1];
                all[j + 1] = temp;
            }
        }
    }
//至此，all数组搞定了
    if (all_cnt == 0)
    {
        cout << "Empty";
    }
    else
    {
        for (int i = 0; i < all_cnt; i++)
        {
            if (i > 0)
                cout << " ";
            cout << all[i];
        }
    }
    cout << endl;
//输出all数组

    int both_cnt = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (a[i] == b[j])
            {
                bool exist = false;
                for (int k = 0; k < both_cnt; k++)
                {
                    if (both[k] == a[i])
                    {
                        exist = true;
                    }
                }
                if (!exist)
                {
                    both[both_cnt] = a[i];
                    both_cnt++;
                }
            }
        }
    }

    for (int i = 0; i < both_cnt - 1; i++)
    {
        for (int j = 0; j < both_cnt - 1 - i; j++)
        {
            if (both[j] > both[j + 1])
            {
                int temp = both[j];
                both[j] = both[j + 1];
                both[j + 1] = temp;
            }
        }
    }

    if (both_cnt == 0)
    {
        cout << "Empty";
    }
    else
    {
        for (int i = 0; i < both_cnt; i++)
        {
            if (i > 0)
                cout << " ";
            cout << both[i];
        }
    }
    cout << endl;

    int only_cnt = 0;
    for (int i = 0; i < n; i++)
    {
        bool found = false;
        for (int j = 0; j < m; j++)
        {
            if (a[i] == b[j])
            {
                found = true;
            }
        }
        if (!found)
        {
            bool exist = false;
            for (int k = 0; k < only_cnt; k++)
            {
                if (only[k] == a[i])
                {
                    exist = true;
                }
            }
            if (!exist)
            {
                only[only_cnt] = a[i];
                only_cnt++;
            }
        }
    }

    for (int i = 0; i < only_cnt - 1; i++)
    {
        for (int j = 0; j < only_cnt - 1 - i; j++)
        {
            if (only[j] > only[j + 1])
            {
                int temp = only[j];
                only[j] = only[j + 1];
                only[j + 1] = temp;
            }
        }
    }

    if (only_cnt == 0)
    {
        cout << "Empty";
    }
    else
    {
        for (int i = 0; i < only_cnt; i++)
        {
            if (i > 0)
                cout << " ";
            cout << only[i];
        }
    }
    cout << endl;

    return 0;
}