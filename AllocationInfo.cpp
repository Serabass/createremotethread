//
// Created by Serabass on 30.11.2018.
//

#include "AllicationInfo.h"

int AllocationInfo::calculateOffset(int step, int fn) {
    return -(((unsigned int) this->address + step) - fn) - 5;
}
