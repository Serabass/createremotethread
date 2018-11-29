#include "MemoryReader.h"
#include "VC.h"
#include "Injector.h"

MemoryReader::MemoryReader(int location) {
    this->location = location;
}

template<typename T>
T MemoryReader::Value(int offset) {
    auto health = new AllocationInfo();
    health->AllocatedBaseAddress = (LPVOID) (location + offset);
    health->AllocatedSize = 4;
    T value;
    SIZE_T b;
    VC::Instance()->injector->Read(health, &value, &b);
    return value;
}


int MemoryReader::Int(int offset) {
    auto health = new AllocationInfo();
    health->AllocatedBaseAddress = (LPVOID) (location + offset);
    health->AllocatedSize = 4;
    int value;
    SIZE_T b;
    VC::Instance()->injector->Read(health, &value, &b);
    return value;
}

void MemoryReader::Int(int offset, int value) {
    auto health = new AllocationInfo();
    health->AllocatedBaseAddress = (LPVOID) (location + offset);
    health->AllocatedSize = 4;
    SIZE_T b;
    VC::Instance()->injector->Write(health, &value, &b);
}

float MemoryReader::Float(int offset) {
    auto health = new AllocationInfo();
    health->AllocatedBaseAddress = (LPVOID) (location + offset);
    health->AllocatedSize = 4;
    float value;
    SIZE_T b;
    VC::Instance()->injector->Read(health, &value, &b);
    return value;
}

void MemoryReader::Float(int offset, float value) {
    auto health = new AllocationInfo();
    health->AllocatedBaseAddress = (LPVOID) (location + offset);
    health->AllocatedSize = 4;
    SIZE_T b;
    VC::Instance()->injector->Write(health, &value, &b);
}