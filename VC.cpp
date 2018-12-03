#include <cstdio>
#include <sstream>
#include <iomanip>
#include <string>
#include "VC.h"
#include "MemoryReader.h"
#include "ASMBuilder.h"

VC::VC() {
    injector = Injector::FromExecName("gta-vc.exe");
}

VC *VC::singleton = nullptr;

VC *VC::Instance() {
    if (!VC::singleton) {
        VC::singleton = new VC();
    }
    return singleton;
}

void VC::Open() {
    injector->Open(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION |
                   PROCESS_VM_READ | PROCESS_VM_WRITE |
                   PROCESS_VM_OPERATION);
}

ASMBuffer *VC::createBuffer() {
    return new ASMBuffer(injector);
}

CVehicle *VC::SpawnVehicle(int modelIndex) {
    int spawnVehicleFn = 0x4AE8F0;
    AllocationInfo *resultAlloc = injector->Alloc(4);
    auto result = (int) resultAlloc->address;

    auto buffer = createBuffer();
    buffer->push(modelIndex);                         // push modelIndex
    buffer->relativeCall(spawnVehicleFn);             // call spawnVehicleFn
    buffer->uInt8(0x89)->uInt8(0x0D)->int32(result);  // mov DWORD PTR ds:result
    buffer->pop(REGISTER::ECX);                       // pop ecx
    buffer->ret();                                    // ret
    buffer->inject();

    int address;

    injector->Read(resultAlloc, &address);
    injector->Free(resultAlloc);

    return new CVehicle(address);
}

std::string hexStr(BYTE *data, int len) {
    std::stringstream ss;
    ss << std::hex;
    for (int i(0); i < len; ++i) {
        ss << (int) data[i];
        ss << " ";
    }
    return ss.str();
}

void VC::SetWeather(int weatherId) {
    int setWeatherFn = 0x57D550;
    auto buffer = createBuffer();
    buffer->push(weatherId);             // push weatherId
    buffer->relativeCall(setWeatherFn);  // call setWeatherFn
    buffer->uInt8(0x59);                 // pop ecx
    buffer->uInt8(0xC3);                 // ret
    buffer->inject();
}

void VC::GetText(int a1, char a2) {
    AllocationInfo *ret = injector->Alloc(4);

    int GetTextFN = 0x584F30;
    auto buffer = createBuffer();
    buffer->push((uint8_t) 0x00);          // push    0
    buffer->push((uint8_t) 0x01);          // push    1
    buffer->push(0x68F1E8);
    buffer->relativeCall(GetTextFN);
    buffer->uInt8(0xB8)->int32((int) ret->address);
    buffer->uInt8(0xC3);
    buffer->inject();
}

void VC::GetVehicle(int vehicleId) {
    int vehiclePool = 0xA0FDE4;
    int getVehicleFn = 0x451C70;
    AllocationInfo *ret = injector->Alloc(4);

    auto buffer = createBuffer();
    buffer->mov(REGISTER::EAX, vehicleId);                                     // mov    eax, vehicleId
    buffer->mov(REGISTER::ECX, vehiclePool);                                   // mov    ecx, vehiclePool
    buffer->push(REGISTER::EAX);                                               // push   eax
    buffer->relativeCall(getVehicleFn);                                        // call   FN
    buffer->pop(REGISTER::ECX);                                                // pop    ecx
    buffer->uInt8(0x89)->uInt8(0x0D)->int32((int) ret->address);               // mov    DWORD PTR ds:retAddr,ecx
    buffer->ret();                                                             // ret
    buffer->inject();

    int result;
    SIZE_T b = injector->Read(ret, &result);
    injector->Free(ret);
}

int VC::GetPlayerPointer() {
    int getPlayerFn = 0x4BC120;
    AllocationInfo *ret = injector->Alloc(4);

    auto buffer = createBuffer();
    buffer->relativeCall(getPlayerFn);
    buffer->uInt8(0xA3)->int32((int) ret->address);
    buffer->ret();
    buffer->inject();

    int result;
    SIZE_T b = injector->Read(ret, &result);
    injector->Free(ret);
    return result;
}

void VC::BlowUpVehicle(int addr) {
    int blowUpVehicle = 0x588A60;

    auto buffer = createBuffer();
    buffer->uInt8(0xB9)->int32(addr);                   // mov    ecx, addr
    buffer->uInt8(0x8B)->uInt8(0x39);                   // mov    edi,DWORD PTR [ecx]
    buffer->push((uint8_t)0x00);                        // push 0
    buffer->relativeCall(blowUpVehicle);                 // call   FN
    buffer->ret();                                      // ret
    buffer->inject();
}

void VC::BlowUpVehicle(CVehicle* v) {
    BlowUpVehicle(v->location);
}

int VC::Money() {
    auto *mem = new AllocationInfo();
    mem->address = (LPVOID) 0x0094ADC8;
    mem->size = 4;
    int result;
    injector->Read(mem, &result);
    return result;
}

void VC::Money(int value) {
    auto *mem = new AllocationInfo();
    mem->address = (LPVOID) 0x0094ADC8;
    mem->size = 4;
    injector->Write(mem, &value);
}

void VC::AddMoney(int value) {
    int current = Money();
    current += value;
    Money(current);
}

void VC::Close() {
    injector->Close();
}
