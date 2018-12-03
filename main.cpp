#include <iostream>
#include "Injector.h"
#include "VC.h"
#include "VCMethod.h"
#include "CPlayer.h"
#include "ASMBuilder.h"
#include "Buffer.h"
#include "AllicationInfo.h"
#include <vector>

#define KEY_PRESSED(K) GetKeyState(K) < 0

int main() {
    VC::Instance()->Open();
    // auto v = VC::Instance()->GetPlayerPointer();
    while (true) {
        Sleep(500);
        if (KEY_PRESSED(VK_CONTROL)) {
            break;
        }

        if (KEY_PRESSED(VK_F9)) {
            auto v = VC::Instance()->SpawnVehicle(206);
            Sleep(2000);
            VC::Instance()->BlowUpVehicle(v);
        }

    }
    VC::Instance()->Close();
    return 0;
}

/*

    while (true) {
        Sleep(500);
        if (GetKeyState(VK_F9) < 0) {
            vc->GetPlayer();
            Sleep(1500);
        }

        if (GetKeyState(VK_NUMPAD1) < 0) { vc->SetWeather(1); }
        if (GetKeyState(VK_NUMPAD2) < 0) { vc->SetWeather(2); }
        if (GetKeyState(VK_NUMPAD3) < 0) { vc->SetWeather(3); }
        if (GetKeyState(VK_NUMPAD4) < 0) { vc->SetWeather(4); }
        if (GetKeyState(VK_NUMPAD5) < 0) { vc->SetWeather(5); }
        if (GetKeyState(VK_NUMPAD6) < 0) { vc->SetWeather(6); }

        if (GetKeyState(VK_CONTROL) < 0) {
            break;
        }
    }
*/
