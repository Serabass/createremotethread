//
// Created by Serabass on 30.11.2018.
//

#ifndef CREATEREMOTETHREAD_CVEHICLE_H
#define CREATEREMOTETHREAD_CVEHICLE_H

#include "MemoryReader.h"

class CVehicle : public MemoryReader {
public:
    explicit CVehicle(int location);
    int GetModelIndex();
    void BlowUp();
};

#endif //CREATEREMOTETHREAD_CVEHICLE_H
