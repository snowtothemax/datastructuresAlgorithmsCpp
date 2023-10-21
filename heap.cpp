#include <iostream>
#include <string>
#include <array>

#define HEAP_SIZE 100


/// @brief 
/// @param arr 
/// @param size 
void heapify(int* arr,int size, int i)
{
        int largestInd = i;
        int leftInd = 2*i + 1;
        int rightInd = 2*i + 2;

        if (leftInd < size && arr[leftInd] > arr[i])
        {
            largestInd = leftInd;
        }
        if (rightInd < size && arr[rightInd] > arr[i])
        {
            largestInd = rightInd;
        }

        if (largestInd != i)
        {
            int largestVal = arr[largestInd];
            int val = arr[i];
            arr[largestInd] = val;
            arr[i] = largestVal;

            heapify(arr,size,largestInd);
        }
}

/// @brief 
/// @param arr 
/// @return 
int peek(int* arr)
{
    return arr[0];
}

/// @brief 
/// @param arr 
/// @param size 
void buildHeap(int* arr, int size)
{
    int startingInd = (size/2)-1;
    for (int i = startingInd; i >= 0; i--)
    {
        heapify(arr,size,i);
    }
}

class Heap{
    public:
        Heap(){
            arr = new int[HEAP_SIZE];
            size=0;
        }
        void insert(int val)
        {
            if (size<HEAP_SIZE)
            {
                arr[size] = val;
                size=size+1;
                buildHeap(arr,size);
            }
        }
        int peek()
        {
            if (size != 0)
            {
                return arr[0];
            }
            return INT_MIN;
        }
    private:
        int *arr;
        int size;
};

/// @brief 
/// @return 
int main()
{
    Heap *heap = new Heap();
    for (int i = 0; i < 20; i++)
    {
        heap->insert(i);
        std::cout<<heap->peek() << "\n";
    }
}