#include <Logging.h>
#include <ModdingFramework/Lua.h>
#include <ModdingFramework/Mod.h>

SetModName("ModdingFramework.Lua");

OnLoad { Log("Hello from ModdingFramework.Lua.dll!"); }

OnUnload {}
