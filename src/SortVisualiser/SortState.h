#pragma once

#include <memory>

typedef struct
{
    int* sortingArray;
    int samples;
    int currentId;
    int arrayChanges;
    int sectionStart;
    int sectionEnd;
    float delay;
} SortState;

typedef std::shared_ptr<SortState> statePtr;