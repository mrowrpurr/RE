local ffi = require("ffi")

function CallMeMaybe()
    local offset = 0x08B27168
    local player_id = ffi.cast("uint32_t*", offset)[0]
    return player_id
end
