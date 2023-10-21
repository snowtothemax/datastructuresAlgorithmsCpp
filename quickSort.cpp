#include <iostream>
#include <string>
#include <array>

/// @brief Hoare's partition method
/// @param arr
/// @param lo
/// @param hi
/// @param p
int partition(int *arr, int lo, int hi, int p)
{
    int i = lo - 1;
    int j = hi + 1;
    while (true)
    {
        do
        {
            i++;
        } while (arr[i] < p);

        do
        {
            j--;
        } while (arr[j] > p);

        if (i >= j)
        {
            return j;
        }

        // swap
        int temp = arr[j];
        arr[j] = arr[i];
        arr[i] = temp;
    }
}

/// @brief Get the pivot value for an array to quicksort (median* for now)
/// @param arr The array to get the pivot for
/// @param lo The low index
/// @param hi The high index
/// @return An integer representing the pivot point for an array
int getPivotIndex(int *arr, int lo, int hi)
{
    if (lo > hi)
    {
        return -1;
    }

    int sum = 0;
    for (int i = lo; i < hi + 1; i++)
    {
        sum += arr[i];
    }

    int size = hi + 1 - lo;
    int average = sum / size;
    int difference = 0;
    int index = lo;
    for (int j = 0; j < hi + 1; j++)
    {
        difference = arr[j] - average;
        int oldDifference = arr[index] - average;
        if ((difference * difference) < (oldDifference * oldDifference))
        {
            index = j;
        }
    }

    return index;
}

void quickSort(int *arr, int lo, int hi)
{
    if (lo < hi)
    {
        int pi = getPivotIndex(arr, lo, hi);
        int partind = partition(arr, lo, hi, arr[pi]);
        quickSort(arr, lo, partind);
        quickSort(arr, partind + 1, hi);
    }
}

int main()
{
    int *arr = new int[9]();
    arr[0] = 198;
    arr[1] = 100;
    arr[2] = 2;
    arr[3] = 1;
    arr[4] = 145;
    arr[5] = 45;
    arr[6] = 3;
    arr[7] = 10;
    arr[8] = 1;
    quickSort(arr, 0, 8);
    for (int i = 0; i < 9; i++)
    {
        std::cout << arr[i] << "\n";
    }
}
