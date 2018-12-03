//
// Created by Serabass on 29.11.2018.
//


#ifndef CREATEREMOTETHREAD_VC_H
#define CREATEREMOTETHREAD_VC_H

#include "Injector.h"
#include "CVehicle.h"
#include "ASMBuffer.h"
#include "Injector.h"

class VC {
private:
public:
    Injector *injector;

    static VC *singleton;
    static VC *Instance();

    VC();

    void Open();

    void Close();

    CVehicle* SpawnVehicle(int modelIndex);

    ASMBuffer* createBuffer();

    void SetWeather(int weatherId);
    void GetText(int a1, char a2);

    void GetVehicle(int vehicleId);

    int GetPlayerPointer();

    void BlowUpVehicle(int addr);
    void BlowUpVehicle(CVehicle *vehicle);
    void AddMoney(int value);
    void Money(int value);
    int Money();

    void Sandbox();
};

#endif //CREATEREMOTETHREAD_VC_H
