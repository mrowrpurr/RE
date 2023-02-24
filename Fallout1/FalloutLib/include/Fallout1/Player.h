#pragma once

#include <Fallout1/RE/InventoryItem.h>

#include <string>

#include "Fallout1/RE/Addresses.h"
#include "Fallout1/RE/GetAddress.h"
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
            return RE::GetModuleAddress<RE::Player*>(RE::Addresses::PlayerPtr, {0x0});
        }

    public:
        static Player& GetSingleton() {
            static Player singleton;
            return singleton;
        }

        // Gets the player's age
        int GetAge() { return *RE::GetModuleAddress<int*>(RE::Addresses::PlayerAge); }

        // Sets the player's age
        void SetAge(int age) { *RE::GetModuleAddress<int*>(RE::Addresses::PlayerAge) = age; }

        // Gets the player's name
        const char* GetName() { return RE::GetModuleAddress<const char*>(RE::Addresses::PlayerName); }

        // Sets the player's name
        void SetName(const char* name) {
            char* playerName = (char*)Fallout1::RE::GetModuleAddress(Fallout1::RE::Addresses::PlayerName);
            strcpy(playerName, (char*)name);
        }

        // Gets the number of items in the player's inventory
        unsigned int GetInventoryCount() { return GetREPlayer()->inventoryCount; }

        // Gets the player's inventory items
        // XXX don't return RE classes, wrap them instead (???) (maybe?)
        std::vector<RE::InventoryItem> GetInventoryItems() {
            auto count = GetInventoryCount();
            if (count == 0) return {};
            auto* itemsPtr = (RE::InventoryItem*)GetREPlayer()->inventoryPtr;
            return std::vector<RE::InventoryItem>(itemsPtr, itemsPtr + count);
        }
    };

    Player& GetPlayer() { return Player::GetSingleton(); }
}