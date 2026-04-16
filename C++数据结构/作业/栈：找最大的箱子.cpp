// #include<iostream>
// using namespace std;

// int main(){
// int num;
// cin>>num;
// int a[num];
// for(int i=0;i<num;i++){
//     cin>>a[i];
// }f
// //至此，已经输入完成了
// for(int i=0;i<num;i++){//i最大为num-1
//     int current=a[i];
//     if(i==num-1){//如果这个i是最后一个数了
//         cout<<0;
//         break;
//     }

//     int j=i+1;//令j为下一个数
//     while((!(a[j]>a[i]))&&j!=num){
//         j++;
//     }//移动j，直至遇到了第一个高的箱子or遍历结束
//     if(j==num){//遍历结束
//         cout<<0<<" ";
//     }
//     else{
//         cout<<j+1<<" ";
//     }
// }
// return 0;
// }

#include <iostream>
using namespace std;
// 使用栈，更高效，能够比上面的更好
struct mystack
{
    int *data; // 用于存放数据
    int top_index;

    mystack(int n)
    {
        data = new int[n];
        top_index = -1; //-1表示栈为空
    }
    ~mystack()
    {
        delete[] data;
    }

    void push(int num)
    { // 入栈
        top_index++;
        data[top_index] = num;
    }

    int pop()
    { // 出栈
        if (top_index >= 0)
            top_index--;
        return data[top_index + 1];
    }

    bool empty()
    {
        return top_index == -1;
    }

    int peek()
    {
        if (top_index >= 0)
            return data[top_index];
        else
            return -1;
    }
};

int main()
{
    int n;
    cin >> n;
    int a[n];
    int ans[n];

    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        ans[i] = 0; // 顺便把答案都默认设为0（找不到的情况）
    }
    // 至此，输入完成了
    mystack stack(n);
    // 注意这个栈里面应该存放的是下标而不是元素！
    for (int i = 0; i < n; i++)
    {
        while (!stack.empty() && a[i] > a[stack.peek()])
        { // 后面来的箱子更高时
            int tem = stack.pop();
            ans[tem] = i + 1;
        }
        stack.push(i); // 比较完成了，然后当前箱子入栈等待
    }

    for (int i = 0; i < n; i++)
    {
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}