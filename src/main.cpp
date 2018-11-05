#include <iostream>

#include "SortingAlgorithms/Quicksort.h"
#include "SortingAlgorithms/BubbleSort.h"
#include "SortVisualiser/SortVisualiser.h"

int main()
{
    const int SAMPLES = 1000;
    const int WIDTH = 1000;
    const int HEIGHT = 800;
    const float DELAY = 2;
    std::string name = "Quicksort";
    
    SortVisualiser<Quicksort> SortVis = SortVisualiser<Quicksort>(
        WIDTH, 
        HEIGHT, 
        SAMPLES, 
        DELAY, 
        name
    );

    return 0;
}   