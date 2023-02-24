#pragma once

#include <string>

#include "RE/GetAddress.h"
#include "RE/Player.h"

namespace Fallout1 {

    class Player {
        Player()                         = default;
        ~Player()                        = default;
        Player(const Player&)            = delete;
        Player(Player&&)                 = delete;
        Player& operator=(const Player&) = delete;
        Player& operator=(Player&&)      = delete;

    public:
        static Player& GetSingleton() {
            static Player singleton;
            return singleton;
        }

        int  GetAge() { return *RE::GetAddress<int>(RE::Addresses::PlayerAge); }
        void SetAge(int age) { *RE::GetAddress<int>(RE::Addresses::PlayerAge) = age; }
    };

    Player& GetPlayer() { return Player::GetSingleton(); }
}
