-- require "our_lib.lua"

function onBark(dogName)
    print("onEvent ---> Dog with name"..dogName.."barked")
end

function onButts(something)
    print("onEvent ---> Butts")
end

function plugin()
    -- onEvent("Bark", onBark)
    -- onEvent("Butts", onButts)

    onEvent("Bark", "onBark")
    onEvent("Butts", "onButts")
end