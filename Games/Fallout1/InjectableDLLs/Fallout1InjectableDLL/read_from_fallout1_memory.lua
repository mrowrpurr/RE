local fallout1 = require("fallout1")

local ffi = require("ffi")

ffi.cdef[[
    typedef struct { uint32_t objID, tileNum; } NPC;

    typedef struct {
        uint32_t    intA;
        uint32_t    intB;
        const char* text;
    } SomeRandomStruct;
]]

function CallMeMaybe()
    local output = ""

    output = output .. "Hello friends!\n"

    output = output .. fallout1.butts() .. "\n"

    output = output .. fallout1.fallout1_function_from_init() .. "\n"

    local moduleBase = 0x400000
    output = output .. "Module Base: " .. string.format("%X", moduleBase) .. "\n"
    
    local player_ptr = ffi.cast("uint32_t*", moduleBase + 0x105734)[0]
    output = output .. "Player Pointer: " .. string.format("%X", player_ptr) .. "\n"
    
    local player_id = ffi.cast("uint32_t*", player_ptr + 0x0)[0]
    output = output .. "Player ID: " .. string.format("%i", player_id) .. "\n"

    local player_tile_number = ffi.cast("uint32_t*", player_ptr + 0x4)[0]
    output = output .. "Player Tile Number: " .. string.format("%i", player_tile_number) .. "\n"

    local player_struct = ffi.cast("NPC*", player_ptr)
    output = output .. "Player Struct objID (should be same as player ID): " .. string.format("%i", player_struct.objID) .. "\n"
    output = output .. "Player Struct tileNum (should be same as player tile number): " .. string.format("%i", player_struct.tileNum) .. "\n"

    output = output .. "The address: " .. string.format("%X", theAddress) .. "\n"

    local some_random_struct = ffi.cast("SomeRandomStruct*", theAddress)
    output = output .. "SomeRandomStruct intA: " .. string.format("%i", some_random_struct.intA) .. "\n"
    output = output .. "SomeRandomStruct intB: " .. string.format("%i", some_random_struct.intB) .. "\n"
    output = output .. "SomeRandomStruct text: " .. string.format("%s", ffi.string(some_random_struct.text)) .. "\n"

    return output
end
