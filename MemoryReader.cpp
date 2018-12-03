#include "MemoryReader.h"
#include "VC.h"
#include "Injector.h"

MemoryReader::MemoryReader(int location) {
    this->location = location;
}

template<typename T>
T MemoryReader::Value(int offset) {
    auto health = new AllocationInfo();
    health->address = (LPVOID) (location + offset);
    health->size = 4;
    T value;
    SIZE_T b;
    VC::Instance()->injector->Read(health, &value, &b);
    return value;
}


int MemoryReader::Int(int offset) {
    auto health = new AllocationInfo();
    health->address = (LPVOID) (location + offset);
    health->size = 4;
    int value;
    SIZE_T b = VC::Instance()->injector->Read(health, &value);
    return value;
}

void MemoryReader::Int(int offset, int value) {
    auto health = new AllocationInfo();
    health->address = (LPVOID) (location + offset);
    health->size = 4;
    SIZE_T b = VC::Instance()->injector->Write(health, &value);
}

WORD MemoryReader::Word(int offset) {
    auto health = new AllocationInfo();
    health->address = (LPVOID) (location + offset);
    health->size = 2;
    WORD value;
    SIZE_T b = VC::Instance()->injector->Read(health, &value);
    return value;
}

void MemoryReader::Word(int offset, WORD value) {
    auto health = new AllocationInfo();
    health->address = (LPVOID) (location + offset);
    health->size = 2;
    SIZE_T b = VC::Instance()->injector->Write(health, &value);
}

BYTE MemoryReader::Byte(int offset) {
    auto health = new AllocationInfo();
    health->address = (LPVOID) (location + offset);
    health->size = 1;
    BYTE value;
    SIZE_T b = VC::Instance()->injector->Read(health, &value);
    return value;
}

void MemoryReader::Byte(int offset, BYTE value) {
    auto health = new AllocationInfo();
    health->address = (LPVOID) (location + offset);
    health->size = 1;
    SIZE_T b = VC::Instance()->injector->Write(health, &value);
}

float MemoryReader::Float(int offset) {
    auto health = new AllocationInfo();
    health->address = (LPVOID) (location + offset);
    health->size = 4;
    float value;
    SIZE_T b = VC::Instance()->injector->Read(health, &value);
    return value;
}

void MemoryReader::Float(int offset, float value) {
    auto health = new AllocationInfo();
    health->address = (LPVOID) (location + offset);
    health->size = 4;
    SIZE_T b = VC::Instance()->injector->Write(health, &value);
}