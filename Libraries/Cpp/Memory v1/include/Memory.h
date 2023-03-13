#pragma once

#include <Logging.h>
#include <Windows.h>

#include "Memory/Bytes.h"
#include "Memory/MemoryAddress.h"
#include "Memory/MemoryReader.h"
#include "Memory/MemoryWriter.h"

namespace Memory {
    typedef MemoryAddress Address;

    // Move me somewhere...
    uintptr_t Allocate(uintptr_t length) {
        if (length == 0) throw std::runtime_error("Length cannot be 0");
        auto addressPtr =
            VirtualAlloc(nullptr, length, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
        if (addressPtr == nullptr) throw std::runtime_error("Failed to allocate memory");
        auto address = reinterpret_cast<uintptr_t>(addressPtr);
        Log("Allocated {} bytes at {:x}", length, address);
        return address;
    }

    // Move me somewhere...
    void Free(uintptr_t address) {
        if (!VirtualFree(reinterpret_cast<BYTE*>(address), 0, MEM_RELEASE))
            throw std::runtime_error("Failed to free memory");
        Log("Freed bytes at {:x}", address);
    }
    void Free(const Address& address) { Free(address.GetAddress()); }
}
