![Reverse Engineering](Images/Logo.png)

# Mrowr Purr's Reverse Engineering Journey

As I learn to reverse engineer video games, I am putting the source code for everything that I learn here.

### Learning Goals

I one day hope to have a variety of examples demonstrating:

- Some examples of simple x86 and x64 assembly programs
- Program memory read/write via external executables
- Program memory read/write via internally injected libraries
  - Libraries / Tools for .dll injection (using different patterns)
- Detours / Trampolines
- Cheat Engine cheat tables for various games
- Minimal modding frameworks for various games in various languages
  - C++
  - Rust
- Embedded virtual machines with library with bindings to host process memory alteration (with REPL)
  - Lua
  - JavaScript
  - Python
- And more!

I'm just getting started learning, so we'll see!

# LICENSE

```
BSD Zero Clause License (SPDX: 0BSD)

Permission to use, copy, modify, and/or distribute this software for any purpose
with or without fee is hereby granted.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF
THIS SOFTWARE.
```

> No GPL/LGPL code will ever be read and learned from during my journey.  
> No unlicensed code will ever be read and learned from during my journey.  
> Portions of code from open source projects will be attributed appropriately.
> 
> _I'm mostly going to rely on videos and, if necessary, MIT/BSD/Apache-style licenced projects._  
> _This is so that you can use any of this code freely, **without attribution** requirements._

# Learning Resources

**These are not official recommendations, I have not watched all of them!**

