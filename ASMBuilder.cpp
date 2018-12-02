//
// Created by Serabass on 30.11.2018.
//

#include "ASMBuilder.h"

ASMBuilder *ASMBuilder::factory(AllocationInfo *mem) {
    return new ASMBuilder(mem);
}

ASMBuilder *ASMBuilder::factory(Injector *injector) {
    return new ASMBuilder(injector);
}

ASMBuilder *ASMBuilder::factory(Injector *injector, SIZE_T allocationSize) {
    return new ASMBuilder(injector, allocationSize);
}

ASMBuilder::ASMBuilder(AllocationInfo *mem) {
    this->mem = mem;
}

ASMBuilder::ASMBuilder(Injector *injector, SIZE_T allocationSize) {
    this->injector = injector;
    this->mem = injector->Alloc(allocationSize);
}

void ASMBuilder::push(BYTE b) {
    data.push_back(b);
}

ASMBuilder::ASMBuilder(Injector *injector) {
    this->injector = injector;
}

ASMBuilder *ASMBuilder::movDWORDToECX(int value) {
    BYTE add[4] = {0x00, 0x00, 0x00, 0x00};
    memcpy(&add[0], &value, 4);
    push(0xB9);

    for (BYTE i : add) {
        push(i);
    }

    return this;
}

ASMBuilder *ASMBuilder::movDWORDPtrToEAX(int value) {
    BYTE add[4] = {0x00, 0x00, 0x00, 0x00};
    memcpy(&add[0], &value, 4);
    push(0xA3);

    for (BYTE i : add) {
        push(i);
    }

    return this;
}

ASMBuilder *ASMBuilder::movEDIDwordPtrEcx() {
    push(0x8B);
    push(0x39);

    return this;
}

ASMBuilder *ASMBuilder::pushByte(BYTE value) {
    push(0x6A);
    push(value);
    return this;
}

ASMBuilder *ASMBuilder::relativeCall(int fnAddress) {
    int instruction = mem->calculateOffset((int) data.size() + 1, fnAddress);
    BYTE instr[4] = {0x00, 0x00, 0x00, 0x00};
    memcpy(&instr[0], &instruction, 4);
    push(0xE8);
    for (BYTE i : instr) {
        push(i);
    }
    return this;
}

ASMBuilder *ASMBuilder::retn() {
    push(0xC3);
    return this;
}

BYTE *ASMBuilder::build() {
    unsigned int size = data.size();
    auto ret = new BYTE[size];

    for (int i = 0; i < size; i++) {
        ret[i] = data[i];
    }

    return ret;
}