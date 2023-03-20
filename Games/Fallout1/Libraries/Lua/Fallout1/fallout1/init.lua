local x = {}

x.addresses = require("fallout1/addresses")

function x.fallout1_function_from_init()
    return "Hello from our fallout1 init.lua file!"
end

function x.butts()
    return "butts"
end

return x 
