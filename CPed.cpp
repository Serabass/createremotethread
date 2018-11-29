//
// Created by Serabass on 30.11.2018.
//

#include "CPed.h"

CPed::CPed(int location) : MemoryReader(location) {
}

float CPed::GetHealth() {
    return this->GetFloatValue(0x354);
}
