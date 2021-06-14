#include <iostream>
#include <cstdlib>
#include <time.h>
#include <vector>

bool isSorted(std::vector<int> &v)
{
    for (int i = 1; i < v.size(); i++)
    {
        if (v[i] < v[i - 1])
        {
            return false;
        }
    }
    return true;
}

void print(std::vector<int> &v)
{
    for (const auto &n : v)
    {
        std::cout << n << " ";
    }
    std::cout << std::endl;
}

void print(int *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

template <class T>
int partition(T *arr, int start, int end)
{
    int pivot = end, i = start - 1, j = start;
    while (j < pivot)
    {
        if (arr[j] < arr[pivot])
        {
            i++;
            T tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
        }
        j++;
    }
    i++;
    T tmp = arr[i];
    arr[i] = arr[pivot];
    arr[pivot] = tmp;
    return i;
}

template <class T>
void quickSort(T *arr, int start, int end)
{
    if (start > end)
    {
        return;
    }
    int pivot = partition(arr, start, end);
    quickSort(arr, start, pivot - 1);
    quickSort(arr, pivot + 1, end);
}

template <class T>
bool isSorted(T *v, int n)
{
    for (int i = 1; i < n; i++)
    {
        if (v[i] < v[i - 1])
        {
            return false;
        }
    }
    return true;
}

int main()
{
    srand(time(nullptr));
    int *arr = new int[100000];

    for (int i = 0; i < 100000; i++)
    {
        arr[i] = rand() % 100000;
    }

    // print(arr, 10);
    quickSort(arr, 0, 100000 - 1);
    // print(arr, 10);
    std::cout << isSorted(arr, 100000) << std::endl;
    delete[] arr;
}