
#ifndef CREATEREMOTETHREAD_ASMBUILDER_H
#define CREATEREMOTETHREAD_ASMBUILDER_H

#include <windows.h>
#include <vector>
#include "AllicationInfo.h"
#include "Injector.h"

class ASMBuilder {

    void push(BYTE b);
public:
    AllocationInfo* mem;
    Injector* injector;
    static ASMBuilder* factory(AllocationInfo* mem);
    static ASMBuilder* factory(Injector * injector);
    static ASMBuilder* factory(Injector * injector, SIZE_T allocationSize);

    std::vector<BYTE> data;

    ASMBuilder(AllocationInfo* mem);
    ASMBuilder(Injector * injector);
    ASMBuilder(Injector * injector, SIZE_T allocationSize);
    ASMBuilder* movDWORDToECX(int value);
    ASMBuilder* movDWORDPtrToEAX(int value);
    ASMBuilder* movEDIDwordPtrEcx();
    ASMBuilder* pushByte(BYTE value);
    ASMBuilder* relativeCall(int fnAddress);
    ASMBuilder* retn();
    BYTE* build();
};

#endif //CREATEREMOTETHREAD_ASMBUILDER_H
