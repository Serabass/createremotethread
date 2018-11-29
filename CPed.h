//
// Created by Serabass on 30.11.2018.
//

#ifndef CREATEREMOTETHREAD_CPED_H
#define CREATEREMOTETHREAD_CPED_H

#include "MemoryReader.h"

class CPed : public MemoryReader {
public:
    explicit CPed(int location);

    float GetHealth();
};

#endif //CREATEREMOTETHREAD_CPED_H
