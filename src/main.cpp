#include <iostream>

#include "SortingAlgorithms/QuickSort.h"
#include "SortingAlgorithms/BubbleSort.h"
#include "SortVisualiser/SortVisualiser.h"

int main()
{
    constexpr int SAMPLES = 200;
    constexpr int WIDTH = 900;
    constexpr int HEIGHT = 800;
    constexpr float DELAY = 10;
    std::string name = "Quicksort";
    
    SortVisualiser<QuickSort> SortVis = SortVisualiser<QuickSort>(
        WIDTH, 
        HEIGHT, 
        SAMPLES, 
        DELAY, 
        name
    );

    return 0;
}   