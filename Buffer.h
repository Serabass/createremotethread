//
// Created by Serabass on 02.12.2018.
//

#ifndef CREATEREMOTETHREAD_BUFFER_H
#define CREATEREMOTETHREAD_BUFFER_H

#include <vector>
#include <cstdint>
#include "Injector.h"

struct RelativeCall {
    int location;
    int fnAddress;
};

class Buffer {
    std::vector<uint8_t> buffer;

    Injector *injector;

    std::vector<RelativeCall> relativeCalls;
public:
    Buffer(Injector* injector);

    Buffer* uInt8(uint8_t value);

    Buffer* int32(int value);

    Buffer* pushInt32(int value);

    Buffer* relativeCall(int address);

    void inject();
};

#endif //CREATEREMOTETHREAD_BUFFER_H
