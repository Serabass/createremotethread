
#include <memory.h>
#include "Buffer.h"

Buffer::Buffer() {

}

Buffer *Buffer::int32(int value) {
    uint8_t buf[4];
    memcpy(&buf[0], &value, 4);

    for (uint8_t i : buf) {
        uInt8(i);
    }

    return this;
}

Buffer *Buffer::uInt8(uint8_t value) {
    buffer.push_back(value);

    return this;
}

Buffer *Buffer::allocInfo(AllocationInfo * allocationInfo)
{
    return int32((int) allocationInfo->address);
}
