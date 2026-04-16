//队列的特点：先入先出，后入后出

class myqueue{
    private:
        int *data;
        int front; // 队头元素本身，只需要记录下标就可以
        int rear;//队尾元素的下一个，只需要记录下标就可以
        int cap;

    public:
        //构造函数
        myqueue(int num){
            cap = num;
            data = new int[num];
            front = 0;
            rear = 0;
        }

        ~myqueue(){
            delete[] data;
        }

        bool isempty(){
            return front == rear;
        }

        bool isfull(){
            return (rear + 1) % cap == front;//浪费一个空间，直接找rear再下一个
        }

        void push(int num){
            if(isfull())
                return;
            data[rear] = num;
            rear = (rear + 1) % cap;
        }
};