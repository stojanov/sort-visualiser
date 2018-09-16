#include <iostream>

#include "Quicksort.h"
#include "BubbleSort.h"
#include "SortVisualiser.h"

int main()
{
    const int SAMPLES = 1000;
    const int WIDTH = 1000;
    const int HEIGHT = 800;
    const int DELAY = 2;
    std::string name = "Quicksort";
    
    // Press S to start
    // It is built so you can change algorithms very easy.
    SortVisualiser<Quicksort> SortVis = SortVisualiser<Quicksort>(WIDTH, HEIGHT, SAMPLES, DELAY, name);


    return 0;
}   