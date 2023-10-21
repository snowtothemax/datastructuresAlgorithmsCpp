#include <iostream>
#include <string>
#include <array>
#include <algorithm>

void mergeSort(int *A, int lo, int hi)
{
    // base case
    if (lo>=hi)
    {
        return;
    }

    int middle = (lo-hi)/2;
    int size = lo-hi+1;
    int *B = new int[size]();
    //left
    mergeSort(A,lo,middle);
    //right
    mergeSort(A,middle+1,hi);
    //merge the left and the right
    for (int j = 0; j < size; j++)
    {
        if (A[j]<=B[count])
        {
            ret[j]=A[j];
        }
        else 
        {
            ret[j]=B[count];
            count++;
        }
    }

    
}

int main()
{
    int arr [] = {72,33,4,500,7,2};
    int *memArr = new int[6];

    std::copy(arr,arr+6,&memArr[0]);

    mergeSort(memArr,6);
    std::cout << memArr[1];
}
