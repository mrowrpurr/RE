#pragma once

#include <Logging.h>
#include <Windows.h>

// ^ require Windows.h first

#include <Psapi.h>  // For MODULEINFO

#include <exception>

namespace Hooks::ArrayOfBytes {

    // TODO DWORD --> uint32_t

    std::string DEFAULT_MODULE_NAME;
    uint32_t    DEFAULT_START_OFFSET = 0;

    DWORD Find(
        const std::string& pattern, std::string mask, uint32_t startOffset = 0,
        std::string moduleName = ""
    ) {
        if (moduleName.empty()) moduleName = DEFAULT_MODULE_NAME;
        if (moduleName.empty()) throw std::exception("No module name provided");
        if (startOffset == 0) startOffset = DEFAULT_START_OFFSET;
        if (mask.empty()) mask = std::string(pattern.size(), 'x');

        Log("FindByteSignatureAddress: moduleName = {}, startOffset = {}, pattern = {}, mask = {}",
            moduleName, startOffset, pattern, mask);

        // Get all module related information
        MODULEINFO modInfo = {0};
        HMODULE    hModule = GetModuleHandle(moduleName.c_str());
        GetModuleInformation(GetCurrentProcess(), hModule, &modInfo, sizeof(MODULEINFO));

        // Assign our base and module size
        // Having the values right is ESSENTIAL, this makes sure
        // that we don't scan unwanted memory and leading our game to crash
        DWORD base = (DWORD)modInfo.lpBaseOfDll + startOffset;
        DWORD size = (DWORD)modInfo.SizeOfImage;

        // Get length for our mask, this will allow us to loop through our array
        size_t patternLength = mask.size();  // What about when mask is not provided?

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
                Log("Found pattern at address: 0x{:X}", base + i);
                return base + i;
            }
        }

        return NULL;
    }
}
