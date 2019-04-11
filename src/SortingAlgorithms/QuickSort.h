#pragma once

#include "../SortVisualiser/Sort.h"

#include <iostream>

class QuickSort : public Sort
{
public:
    QuickSort() = default;
    
    void sort();
    void swap(int* a, int *b);
    int partition(int low, int high);
    void quicksort(int low, int high);
};
