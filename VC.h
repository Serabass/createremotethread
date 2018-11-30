//
// Created by Serabass on 29.11.2018.
//


#ifndef CREATEREMOTETHREAD_VC_H
#define CREATEREMOTETHREAD_VC_H

#include "Injector.h"
#include "CVehicle.h"

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

    void SetWeather(int weatherId);

    void GetVehicle(int vehicleId);

    int GetPlayerPointer();

    void BlowUpVehicle(int addr);
};

#endif //CREATEREMOTETHREAD_VC_H
