local ffi = require("ffi")

function CallMeMaybe()
    local output = ""

    local moduleBase = 0x400000
    output = output .. "Module Base: " .. string.format("%X", moduleBase) .. "\n"
    
    local player_ptr = ffi.cast("uint32_t*", moduleBase + 0x105734)[0]
    output = output .. "Player Pointer: " .. string.format("%X", player_ptr) .. "\n"
    
    local player_id = ffi.cast("uint32_t*", player_ptr + 0x0)[0]
    output = output .. "Player ID: " .. string.format("%i", player_id) .. "\n"

    local player_tile_number = ffi.cast("uint32_t*", player_ptr + 0x4)[0]
    output = output .. "Player Tile Number: " .. string.format("%i", player_tile_number) .. "\n"

    return output
end
