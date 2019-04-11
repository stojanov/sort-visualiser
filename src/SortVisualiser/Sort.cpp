#include "Sort.h"

void Sort::initSortState(statePtr state) 
{
    m_sortState = state;
    m_arr = state->sortingArray;
    m_l = state->samples;
}

void Sort::swapped_item(int id, int nextId, int sectionStart, int sectionEnd) 
{
    m_sortState->currentId = id;
    m_sortState->sectionStart = sectionStart;
    m_sortState->sectionEnd = sectionEnd;
    m_sortState->arrayChanges++;

    std::this_thread::sleep_for(
        std::chrono::microseconds((int) m_sortState->delay)
    );
}

void Sort::attachFinishCallback(voidCallback fn)
{
    m_finishCallback = fn;
}

void Sort::onFinish()
{
    m_sortState->currentId = -1;
    if (m_finishCallback) 
    {
        m_finishCallback();
    }
}

void Sort::printarr()
{
    std::cout << "\n";
    for(int i = 0; i < m_l; i++)
        std::cout << " " << m_arr[i];
    std::cout << "\n";
}