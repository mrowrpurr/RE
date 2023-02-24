#pragma once

#include <string>

#include "RE/Addresses.h"
#include "RE/GetAddress.h"
#include "RE/InventoryItem.h"
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
        // TODO this should be private
        // TODO XXX move the 0x0 bit to Addresses
        RE::Player* GetREPlayer() {
            return RE::GetAddress<RE::Player*>(RE::MODULE_BASE + RE::Addresses::PlayerPtr, {0x0});
        }

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

        // TODO - move to like an inventory object or some shit.
        unsigned int GetInventoryCount() { return GetREPlayer()->inventoryCount; }

        RE::InventoryItem GetInventoryItem(unsigned int index) {
            auto total = GetInventoryCount();
            if (index >= total) return {};
            uintptr_t  inventoryPtr = GetREPlayer()->inventoryPtr;
            uintptr_t  itemBase     = inventoryPtr + index * 0x8;
            uintptr_t* itemPtr      = reinterpret_cast<uintptr_t*>(itemBase);
            uint32_t*  quantity     = reinterpret_cast<uint32_t*>(itemBase + 0x4);
            return RE::InventoryItem{*itemPtr, *quantity};
        }
    };

    Player& GetPlayer() { return Player::GetSingleton(); }
}

// return RE::GetAddress<RE::InventoryItem*>(GetREPlayer()->inventoryPtr, {index * 8});
