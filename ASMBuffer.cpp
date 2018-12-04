
#include "ASMBuffer.h"

ASMBuffer::ASMBuffer(Injector *injector) : Buffer() {
    this->injector = injector;
}

ASMBuffer *ASMBuffer::push(int value) {
    uInt8(0x68);         // push value
    int32(value);

    return this;
}

ASMBuffer *ASMBuffer::push(uint8_t value) {
    uInt8(0x6A);         // push value
    uInt8(value);

    return this;
}

ASMBuffer *ASMBuffer::push(REGISTER aRegister) {
    switch (aRegister) {
        case REGISTER::EAX:
            return (ASMBuffer *) uInt8(0x50);         // push eax
        case REGISTER::EBX:
            return (ASMBuffer *) uInt8(0x53);         // push ebx
        case REGISTER::ESI:
            return (ASMBuffer *) uInt8(0x56);         // push esi
        default:
            throw "Unknown register";
    }
}

ASMBuffer *ASMBuffer::relativeCall(int address) {
    auto rc = new RelativeCall();
    rc->location = buffer.size() + 1;
    rc->fnAddress = address;
    relativeCalls.push_back(*rc);

    return (ASMBuffer *) uInt8(0xE8)->int32(0x00000000);
}

ASMBuffer *ASMBuffer::pop(REGISTER aRegister) {
    switch (aRegister) {
        case REGISTER::ECX:
            uInt8(0x59);
            break;
    }

    return this;
}

ASMBuffer *ASMBuffer::mov(REGISTER aRegister, int value) {
    switch (aRegister) {
        case REGISTER::EAX:
            uInt8(0xB8)->int32(value);
            break;
        case REGISTER::ECX:
            uInt8(0x8B)->int32(value);
            break;
    }

    return this;
}

ASMBuffer *ASMBuffer::ret() {
    return (ASMBuffer *) uInt8(0xC3);
}

void ASMBuffer::inject() {
    auto allocationInfo = injector->Alloc(buffer.size());

    for (RelativeCall rc : relativeCalls) {
        int fnInstr = allocationInfo->calculateOffset(rc.location - 1, rc.fnAddress);
        memcpy(&buffer[rc.location], &fnInstr, 4);
    }

    injector->InjectAsm(allocationInfo, &buffer[0]);
    injector->Free(allocationInfo);
}

