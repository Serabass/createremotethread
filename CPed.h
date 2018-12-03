//
// Created by Serabass on 30.11.2018.
//

#ifndef CREATEREMOTETHREAD_CPED_H
#define CREATEREMOTETHREAD_CPED_H

#include "MemoryReader.h"
#include "macros.h"

class CPed : public MemoryReader {
public:
    explicit CPed(int location);

    DEFAULT_PROP_H(float, Health)
    DEFAULT_PROP_H(float, Armor)

    DEFAULT_PROP_H(int, LastControlledVehicle)
};

#endif //CREATEREMOTETHREAD_CPED_H
