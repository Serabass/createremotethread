
#include "VC.h"
#include "MemoryReader.h"

VC::VC() {
    injector = Injector::FromExecName("gta-vc.exe");
}

#define COUNT 12

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

CVehicle* VC::SpawnVehicle(int modelIndex) {
    const int count = 18;
    int spawnVehicleFn = 0x4AE8F0;
    AllocationInfo *mem = injector->Alloc(count);
    AllocationInfo *ret = injector->Alloc(4);
    BYTE fn[4] = {0x00, 0x00, 0x00, 0x00};
    BYTE mi[4] = {0x00, 0x00, 0x00, 0x00};
    BYTE retAr[4] = {0x00, 0x00, 0x00, 0x00};
    int fnInstr = mem->calculateOffset(5, spawnVehicleFn);
    int baseAddr = (int) ret->AllocatedBaseAddress;
    memcpy(&fn[0], &fnInstr, 4);
    memcpy(&mi[0], &modelIndex, 4);
    memcpy(&retAr[0], &baseAddr, 4);
    BYTE spawnVehicle[count] = {
            0x68, mi[0], mi[1], mi[2], mi[3],                           // push modelIndex
            0xE8, fn[0], fn[1], fn[2], fn[3],                           // call FN
            0x89, 0x0D, retAr[0], retAr[1], retAr[2], retAr[3],         // mov    DWORD PTR ds:retArray,ecx
            0x59,                                                       // pop ecx
            0xC3                                                        // ret
    };
    injector->InjectAsm(mem, spawnVehicle);
    injector->Free(mem);

    int address;
    SIZE_T b;

    injector->Read(ret, &address, &b);
    injector->Free(ret);

    return new CVehicle(address);
}

void VC::SetWeather(int weatherId) {
    const int count = 12;
    int setWeatherFn = 0x57D550;
    AllocationInfo *mem = injector->Alloc(count);
    BYTE instr[4] = {0x00, 0x00, 0x00, 0x00};
    BYTE weather[4] = {0x00, 0x00, 0x00, 0x00};
    int instruction = mem->calculateOffset(5, setWeatherFn);
    memcpy(&instr[0], &instruction, 4);
    memcpy(&weather[0], &weatherId, 4);
    BYTE setWeather[count] = {
            0x68, weather[0], weather[1], weather[2], weather[3],   // push weatherId
            0xE8, instr[0], instr[1], instr[2], instr[3],           // call FN
            0x59,                                                   // pop ecx
            0xC3                                                    // ret
    };
    injector->InjectAsm(mem, setWeather);
    injector->Free(mem);
}

void VC::GetVehicle(int vehicleId) {
    const int count = 25;
    int vehiclePool = 0xA0FDE4;
    int getVehicleFn = 0x451C70;
    AllocationInfo *mem = injector->Alloc(count);
    AllocationInfo *ret = injector->Alloc(4);
    BYTE instr[4] = {0x00, 0x00, 0x00, 0x00};
    BYTE vehicle[4] = {0x00, 0x00, 0x00, 0x00};
    BYTE retAr[4] = {0x00, 0x00, 0x00, 0x00};
    int instruction = mem->calculateOffset(12, getVehicleFn);
    memcpy(&instr[0], &instruction, 4);
    memcpy(&vehicle[0], &vehicleId, 4);
    int baseAddr = (int) ret->AllocatedBaseAddress;
    memcpy(&retAr[0], &baseAddr, 4);
    BYTE getVehicle[count] = {
            0xB8, vehicle[0], vehicle[1], vehicle[2], vehicle[3],     // mov    eax, vehicleId
            0x8B, 0x0D, 0xE4, 0xFD, 0xA0, 0x00,                       // mov    ecx, vehiclePool
            0x50,                                                     // push   eax
            0xE8, instr[0], instr[1], instr[2], instr[3],             // call   FN
            0x59,                                                     // pop ecx
            0x89, 0x0D, retAr[0], retAr[1], retAr[2], retAr[3],       // mov    DWORD PTR ds:retArray,ecx
            0xC3,                                                     // ret
    };
    injector->InjectAsm(mem, getVehicle);

    int result;
    SIZE_T b;

    injector->Read(ret, &result, &b);
    injector->Free(mem);
    injector->Free(ret);
}

int VC::GetPlayerPointer() {
    const int count = 25;
    int getPlayerFn = 0x4BC120;
    AllocationInfo *mem = injector->Alloc(count);
    AllocationInfo *ret = injector->Alloc(4);
    BYTE instr[4] = {0x00, 0x00, 0x00, 0x00};
    BYTE retAr[4] = {0x00, 0x00, 0x00, 0x00};
    int instruction = mem->calculateOffset(0, getPlayerFn);
    memcpy(&instr[0], &instruction, 4);
    int baseAddr = (int) ret->AllocatedBaseAddress;
    memcpy(&retAr[0], &baseAddr, 4);
    BYTE getVehicle[count] = {
            0xE8, instr[0], instr[1], instr[2], instr[3],             // call   FN
            0xA3, retAr[0], retAr[1], retAr[2], retAr[3],             // mov    DWORD PTR ds:retArray,eax
            0xC3,                                                     // ret
    };
    injector->InjectAsm(mem, getVehicle);

    int result;
    SIZE_T b;

    injector->Read(ret, &result, &b);
    injector->Free(mem);
    injector->Free(ret);
    return result;
}

void VC::BlowUpVehicle(int addr) {
    const int count = 15;
    int getVehicleFn = 0x588A60;
    AllocationInfo *mem = injector->Alloc(count);
    BYTE instr[4] = {0x00, 0x00, 0x00, 0x00};
    BYTE add[4] = {0x00, 0x00, 0x00, 0x00};
    int instruction = mem->calculateOffset(10, getVehicleFn);
    memcpy(&instr[0], &instruction, 4);
    memcpy(&add[0], &addr, 4);
    BYTE getVehicle[count] = {
            0xB9, add[0], add[1], add[2], add[3],                     // mov    ecx, addr
            0x8B, 0x39,                                               // mov    edi,DWORD PTR [ecx]
            0x6A, 0x00,                                               // push 0
            0xE8, instr[0], instr[1], instr[2], instr[3],             // call   FN
            0xC3,                                                     // ret
    };
    injector->InjectAsm(mem, getVehicle);
    injector->Free(mem);
}

int VC::Money() {
    auto *mem = new AllocationInfo();
    mem->AllocatedBaseAddress = (LPVOID)0x0094ADC8;
    mem->AllocatedSize = 4;
    int result;
    injector->Read(mem, &result, nullptr);
    return result;
}

void VC::Money(int value) {
    auto *mem = new AllocationInfo();
    mem->AllocatedBaseAddress = (LPVOID)0x0094ADC8;
    mem->AllocatedSize = 4;
    injector->Write(mem, &value, nullptr);
}

void VC::AddMoney(int value) {
    int current = Money();
    current += value;
    Money(current);
}

void VC::Close() {
    injector->Close();
}

void VC::Sandbox() {
    auto *mem = new AllocationInfo();
    mem->AllocatedBaseAddress = (LPVOID)0xA0FDE4;
    mem->AllocatedSize = 4;

    int i;

    do {
        injector->Read(mem, &i, nullptr);

        if (i != 0 && i != -1) {
            int l;
            mem->AllocatedBaseAddress = (LPVOID)i;
            injector->Read(mem, &l, nullptr);
            auto v = new CVehicle(l);
            v->BlowUp();
            Sleep(1500);
        }
    } while (i != 0 && i != -1);
}