#include <Windows.h>
#include <string>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_win32.h>
#include <imgui/imgui_impl_dx11.h>

#include "main.h"
#include "gui.h"

bool endProgram()
{
    // Code pour éteindre tout
    // ...
    return true;
}

DWORD WINAPI MainThread(LPVOID lpParam)
{
    AllocConsole();
    AttachConsole(GetCurrentProcessId());

    FILE* pConsole;
    freopen_s(&pConsole, "CONOUT$", "w", stdout);

    printf("%s\nThe program is now initialized and ready for use.\n\nINSERT = Open menu\nDELETE = Silent exit\n\n", logoSOT);

    while (true)
    {
        if (GetAsyncKeyState(VK_INSERT) & 1)
        {
            menuVisible = !menuVisible;
            printf("test\n");
        }
        if (GetAsyncKeyState(VK_DELETE) & 1)
        {
            // code pour éteindre toute traces de l'injection
            // ...
        }
        Sleep(20);
    }

    endProgram();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(nullptr, 0, MainThread, hModule, 0, nullptr);
        break;
    case DLL_PROCESS_DETACH:
        break;
    }

    return TRUE;
}