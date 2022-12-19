// MinHookClient.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <windows.h>
#include <iostream>

int main()
{
    HMODULE hHookEngineDll = LoadLibrary(L"MinHoookDll.dll");
    // wait for key press to avoid race condition (Sleep 1 run before being hooked)
    system("pause");
    printf("Sleep 1 now!\n");
    Sleep(100000);
    printf("Sleep 2 now\n");
    Sleep(100000);
    return 0;
}
