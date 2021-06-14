#include <iostream>

int ARR_SIZE = 1000;
static const int TOTAL_ALG = 5;

template <class T>
void swap(T *arr, int ind1, int ind2)
{
    T tmp = arr[ind1];
    arr[ind1] = arr[ind2];
    arr[ind2] = tmp;
}

template <class T>
void selectionSort(T *arr)
{
    for (int i = 0; i < ARR_SIZE; i++)
    {
        int min = i;
        for (int j = i + 1; j < ARR_SIZE; j++)
        {
            if (arr[min] > arr[j])
                min = j;
        }
        swap(arr, i, min);
    }
}

template <class T>
void insertionSort(T *arr)
{
    for (int i = 1; i < ARR_SIZE; i++)
    {
        int j = i;
        while (j > 0 && arr[j] < arr[j - 1])
        {
            swap(arr, j, j - 1);
            j--;
        }
    }
}

template <class T>
void bubbleSort(T *arr)
{
    for (int i = 0; i < ARR_SIZE - 1; i++)
    {
        int j = 0;
        while (j < ARR_SIZE)
        {
            if (arr[j - 1] > arr[j])
                swap(arr, j, j - 1);
            j++;
        }
    }
}

template <class T>
void merge(T *arr, int start, int middle, int end)
{
    T *tmp = new T[(end + 1) - start];
    int index = 0;
    int lStart = start, rStart = middle + 1;
    while (lStart <= middle && rStart <= end)
    {
        if (arr[lStart] <= arr[rStart])
        {
            tmp[index++] = arr[lStart++];
        }
        else
        {
            tmp[index++] = arr[rStart++];
        }
    }

    while (lStart <= middle)
    {
        tmp[index++] = arr[lStart++];
    }

    while (rStart <= end)
    {
        tmp[index++] = arr[rStart++];
    }

    for (int tmpCursor = 0, cursor = start; cursor <= end; tmpCursor++, cursor++)
    {
        arr[cursor] = tmp[tmpCursor];
    }

    delete[] tmp;
}

template <class T>
void mergeSort(T *arr, int start, int end)
{
    if (start != end)
    {
        int middle = (start + end) / 2;
        mergeSort(arr, start, middle);   // merging for the left half
        mergeSort(arr, middle + 1, end); // merging for the right half
        merge(arr, start, middle, end);
    }
}

template <class T>
void printArr(T *arr, char delim, char end)
{
    for (int i = 0; i < ARR_SIZE; i++)
    {
        std::cout << arr[i] << delim;
    }
    std::cout << end;
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
bool isSorted(T *v)
{
    for (int i = 1; i < ARR_SIZE; i++)
    {
        if (v[i] < v[i - 1])
        {
            return false;
        }
    }
    return true;
}