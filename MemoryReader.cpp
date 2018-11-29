#include "MemoryReader.h"
#include "VC.h"
#include "Injector.h"

MemoryReader::MemoryReader(int location) {
    this->location = location;
}

template<typename T>
T MemoryReader::GetValue(int offset) {
    auto health = new AllocationInfo();
    health->AllocatedBaseAddress = (LPVOID) (location + offset);
    health->AllocatedSize = 4;
    T value;
    SIZE_T b;
    VC::Instance()->injector->Read(health, &value, &b);
    return value;
}


int MemoryReader::GetIntValue(int offset) {
    auto health = new AllocationInfo();
    health->AllocatedBaseAddress = (LPVOID) (location + offset);
    health->AllocatedSize = 4;
    int value;
    SIZE_T b;
    VC::Instance()->injector->Read(health, &value, &b);
    return value;
}

void MemoryReader::SetIntValue(int offset, int value) {
    auto health = new AllocationInfo();
    health->AllocatedBaseAddress = (LPVOID) (location + offset);
    health->AllocatedSize = 4;
    SIZE_T b;
    VC::Instance()->injector->Write(health, &value, &b);
}

float MemoryReader::GetFloatValue(int offset) {
    auto health = new AllocationInfo();
    health->AllocatedBaseAddress = (LPVOID) (location + offset);
    health->AllocatedSize = 4;
    float value;
    SIZE_T b;
    VC::Instance()->injector->Read(health, &value, &b);
    return value;
}

void MemoryReader::SetFloatValue(int offset, float value) {
    auto health = new AllocationInfo();
    health->AllocatedBaseAddress = (LPVOID) (location + offset);
    health->AllocatedSize = 4;
    SIZE_T b;
    VC::Instance()->injector->Write(health, &value, &b);
}