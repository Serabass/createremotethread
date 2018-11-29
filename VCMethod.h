
#ifndef CREATEREMOTETHREAD_VCMETHOD_H
#define CREATEREMOTETHREAD_VCMETHOD_H

#include "VC.h"

template<typename A1, SIZE_T count>
class VCMethod {
protected:
    int location;
    VC *vc = VC::Instance();
    BYTE *payload;

    virtual VCMethod *Prepare(AllocationInfo *mem, A1 a) = 0;
public:
    explicit VCMethod(int location);
    virtual void Invoke(A1 a);
};

class SpawnVehicleMethod : public VCMethod<int, 12> {
protected:
    SpawnVehicleMethod *Prepare(AllocationInfo *mem, int modelIndex) override;
public:
    SpawnVehicleMethod();

};

#endif //CREATEREMOTETHREAD_VCMETHOD_H
