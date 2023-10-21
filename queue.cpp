#include <iostream>
#include <string>
#include <array>

#define ARR_CAPACITY 100

template <typename T>
class Queue {
    public:
        Queue(){
            head=0;
            tail=0;
            capacity=0;
        }

        void push(int val)
        {
            if (capacity<ARR_CAPACITY)
            {
                arr[head]=val;
                capacity++;
                head++;
                head=head%ARR_CAPACITY;
            }
        }

        int pop()
        {
            if (capacity>0)
            {
                int retval = arr[tail];
                tail++;
                capacity--;
                tail=tail%ARR_CAPACITY;
                return retval;
            }
            else return -1;
        }

    private:
        int head;
        int tail;
        int capacity;
        T arr [ARR_CAPACITY];
};

int main()
{
    Queue* queue = new Queue();
    if (queue->pop() == -1)
    {
        std::cout << "Good \n";
    }
    queue->push(1);
    queue->pop();
    for (int i = 0; i < ARR_CAPACITY; i++)
    {
        queue->push(i);
    }
    for (int i = 0; i < ARR_CAPACITY; i++)
    {
        std::cout << queue->pop();
    }
    std::cout << queue->pop();
}
