#include <iostream>
#include <string>
#include <array>

template <typename T>
class Stack {
    public:
        void push(T val)
        {
            if (head >= 99)
            {
                return;
            }
            head++;
            arr[head] = val;
        }

        T pop()
        {
            if (head == -1)
            {
                return -1;
            }
            int ret = arr[head];
            head--;
            return ret;
        }

        int size()
        {
            return head;
        }
        
        Stack() {
            head = 0;
            arr = new T[100];
        }
    private:
        T *arr;
        int head;
};

int main()
{
    Stack<int>* stack = new Stack<int>();
    stack->push(1);
    stack->push(2);
    stack->push(3);
    stack->push(4);

    while (stack->size()>0)
    {
        std::cout << stack->pop();
    }
}
