
#ifndef CREATEREMOTETHREAD_ASMBUILDER_H
#define CREATEREMOTETHREAD_ASMBUILDER_H

#include <windows.h>
#include <vector>

class ASMBuilder {
public:
    static ASMBuilder* factory();

    std::vector<BYTE> bytes;

    ASMBuilder();

    ASMBuilder* movECXValue(int value);
    ASMBuilder* movEDIDwordPtrEcx();
    ASMBuilder* pushByte(BYTE value);
    ASMBuilder* relativeCall(int relativeAddr);
    ASMBuilder* retn();
    BYTE* build();
};

#endif //CREATEREMOTETHREAD_ASMBUILDER_H
