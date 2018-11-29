
#include "VCMethod.h"

template<typename T, SIZE_T count>
VCMethod<T, count>::VCMethod(int location)  {
    this->location = location;
}

template<typename T, SIZE_T count>
void VCMethod<T, count>::Invoke(T a) {
    AllocationInfo *mem = vc->injector->Alloc(count);
    Prepare(mem, a);
    vc->injector->InjectAsm(mem, payload);
    vc->injector->Free(mem);
}

SpawnVehicleMethod::SpawnVehicleMethod()
        : VCMethod(0x4AE8F0) {}

SpawnVehicleMethod *SpawnVehicleMethod::Prepare(AllocationInfo *mem, int modelIndex) {
    BYTE fn[4] = {0x00, 0x00, 0x00, 0x00};
    BYTE mi[4] = {0x00, 0x00, 0x00, 0x00};
    int fnInstr = mem->calculateOffset(5, this->location);
    memcpy(&fn[0], &fnInstr, 4);
    memcpy(&mi[0], &modelIndex, 4);
    BYTE spawnVehicle[] = {
            0x68, mi[0], mi[1], mi[2], mi[3],              // push modelIndex
            0xE8, fn[0], fn[1], fn[2], fn[3],              // call FN
            0x59,                                          // pop ecx
            0xC3                                           // ret
    };
    payload = spawnVehicle;
    return this;
}
