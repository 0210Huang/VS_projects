// 此题关键：必须快排，因为数据数量很大，也即这两个集合的容量很大，如果简单用for循环不断遍历，肯定会超时
#include <iostream>

using namespace std;

int a[100005];
int b[100005];
int ans[100005];

void quickSort(int arr[], int left, int right) // 用快速排序，防止超时
{
    if (left >= right)
        return;

    int i = left;
    int j = right;
    int key = arr[left];

    while (i < j)
    {
        while (i < j && arr[j] >= key)
        {
            j--;
        }
        arr[i] = arr[j];

        while (i < j && arr[i] <= key)
        {
            i++;
        }
        arr[j] = arr[i];
    }
    arr[i] = key;

    quickSort(arr, left, i - 1);
    quickSort(arr, i + 1, right);
}

int main()
{
    int n, m;

    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    cin >> m;
    for (int i = 0; i < m; i++)
    {
        cin >> b[i];
    }
    // 至此，两个集合输入完毕了
    quickSort(a, 0, n - 1);
    quickSort(b, 0, m - 1);
    // 至此，两个集合都排序完成了

    int i = 0, j = 0, k = 0;
    while (i < n && j < m) // 两者都没有到终点
    {
        if (i > 0 && a[i] == a[i - 1])
        {
            i++;
            continue;
        }
        if (j > 0 && b[j] == b[j - 1])
        {
            j++;
            continue;
        }
        // 在指针挑选的时候去重，这样可以更简便，因为原数组怎么样无所谓。不是在排序之后就立马去重
        if (a[i] == b[j]) // 相等时
        {
            ans[k] = a[i];
            k++;
            i++;
            j++;
        }
        else if (a[i] < b[j]) // 丢掉小的，因为已经排过序了，如果不匹配，以后这个小的不可能再匹配得上了
        {
            i++;
        }
        else // 同理
        {
            j++;
        }
    }

    if (k == 0)
    {
        cout << "EMPTY" << endl;
    }
    else // 输出结果
    {
        for (int x = 0; x < k; x++)
        {
            if (x > 0)
                cout << " ";
            cout << ans[x];
        }
        cout << endl;
    }

    return 0;
}