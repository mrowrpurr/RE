#pragma once

#include <Windows.h>
// ^ require Windows.h first

#include <psapi.h>  // For MODULEINFO

namespace RE::Helpers {

    DWORD FindByteSignatureAddress(
        const wchar_t* moduleName, unsigned int startOffset, const char* pattern, const char* mask
    ) {
        // Get all module related information
        MODULEINFO modInfo = {0};
        HMODULE    hModule = GetModuleHandleW(moduleName);
        GetModuleInformation(GetCurrentProcess(), hModule, &modInfo, sizeof(MODULEINFO));

        // Assign our base and module size
        // Having the values right is ESSENTIAL, this makes sure
        // that we don't scan unwanted memory and leading our game to crash
        DWORD base = (DWORD)modInfo.lpBaseOfDll + startOffset;
        DWORD size = (DWORD)modInfo.SizeOfImage;

        // Get length for our mask, this will allow us to loop through our array
        DWORD patternLength = (DWORD)strlen(mask);

        for (DWORD i = 0; i < size - patternLength; i++) {
            bool found = true;
            for (DWORD j = 0; j < patternLength; j++) {
                // if we have a ? in our mask then we have true by default,
                // or if the bytes match then we keep searching until finding it or not
                if (mask[j] == '?') continue;
                auto value = *(char*)(base + i + j);
                if (value != pattern[j]) {
                    found = false;
                    break;
                }
            }

            // found = true, our entire pattern was found
            // return the memory addy so we can write to it
            if (found) {
                return base + i;
            }
        }

        return NULL;
    }
}