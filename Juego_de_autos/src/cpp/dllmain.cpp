// dllmain.cpp : Define el punto de entrada de la aplicación DLL.
#include "pch.h"
#include <iostream>

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

extern "C" __declspec(dllexport) const char* InitJuego()
{
    std::cout << "im so bored morty im im gonna kill you" << std::endl;

#ifdef _DEBUG
    return "Juego de autos: Running in DEBUG";
#endif // _DEBUG
    return "Juego de autos: Running in RELEASE";
}