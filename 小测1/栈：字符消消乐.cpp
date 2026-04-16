#include<iostream>
using namespace std;

class mystack{
    public:
        char *data;
        int top_index;

        mystack(int num){
            data = new char[num];
            top_index = -1;
        }

        ~mystack(){
            delete[] data;
        }

        bool isempty(){
            return top_index == -1;
        }

        void push(char ch){
            top_index++;
            data[top_index] = ch;
        }

        void pop(){
            top_index--;
        }

        // void see(){
        //     if(isempty()){
        //         cout << "EMPTY";
        //         return;
        //     }
        //     while(top_index!=-1){
        //         cout << data[top_index];
        //         top_index--;
        //     }
        //     return;
        // }
        //上面的出现了没有换行、输出顺序反了的问题，应该从0开始输出直到top_index才对
        void see(){
            if(isempty()){
                cout << "EMPTY" << endl;
                return;
            }
            for (int i = 0; i <= top_index;i++){
                cout << data[i];
            }
            cout << endl;//结束之后，换个行
            return;
        }
};

int main(){
    int n;
    cin >> n;
    for (int i = 0; i < n;i++){
        mystack sta(10005);//多开一点更安全
        //char ch;
        // while (cin >> ch)
        // {
        //     if(!sta.isempty()&&ch==sta.data[sta.top_index]){//如果要相消
        //         sta.pop();//直接退掉上一个
        //     }
        //     else{
        //         sta.push(ch);
        //     }
        // }
        // 上面这个输入方式是不对的，while（cin>>）会导致一直在吞入数据直到全部结束，不会因为换行or空格而停下来！不要使用！

        //最好的办法是每一行先读到一个字符数组里面去，然后再处理，不要边读边处理，如下面
        char arr[10005];
        cin >> arr;
        int j = 0;
        while(arr[j]!='\0'){
            char ch = arr[j];//拿出来
            if (!sta.isempty() && ch == sta.data[sta.top_index]){ // 如果要相消
                sta.pop();//直接退掉上一个
            }
            else{
                sta.push(ch);//放进去
            }
            j++;
        }
        sta.see();
    }
    return 0;
}
//至此，代码没有问题了