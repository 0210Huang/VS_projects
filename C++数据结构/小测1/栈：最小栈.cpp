#include<iostream>
using namespace std;

class mystack{
public:
    int *data;
    int top_index;

    mystack(int num)
    {
        data = new int[num];
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

    void push(int num)
    {
        top_index++;
        data[top_index] = num;
    }

    void pop()
    {
        top_index--;
    }

    void top(){
        cout << data[top_index] << endl;
        return;
    }

    void getMin(){
        int min = data[0];
        for (int i = 0; i <= top_index;i++){
            if(data[i]<min)
                min = data[i];
        }
        cout << min << endl;
    }
};

int main(){
    int q;
    cin >> q;
    mystack sta(10000);
    for (int i = 0; i < q;i++){//每一次操作
        char arr[100];
        cin >> arr;
        if(arr[0]=='p'&&arr[1]=='o'&&arr[2]=='p'){
            sta.pop();
        }
        if (arr[0] == 't' && arr[1] == 'o' && arr[2] == 'p'){
            sta.top();
        }
        if (arr[0] == 'g' && arr[1] == 'e' && arr[2] == 't' && arr[3] == 'M' && arr[4] == 'i' && arr[5] == 'n'){
            sta.getMin();
        }
        // if (arr[0] == 'p' && arr[1] == 'u' && arr[2] == 's'&&arr[3]=='h'){
        //     int tem = arr[5];//这是不行的！cin碰到空格就会停止！
        //     int res=0;
        //     while (arr[tem] != '\0')
        //     {
        //         res += arr[tem];
        //         res *= 10;//让出下一位
        //         tem++;
        //     }
        //     res /= 10;//撤销最后多余的10
        //     sta.push(res);
        // }
        //修改如下
        if (arr[0] == 'p' && arr[1] == 'u' && arr[2] == 's' && arr[3] == 'h')
        {
            int val;
            cin >> val; // 直接把后面的数字读进 val 里！
            sta.push(val);
        }
    }
    return 0;
}
//至此，全部修改完毕