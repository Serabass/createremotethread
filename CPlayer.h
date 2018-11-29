//
// Created by Serabass on 30.11.2018.
//

#ifndef CREATEREMOTETHREAD_CPLAYER_H
#define CREATEREMOTETHREAD_CPLAYER_H

#include "VC.h"
#include "MemoryReader.h"
#include "CPed.h"

class CPlayer : public CPed {
public:
    static CPlayer *Instance();

    static CPlayer *singleton;

    explicit CPlayer(int location);

    CPed** GetNearestPeds();
};


#endif //CREATEREMOTETHREAD_CPLAYER_H
