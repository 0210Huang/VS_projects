//栈的特点：先入后出，后入先出

class mystack{
    private:
        int *data;//用来记录栈的位置
        int top_index;//记录栈顶元素的下标，而不需要用指针
        int cap;

    public:
        // 构造函数
        mystack(int num)
        {
            cap = num;
            data = new int[num];
            top_index = -1; // 一开始是-1，记住，方便判断栈空
        }

    //析构函数
    ~mystack(){
        delete[] data;
    }

    bool empty(){
        return top_index == -1;
    }

    int peek(){
        if(top_index>=0) 
            return data[top_index];
        return -1;
    }

    void push(int num){
        top_index++;
        data[top_index] = num;
    }

    int pop(){
        top_index--;
        return data[top_index + 1];
    }
};