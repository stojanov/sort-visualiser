#pragma once 

#include <functional>
#include <iostream>
#include <chrono>
#include <thread>
#include <ratio>

#include "SortState.h"

typedef std::function<void()> voidCallback;

class Sort
{
private:
    statePtr m_sortState;
    voidCallback m_finishCallback;

protected:
    int *m_arr;
    int m_l;

    void swapped_item(int id, int nextId, int sectionStart, int sectionEnd);
    void onFinish();
public:
    Sort() = default;

    void initSortState(statePtr state);
    void attachFinishCallback(voidCallback fn);
    void printarr();
};