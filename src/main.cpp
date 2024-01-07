#include <Windows.h>
#include <cstdio>
#include <string>
#include "imgui/imgui.h"

bool menuVisible = false;

char logoSOT[] =
"                                    &@@@@@@@@@@&                                \n"
"                            @/#@@@@@@@@@@@@@@@@@@@@@@@@                         \n"
"                       %@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%@@@@                    \n"
"                    @@@@@@@@@@@@@@, %@@@@@@@@@@@@   .                           \n"
"                  @@@        %@@@@@@@@@@@@  @@           *@@@@@/                \n"
"                ,&    @@@@@@@@@@@@@@@@@@@  .       @@@@@@@@@@@@@%               \n"
"                  %@@@@@@@@@@&   @@@@        @@@@@@@@@@@@@@@@@@@*               \n"
"              @@@@@@@@@@@ &(& # @@@*   %@@@@@@@@@@@@@#@@@@@@@@@@@@@             \n"
"            %@@@@@@@@@@@@       #  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@            \n"
"            @@@@@@@@@@            @@@@@@@@@@@@@@@,@@@@@@@@@@& @@@@@@@@          \n"
"            &@@@@@@@@@         @  @@@@@@@@@@@@@@@@@@@@@@@@    @@@@@@@@          \n"
"             @@@@@@@   ,            @@@@@@@@@@@@@@@@@@@*      @@@@@@@@          \n"
"            @@@     @@@#            @@@@@@@@@@@@@@@@@      ,   @@@@@@@          \n"
"               @    %@              @@@@ &@@@@@@@@@     ,      @@@@@@           \n"
"                      @%.     &/  @   &@@@@@@@@@        (      @@@@@            \n"
"             ,                      &@@@@@@@@@@@              @@@@@@            \n"
"           @@@@@                   @@@@      @@*,.     /.,(,    &@@@@           \n"
"          @@@@% /@  ,/.&          /@@@        @@@@@@@@@@@@@@@@@@@@@@@@@         \n"
"               @@@@@@@@@@@@@@@@@@@@@      @    @@@@@@@@@@@@@@@@@@@@@@           \n"
"               @@@@@@@@@@@@@@@   .@@%   @@@     @@@@@@@@.   @@@@@@              \n"
"                 &@@@@@@@@@@@@@@@@      %@@@@ .,@*.@@@@@@  *@@@@@@              \n"
"                        @@@@@@@@@@@@@@@@@@@@@@@@@@ @@@@@     &@@@               \n"
"                          /@@@@@@@@@@@@@@@@@@@@@@@@ @@@                         \n"
"                          @@@@  @@ .@@@@@@@@@  #@@@   @                         \n"
"                           @@&        @@@@,    @@@@@@@                          \n"
"                           ( @#      @@@@@@    @@@@@@                           \n"
"                           @@@       @@@@*      @@@@@                           \n"
"                                     @@@@#     @  @                             \n\n";

bool IsTargetProcess()
{
    char szFileName[MAX_PATH];
    GetModuleFileName(NULL, szFileName, MAX_PATH);

    std::string processName = strrchr(szFileName, '\\') + 1;

    if (processName != "SoTGame.exe")
    {
        MessageBox(NULL, "This program only work with Sea of Thieves (SoTGame.exe) !", "Error", MB_OK | MB_ICONERROR);
        return false;
    }

    return true;
}

DWORD WINAPI MainThread(LPVOID lpParam)
{
    AllocConsole();
    AttachConsole(GetCurrentProcessId());

    FILE* pConsole;
    freopen_s(&pConsole, "CONOUT$", "w", stdout);

    printf(logoSOT);
    printf("The program is now initialized and ready for use.\n\nINSERT = Open menu\nDELETE = Silent exit\n\n");

    while (true)
    {
        if (GetAsyncKeyState(VK_INSERT) & 1)
        {
            if (!menuVisible)
            {
                printf("afficher menu\n");
                menuVisible = true;
            }
            else
            {
                printf("cacher menu\n");
                menuVisible = false;
            }
        }
        if (GetAsyncKeyState(VK_DELETE) & 1)
        {
            HWND hwndConsole;
            hwndConsole = GetConsoleWindow();
            ShowWindow(hwndConsole, SW_HIDE);

            FreeConsole();
            FreeLibraryAndExitThread(static_cast<HMODULE>(lpParam), 0);
        }
        Sleep(20);
    }

    FreeConsole();
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        if (IsTargetProcess())
        {
            CreateThread(nullptr, 0, MainThread, hModule, 0, nullptr);
        }
        break;
    case DLL_PROCESS_DETACH:
        break;
    }

    return TRUE;
}