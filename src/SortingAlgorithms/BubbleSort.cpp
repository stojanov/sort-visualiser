#include "BubbleSort.h"

void BubbleSort::sort()
{
    int sortedElements = 0;
    bool swapped = true;
    while(swapped)
    {
        swapped = false;
        for(int i = 0; i < m_l - 1; i++)
        {
            if(m_arr[i] > m_arr[i + 1])
            {
                swapped = true;
                int temp = m_arr[i];
                m_arr[i] = m_arr[i + 1];
                m_arr[i + 1] = temp;
                swapped_item(i, i + 1, i, (m_l - 1) - sortedElements);
            }
        }
        sortedElements++;
    }

    onFinish();
}