//
// Created by Serabass on 30.11.2018.
//

#include "CPed.h"
#include "macros.h"

#define OFFSET_HEALTH 0x354
#define OFFSET_ARMOR 0x358

CPed::CPed(int location) : MemoryReader(location) {
}

DEFAULT_PROP(CPed, Float, float, Health, OFFSET_HEALTH);
DEFAULT_PROP(CPed, Float, float, Armor, OFFSET_ARMOR);
