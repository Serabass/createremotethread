//
// Created by Serabass on 30.11.2018.
//

#include "ASMBuilder.h"

ASMBuilder *ASMBuilder::factory() {
    return new ASMBuilder();
}

ASMBuilder::ASMBuilder() {

}

ASMBuilder *ASMBuilder::movECXValue(int value) {
    BYTE add[4] = {0x00, 0x00, 0x00, 0x00};
    memcpy(&add[0], &value, 4);
    bytes.push_back(0xB9);

    for (BYTE i : add) {
        bytes.push_back(i);
    }

    return this;
}

ASMBuilder *ASMBuilder::movEDIDwordPtrEcx() {
    bytes.push_back(0x8B);
    bytes.push_back(0x39);

    return this;
}

ASMBuilder *ASMBuilder::pushByte(BYTE value) {
    bytes.push_back(0x6A);
    bytes.push_back(value);
    return this;
}

ASMBuilder *ASMBuilder::relativeCall(int relativeAddr) {
    BYTE instr[4] = {0x00, 0x00, 0x00, 0x00};
    memcpy(&instr[0], &relativeAddr, 4);
    bytes.push_back(0xE8);
    for (BYTE i : instr) {
        bytes.push_back(i);
    }
    return this;
}

ASMBuilder *ASMBuilder::retn() {
    bytes.push_back(0xC3);
    return this;
}

BYTE *ASMBuilder::build() {
    return &bytes[0];
}