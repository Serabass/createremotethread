
#include <memory.h>
#include "Buffer.h"

Buffer::Buffer() {

}

Buffer *Buffer::int32(int value) {
    uint8_t buf[4];
    memcpy(&buf[0], &value, 4);

    for (uint8_t i : buf) {
        buffer.push_back(i);
    }

    return this;
}

Buffer *Buffer::uInt8(uint8_t value) {
    buffer.push_back(value);

    return this;
}
