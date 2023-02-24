#pragma once

#include <Fallout1/RE/InventoryItem.h>

#include <string>

#include "Fallout1/RE/Addresses.h"
#include "Fallout1/RE/GetAddress.h"
#include "Fallout1/RE/ModuleBase.h"
#include "Fallout1/RE/Player.h"

namespace Fallout1 {

    class Player {
        Player()                         = default;
        ~Player()                        = default;
        Player(const Player&)            = delete;
        Player(Player&&)                 = delete;
        Player& operator=(const Player&) = delete;
        Player& operator=(Player&&)      = delete;

        RE::Player* GetREPlayer() {
            // TODO XXX move the 0x0 bit to Addresses
            return RE::GetAddress<RE::Player*>(RE::MODULE_BASE + RE::Addresses::PlayerPtr, {0x0});
        }

    public:
        static Player& GetSingleton() {
            static Player singleton;
            return singleton;
        }

        int  GetAge() { return *RE::GetAddress<int*>(RE::MODULE_BASE + RE::Addresses::PlayerAge); }
        void SetAge(int age) { *RE::GetAddress<int*>(RE::MODULE_BASE + RE::Addresses::PlayerAge) = age; }

        const char* GetName() { return RE::GetAddress<const char*>(RE::MODULE_BASE + RE::Addresses::PlayerName); }
        void        SetName(const char* name) {
            char* playerName = (char*)Fallout1::RE::GetAddress(RE::MODULE_BASE + Fallout1::RE::Addresses::PlayerName);
            strcpy(playerName, (char*)name);
        }

        unsigned int GetInventoryCount() { return GetREPlayer()->inventoryCount; }

        std::vector<RE::InventoryItem> GetInventoryItems() {
            auto count = GetInventoryCount();
            if (count == 0) return {};
            auto* itemsPtr = (RE::InventoryItem*)GetREPlayer()->inventoryPtr;
            return std::vector<RE::InventoryItem>(itemsPtr, itemsPtr + count);
        }
    };

    Player& GetPlayer() { return Player::GetSingleton(); }
}