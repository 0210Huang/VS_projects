#include<iostream>
using namespace std;


struct mystack{
    int *data;
    int top_index;

    mystack(int n){
        data = new int[n];
        top_index = -1;
    }

    ~mystack(){
        delete[] data;
    }

    void push(int num){
        top_index++;
        data[top_index] = num;
    }

    int pop(){
        top_index--;
        return data[top_index + 1];
    }

    bool empty(){
        if(top_index==-1)
            return 1;
        return 0;
    }

    int peek(){
        if(top_index>=0)
            return data[top_index];
        return -1;
    }
};

int main(){
    int num;
    cin >> num;
    int in_seq[num];
    int out_seq[num];
    for (int i = 0; i < num;i++){
        cin >> in_seq[i];
    }
    for (int i = 0; i < num; i++)
    {
        cin >> out_seq[i];
    }
    //至此，顺序记录完毕了

    mystack stack(num);
    int out = 0;//只向当前需要的车厢

    for (int i = 0; i < num;i++){
        stack.push(in_seq[i]);//新车厢无脑进死胡同

        while(!stack.empty()&&stack.peek()==out_seq[out]){//如果正好是需要的在栈顶
            stack.pop();//车开出去
            out++;//看下一辆需要的车
        }
    }
    if (stack.empty())//只需要看栈是不是空的就可以
    {
        cout << "YES" << endl;
    }
    else
    {
        cout << "NO" << endl;
    }

        return 0;
}