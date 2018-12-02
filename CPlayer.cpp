//
// Created by Serabass on 30.11.2018.
//

#include "CPlayer.h"
#include "VC.h"
#include <vector>

CPlayer *CPlayer::singleton = nullptr;

CPlayer *CPlayer::Instance() {
    if (!singleton) {
        int pointer = VC::Instance()->GetPlayerPointer();
        singleton = new CPlayer(pointer);
    }
    return singleton;
}

CPlayer::CPlayer(int location) : CPed(location + 0x0) {
}

CPed** CPlayer::GetNearestPeds() {
    std::vector<CPed*> result;

    for (int i = 0; i < 10; i++) {
        int pointer = this->Int(0x56C + (4 * i));
        result.push_back(new CPed(pointer));
    }

    return &result[0];
}
