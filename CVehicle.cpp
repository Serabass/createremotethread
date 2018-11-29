//
// Created by Serabass on 30.11.2018.
//

#include "CVehicle.h"
#include "Injector.h"
#include "VC.h"
#include "ASMBuilder.h"

CVehicle::CVehicle(int location) : MemoryReader(location) {
}

int CVehicle::GetModelIndex() {
    return this->Int(0x5C);
}

void CVehicle::BlowUp() {
    auto injector = VC::Instance()->injector;
    const int count = 15;
    int getVehicleFn = 0x588A60;
    AllocationInfo *mem = injector->Alloc(count);
    BYTE instr[4] = {0x00, 0x00, 0x00, 0x00};
    BYTE add[4] = {0x00, 0x00, 0x00, 0x00};
    int instruction = mem->calculateOffset(10, getVehicleFn);
    memcpy(&instr[0], &instruction, 4);
    memcpy(&add[0], &location, 4);
    BYTE getVehicle[count] = {
            0xB9, add[0], add[1], add[2], add[3],                     // mov    ecx, addr
            0x8B, 0x39,                                               // mov    edi,DWORD PTR [ecx]
            0x6A, 0x00,                                               // push 0
            0xE8, instr[0], instr[1], instr[2], instr[3],             // call   FN
            0xC3,                                                     // ret
    };

    BYTE *getVehicle2 = ASMBuilder::factory()
            ->movECXValue(location)              // mov    ecx, addr
            ->movEDIDwordPtrEcx()                // mov    edi,DWORD PTR [ecx]
            ->pushByte(0)                        // push 0
            ->relativeCall(instruction)          // call   FN
            ->retn()                             // ret
            ->build();

    injector->InjectAsm(mem, getVehicle);
    injector->Free(mem);
}
