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
protected:
    std::vector<uint8_t> buffer;

public:
    Buffer();

    Buffer* uInt8(uint8_t value);

    Buffer* int32(int value);

    Buffer* allocInfo(AllocationInfo* allocationInfo);
};

#endif //CREATEREMOTETHREAD_BUFFER_H
