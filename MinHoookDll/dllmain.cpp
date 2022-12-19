// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

#include "MinHook.h"



typedef DWORD(NTAPI* pNtDelayExecution)( // https://malapi.io/winapi/NtDelayExecution
    IN BOOLEAN Alertable,
    IN PLARGE_INTEGER DelayInterval
    );


extern pNtDelayExecution pOrigNtDelayExecution = (pNtDelayExecution)GetProcAddress(GetModuleHandle(L"ntdll.dll"), "NtDelayExecution");

// our modified NtDelayExecution
DWORD NTAPI NtDelayExecution(IN BOOLEAN Alertable, IN PLARGE_INTEGER DelayInterval)
{
    // Mock this poor attempt >:)
    MessageBoxA(0, "Feeling sleepy??", ":)", 0);


    // Make it so NtDelayExecution actually gets called with a delay of 0, basically nullifying the sleep.
    return pOrigNtDelayExecution(Alertable, (PLARGE_INTEGER)0);
}


DWORD WINAPI hook_thread(LPVOID lpReserved) {

    MH_STATUS status = MH_CreateHookApi(TEXT("ntdll"), "NtDelayExecution", NtDelayExecution, reinterpret_cast<LPVOID*>(&pOrigNtDelayExecution));

    // Enable hooks
    status = MH_EnableHook(MH_ALL_HOOKS);
    return status;
}


// main function of the dll
BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH: {

        // Initialize, and if that fails just return -1 aka ERROR
        if (MH_Initialize() != MH_OK) return -1;

        DisableThreadLibraryCalls(hModule);

        // Create hooked thread
        HANDLE hThread = CreateThread(nullptr, 0, hook_thread, hModule, 0, nullptr);
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }

    return TRUE;
}