> **GH** is [Guided Hacking](https://www.youtube.com/@GuidedHacking)
> > Note: my IP is blocked from their website, even though I have **never** been there before.
> > So the only content I have available to me, as a learner, is what they have on YouTube. 

- GH: Cheat Engine Tutorial Guide (**PLAYLIST TODO**)
  - [GH: Cheat Engine Tutorial Guide 1/3 Steps 1-5](https://youtu.be/Nib69uZJCaA)
  - [GH: Cheat Engine Tutorial Guide 2/3 Steps 6-9 Pointers & Code Injection](https://youtu.be/yjdSxL2DWfE)
  - [GH: Cheat Engine Tutorial Guide 3/3 Tutorial Games](https://youtu.be/H9_0exi5tCU)

- GH: C++ How To Hack Any Game Tutorial ([playlist](https://www.youtube.com/playlist?list=PL2C03D3BB7FAF2EA0))
  - [GH: How To Find Offsets, Entity Addresses & Pointers](https://youtu.be/YaFlh2pIKAg)
  - [GH: How to Hack Any Game C++ External Trainer Assault Cube 1/2](https://youtu.be/wiX5LmdD5yk)
  - [GH: How to Hack Any Game C++ External Trainer Assault Cube 2/2](https://youtu.be/UMt1daXknes)
  - [GH: C++ How to Hack Any Game - Internal Hack Tutorial](https://youtu.be/hlioPJ_uB7M)

- GH: Game Hacking 200 Series - Game Hacking Shenanigans ([playlist](https://www.youtube.com/playlist?list=PLt9cUwGw6CYFKVpM1mJoz2yBMVMjl_f5F))
  - [GH: How to Make Cheat Engine Scripts | GH201](https://youtu.be/BofjhNsR-FU)
  - [GH: Cheat Engine Code Injection Tutorial | GH202](https://youtu.be/I9xO2mtpYgI)
  - [GH: Cheat Engine Shared OpCode Tutorial | GH203](https://youtu.be/Twj1cdG6DcE)
  - [GH: Cheat Engine Floating Point Values & XMM Registers | GH204](https://youtu.be/EL0rGxCz0gs)
  - [GH: Cheat Engine One Hit Kills & God Mode Tutorial | GH205](https://youtu.be/9eNbydCXW-E)
  - [GH: Cheat Engine Damage Multiplier Script Tutorial | GH206](https://youtu.be/nv6Iidq7BTA)
  - [GH: Cheat Engine Floats - Defense & Damage Boost | GH207](https://youtu.be/zxb_OC8-wl4)
  - [GH: Defense Boost with Integers in Cheat Engine Tutorial | GH208](https://youtu.be/J6yqIyYOGXU)
  - [GH: Intro to Complex Cheat Engine Scripts | GH209](https://youtu.be/0_-0nxd805I)
  - [GH: How To Update Broken Cheat Engine Table Scripts | GH210](https://youtu.be/Aa7TEpeiD2c)

- GH: CS420 Game Hacking Course ([playlist](https://www.youtube.com/playlist?list=PLt9cUwGw6CYG1b4L76vZ49tvI2mfmRSCl))
  - [GH: CS420 - 1 Game Hacking Course Introduction](https://youtu.be/hj4rhfnikVs)
  - [GH: CS420 - 2 Memory Editing 1 - Game Hacking Course](https://youtu.be/xOBE_vWDX_I)
  - [GH: CS420 - 3 Base Systems - Hex, Decimal & Binary](https://youtu.be/nA7o5kmH6wg)
  - [GH: CS420 - 4 - How to Hex Edit Games - Game Hacking Course](https://youtu.be/EpcK8uk7lcY)
  - [GH: CS420 - 5 - Memory Editing & Data Types - Game Hacking Course](https://youtu.be/6KNNRqjpgGE)
  - [GH: CS420 6 - What is Virtual Memory ? Full Course](https://youtu.be/aPNcEckD1Qk)
  - [GH: CS420 7 - Virtual Memory & Multilevel Pointers Tutorial](https://youtu.be/_W0xdVO8-j4)
  - [GH: CS420 8 - How to Edit Assembly Tutorial](https://youtu.be/_Sm84vARhbw)

- GH: ReClass Tutorials ([playlist](https://www.youtube.com/playlist?list=PLt9cUwGw6CYHYGsDbI9QnHIJ9q67jzlzL))
  - [GH: How To Use ReClass Tutorial](https://youtu.be/DyqnhSkcVIw)
  - [GH: Reverse Engineering Tutorial No Recoil IDA Pro & ReClass](https://youtu.be/wEkwCW4oJrY)
  - [GH: How to Find and Reverse the CSGO EntityList with ReClass.NET](https://youtu.be/oXlOboQURy0)
  - [GH: Assault Cube TriggerBot Tutorial - Reversing, ReClass & More](https://youtu.be/HZsnoUWK4Do)
  - [GH: Reversing Engineering FlyHack Tutorial NoClip IDA pro Cheat Engine C++](https://youtu.be/tpjwuZCcheQ)
  - [GH: How to Find the ViewMatrix Offset CSGO](https://youtu.be/crT9zGviqVs)
  - [GH: Reclass Tutorial - ReClass.NET - How To Reverse Structures](https://youtu.be/vQb21RM9-5M)
  - [GH: GH Entity List Finder Tutorial](https://youtu.be/F9mwwIqkeqE)

- GH: Manual Mapping DLL Injection Tutorial ([playlist](https://www.youtube.com/playlist?list=PLt9cUwGw6CYEX6mVdDAly7oZOgpsZOycp))
  - [GH: Manual Mapping DLL Injection Tutorial - How to Manual Map 1of4](https://youtu.be/qzZTXcBu3cE)
  - [GH: Manual Mapping DLL Injection Tutorial 2of4](https://youtu.be/EXRm7tCOwGg)
  - [GH: Manual Mapping DLL Injection Tutorial 3of4](https://youtu.be/c8B--5lKbNg)
  - [GH: Manual Mapping DLL Injection Tutorial 4of4](https://youtu.be/_7SvkCGE67M)

- GH: C++ Skyrim Hacking Tutorial ([playlist](https://www.youtube.com/playlist?list=PLt9cUwGw6CYHGTfaPSywuS-lZfBpozPa9))
  - [GH: C++ Skyrim Cheats Part1: Introduction & Overlay](https://youtu.be/i8Cn7fydNUA)
  - [GH: C++ Skyrim Cheats Part2: How to Find Entitylist & Hooking](https://youtu.be/aYN7IjGubuY)
  - [GH: C++ Skyrim Hacks Part3: Writing the ESP](https://youtu.be/jOwTVLqaEsw)
  - [GH: C++ Skyrim Hacks Part4: NoClip Hack Tutorial Part 1](https://youtu.be/-ZJyAWDQXzM)
  - [GH: C++ Skyrim Hacks Part5: NoClip Part 2](https://youtu.be/W0IgSTlGJTY)
  - [GH: C++ Skyrim Mods Part6: Map Teleport & ASM](https://youtu.be/NzyFl4_LM3M)
  - [GH: C++ Skyrim Mods Part 7: Find Bones & Write ESP](https://youtu.be/JtWPpbLAh8Q)

- GH: OpenGL ESP Tutorial ([playlist](https://www.youtube.com/playlist?list=PLt9cUwGw6CYEER_157GkcVNVnn9oGdTEz))
  - [GH: C++ Internal Trampoline Hook Tutorial - OpenGL Hook](https://youtu.be/HLh_9qOkzy0)
  - [GH: OpenGL Hook - SwapBuffers Hook Tutorial - Drawing & Text 1/2](https://youtu.be/dEgva5-OsSY)
  - [GH: OpenGL Hook - SwapBuffers Hook Tutorial - Drawing & Text 2/2](https://youtu.be/6JV0dmLWMNs)
  - [GH: How to make an OpenGL ESP Tutorial](https://youtu.be/kGDKQXgxIrY)

- C++ How to make a DIRECTX MENU CHEAT
  - [GH: C++ How to make a DIRECTX MENU CHEAT Pt 1/6](https://youtu.be/oWuIUzBtdcM)
  - [GH: C++ How to make a DIRECTX MENU Cheat Pt 2/6](https://youtu.be/y-YvN6SLv4Y)
  - [GH: C++ How to make a DIRECTX MENU Cheat Pt 3/6](https://youtu.be/xQUYuNRTvb8)
  - [GH: C++ How to make a DIRECTX MENU Cheat Pt 4/6](https://youtu.be/jQx-I0Csa5w)
  - [GH: C++ How to make a DIRECTX MENU Cheat Pt 5/6](https://youtu.be/q7M2-90mMmc)
  - [GH: C++ How to make a DIRECTX MENU Cheat Pt 6/6](https://youtu.be/62iFdscv_M0)

- Casual Gamer: How To Make An ESP Hack ([playlist](https://www.youtube.com/playlist?list=PLZ4C_iMwBO68DzDYDNC28bh1wxrewTDYr))
  - [Casual Gamer: How To Make An ESP Hack - Part 1: Entity List](https://youtu.be/SPHARh6ukog)
  - [Casual Gamer: How To Make An ESP Hack - Part 2: World To Screen](https://youtu.be/pd4O1-7o3dc)
  - [Casual Gamer: How To Make An ESP Hack - Part 3: Drawing Rectangles](https://youtu.be/fOHPaBkwvyk)

- Casual Gamer: Terraria ([playlist](https://www.youtube.com/playlist?list=PLZ4C_iMwBO698cGY-v2UUsooUQ2qecj3J))
  - [Casual Gamer: Hacking Terraria in C++ | (1/3) | Self unloading DLL](https://youtu.be/uuMg7CeJF1k)
  - [Casual Gamer: Hacking Terraria in C++ | (2/3) | Internal Signature Scanning](https://youtu.be/l025elxvmX8)
  - [Casual Gamer: Hacking Terraria in C++ | (3/3) | Player Base Pointer, Ghost Mode & Teleport Hack](https://youtu.be/PEOK7iww3zQ)

- Casual Gamer (Misc)
  - [Casual Gamer: Simulate Keyboard In Games | C++ Game Hacking](https://youtu.be/L271J_lKyRA)
  - [Casual Gamer: How To Make A DLL Injector C++](https://youtu.be/44-TOfLGBzk)
  - [Casual Gamer: Hooking DirectX9](https://youtu.be/20wXiQMVMpA)
  - [Casual Gamer: Hooking DirectInput C++](https://youtu.be/oh9i7hPQZT8)
  - [Casual Gamer: How To Hook DirectX 11](https://youtu.be/fChxV6rypIg)
  - [Casual Gamer: Game Hack Menu](https://youtu.be/NcClcNlsfdw)
  - [Casual Gamer: Cheat Engine THREADSTACK Pointers - C++ Game Hacking Tutorial Part 5 | Memory Hacking](https://youtu.be/YDHE42QIRNQ)

- GH (Misc)
  - [GH: What is the Windows API? What is Windows.h?](https://youtu.be/S4lQwJawOzI)
  - [GH: Simple C++ DLL Injector Source Code Tutorial - Quick and EZ](https://youtu.be/PZLhlWUmMs0)
  - [GH: How To Find the EntityList in Assault Cube with Cheat Engine Tutorial](https://youtu.be/TCu0qSivXUc)
  - [GH: How To Hack Any Game With Cheat Engine - Pointers & EntityBase](https://youtu.be/fvv8IJGke1Q)

Other (Misc)
  - [Stephen Champan Hacking Videos - Playlist](https://www.youtube.com/playlist?list=PLNffuWEygffbJGq_cffRgEzFk6N1wrKtx)
  - [Hex Murder: How to find an Entity List / Object List | Cheat Engine](https://youtu.be/0Hr-8rH3nWs)

Articles:
  - https://www.thehackerwithin.com/blog/11-08-07/Steam_s_anti-debugging_code.aspx
