# Repository Layout

## Games
  - [Game]
    - Cheat Engine
    - IDA
    - Libraries
      - [Cpp/Rust/Other]
        - Lib[Game]
    - Tools
      - [Game].Cheats.UI

## Libraries
  - [Cpp/Rust/Other]
    - UI
        - ButtonsApp
    - Logging
        - BringYourOwnLogger
    - Formatting
        - FmtCompatibility
    - RE
        - LibRE

## Tools
    - DLLInjector
        - CLI
        - UI

## Resources

- Resources
  - Images
  - Fonts

## vcpkg

_This repo should be a valid vcpkg repo:_
- ports
- versions

## C++

_And has top-level vcpkg and CMake config etc_
- CMakeLists/Presets/clang-tidy/clang-format/...
- vcpkg.json/vcpkg-configuration/...
