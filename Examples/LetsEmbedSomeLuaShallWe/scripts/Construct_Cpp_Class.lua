-- Construct a Dog class which takes a name and call the Bark method
-- The global namespace has a class named Dog
-- The Dog class has a constructor which takes a name
-- The Dog class has a method named Bark

-- Create a new Dog object
local dog = Animals.Dog("Parker")

-- Call the Bark method
dog:Bark()

-- Get the name of the dog
local name = dog:GetName()

-- Print the name of the dog
print(name)
