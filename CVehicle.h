//
// Created by Serabass on 30.11.2018.
//

#ifndef CREATEREMOTETHREAD_CVEHICLE_H
#define CREATEREMOTETHREAD_CVEHICLE_H

#include "MemoryReader.h"
#include "macros.h"

class CVehicle : public MemoryReader {
public:
    explicit CVehicle(int location);
    void BlowUp();

    DEFAULT_PROP_H(BYTE, ModelIndex);
};

#endif //CREATEREMOTETHREAD_CVEHICLE_H
