#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>
#include <random>
#include <chrono>
#include <thread>
#include <ratio>

#include "Sort.h"
#include "SortState.h"
#include "SortRenderer.h"

template<typename T>
class SortVisualiser
{
private:
    statePtr m_sortState;
    SortRenderer m_renderer;

    T m_sorter;

    std::chrono::high_resolution_clock::time_point m_start;
    std::chrono::high_resolution_clock::time_point m_end;

    void initState(int samples, float delay) 
    {
        m_sortState = std::make_shared<SortState>();

        m_sortState->samples = samples;
        m_sortState->delay = 1000 * delay;
        m_sortState->currentId = -1;
        m_sortState->arrayChanges = 0;
        m_sortState->sectionStart = 0;
        m_sortState->sectionEnd = 0;
        m_sortState->sortingArray = new int[samples + 1];
    }

public:
    SortVisualiser(int width, int height, int samples, float delay, std::string algoName)
    {
        initState(samples, delay);

        m_sorter = T();
        m_renderer = SortRenderer(width, height);

        m_renderer.initSortState(m_sortState);
        m_sorter.initSortState(m_sortState);

        m_sorter.attachFinishCallback([]() {
            std::cout << "Done.\n";
        });

        start_sorting();
        m_renderer.startRender();

        exit(0);
    }

    void start_sorting()
    {   
        std::thread(
            [&] () 
            {
                sort_func();
            }
        ).detach();
    }

    void sort_func()
    {
        randomize();
        m_start = std::chrono::high_resolution_clock::now();
        m_sorter.sort();
    }

    // Helper
    void printarr()
    {
        m_sorter.printarr();
    }

    void randomize()
    {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<double> dist(0, m_sortState->samples);
        
        for(int i = 0; i <  m_sortState->samples; i++)
        {
            m_sortState->sortingArray[i] = (int) dist(mt);
            std::this_thread::sleep_for(
                std::chrono::microseconds((int) m_sortState->delay)
            );
        }
    }

    ~SortVisualiser()
    {
        delete []m_sortState->sortingArray;
    }
};