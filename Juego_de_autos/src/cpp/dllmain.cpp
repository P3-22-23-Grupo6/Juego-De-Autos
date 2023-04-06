// dllmain.cpp : Define el punto de entrada de la aplicación DLL.
#include "pch.h"
#include <iostream>
#include "MotorApi.h"

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


extern "C" __declspec(dllexport) const char* InitJuego(MotorApi* motor)
{
    std::cout << "Ya no se" << std::endl;

    motor->RegisterGame("Juego de autos");

#ifdef _DEBUG
    return "Juego de autos: Running in DEBUG";
#endif // _DEBUG
    return "Juego de autos: Running in RELEASE";
}