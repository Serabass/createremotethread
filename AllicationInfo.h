//
// Created by Serabass on 30.11.2018.
//

#ifndef CREATEREMOTETHREAD_ALLICATIONINFO_H
#define CREATEREMOTETHREAD_ALLICATIONINFO_H

#include <windows.h>

struct AllocationInfo {
    LPVOID address;
    SIZE_T size;

    int calculateOffset(int step, int fn);
};

#endif //CREATEREMOTETHREAD_ALLICATIONINFO_H
