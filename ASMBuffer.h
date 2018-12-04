
#ifndef CREATEREMOTETHREAD_ASMBUFFER_H
#define CREATEREMOTETHREAD_ASMBUFFER_H

#include <vector>
#include "Buffer.h"

enum REGISTER {
    EAX,
    ECX,
    EBX,
    ESI,
};

class ASMBuffer : public Buffer {
    std::vector<RelativeCall> relativeCalls;
    Injector *injector;
public:
    explicit ASMBuffer(Injector* injector);
    ASMBuffer* push(int value);
    ASMBuffer* push(uint8_t value);
    ASMBuffer* push(REGISTER aRegister);
    ASMBuffer* relativeCall(int address);
    ASMBuffer* pop(REGISTER aRegister);
    ASMBuffer* mov(REGISTER aRegister, int value);
    ASMBuffer* ret();
    void inject();
};


#endif //CREATEREMOTETHREAD_ASMBUFFER_H
