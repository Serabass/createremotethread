
#include <memory.h>
#include "Buffer.h"

Buffer::Buffer(Injector *injector) {
    this->injector = injector;
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

Buffer *Buffer::pushInt32(int value) {
    uInt8(0x68);         // push modelIndex
    int32(value);

    return this;
}

Buffer *Buffer::relativeCall(int address) {
    auto rc = new RelativeCall();
    rc->location = buffer.size() + 1;
    rc->fnAddress = address;
    relativeCalls.push_back(*rc);

    uInt8(0xE8)
            ->uInt8(0x00)
            ->uInt8(0x00)
            ->uInt8(0x00)
            ->uInt8(0x00);

    return this;
}

void Buffer::inject() {
    auto allocationInfo = injector->Alloc(buffer.size());

    for (RelativeCall rc : relativeCalls) {
        int fnInstr = allocationInfo->calculateOffset(rc.location - 1, rc.fnAddress);
        memcpy(&buffer[rc.location], &fnInstr, 4);
    }

    injector->InjectAsm(allocationInfo, &buffer[0]);
    injector->Free(allocationInfo);
}
