#pragma once 

#include <functional>
#include <iostream>

class Sort
{
private:
    std::function<void(int, int, int, int)> m_swap_func;

protected:
    int *m_arr;
    int m_l;
    
    void assign_arr(int *arr, int l) 
    {
        m_arr = arr;
        m_l = l;
    }

    void swapped_item(int id, int next_id, int section_start, int section_end) 
    {
        m_swap_func(id, next_id, section_start, section_end);
    };

public:
    Sort() {}
    Sort(int *arr, int l) 
    : m_arr(arr), m_l(l) {}

    void assign_swap_func(std::function<void(int, int, int, int)> func) 
    {
        m_swap_func = func;
    }

    void printarr()
    {
        std::cout << "\n";
        for(int i = 0; i < m_l; i++)
            std::cout << " " << m_arr[i];
        std::cout << "\n";
    }
};