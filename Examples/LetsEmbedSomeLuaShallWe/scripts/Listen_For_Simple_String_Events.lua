-- require "our_lib.lua"

function onBark(dogName)
    print("onEvent Fn ---> Dog with name "..dogName.." barked")
end

function onButts(something)
    print("onEvent Fn ---> Butts")
end

function plugin()
    onEvent("Bark", onBark)
    onEvent("Butts", onButts)
end