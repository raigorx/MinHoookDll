# Minhook simple dll attach example

Based on https://shubakki.github.io/posts/2022/12/detecting-and-evading-sandboxing-through-time-based-evasion/

Simple minhook example via run-time dynamic linking for fun and learning

## How to Build/Compile

- Visual studio 2022 and its workload Desktop development with C++ are requiere
- https://github.com/TsudaKageyu/minhook I recommend installing it via vcpkg

## Code structure

- **MinHookClient** console win app that load the MinHoookDll
- **MinHoookDll** dll that hooks NtDelayExecution on DLL_PROCESS_ATTACH
