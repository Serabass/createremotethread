#include <iostream>
#include "Injector.h"
#include "VC.h"
#include "VCMethod.h"
#include "CPlayer.h"

int main() {
    VC::Instance()->Open();

    while (true) {
        Sleep(500);
        if (GetKeyState(VK_F9) < 0) {
            auto v = VC::Instance()->SpawnVehicle(200);
            Sleep(2000);

            v->BlowUp();
        }

        if (GetKeyState(VK_CONTROL) < 0) {
            break;
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
