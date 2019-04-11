#include "QuickSort.h"

void QuickSort::sort()
{
    quicksort(0, m_l - 1);
    onFinish();
}

void QuickSort::swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int QuickSort::partition(int low, int high)
{
    int pivot = m_arr[high];  

    int i = low - 1;

    for (int j = low; j <= high - 1; j++)
    {
        if (m_arr[j] <= pivot)
        {
            i++;
            swap(&m_arr[i], &m_arr[j]);
            swapped_item(i, j, low, high);
        }
    }

    swap(&m_arr[i + 1], &m_arr[high]);
    swapped_item(i, high, low, high);
    return i + 1;
}

void QuickSort::quicksort(int low, int high)
{
    if (low < high)
    {
        int pi = partition(low, high);

        quicksort(low, pi - 1);
        quicksort(pi + 1, high); 
    }
}