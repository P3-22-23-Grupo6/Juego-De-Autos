// dllmain.cpp : Define el punto de entrada de la aplicación DLL.
#include "pch.h"
#include <iostream>
#include "MotorApi.h"
#include "ComponentsFactory.h"
#include "PlayerController.h"
#include "Checkpoint.h"
#include "RaceManager.h"
#include "ScriptManager.h"
#include "Rotator.h"
#include "Boost.h"
#include "CameraPanner.h"
#include "Water.h"
#include "EnemyAI.h"
#include "SceneChangeButton.h"
using namespace LocoMotor;
using namespace JuegoDeAutos;


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


extern "C" __declspec(dllexport) const char* InitJuego(LocoMotor::MotorApi* motor)
{
    LocoMotor::ComponentsFactory::GetInstance()->RegisterComponent<PlayerController>("PlayerController");
    LocoMotor::ComponentsFactory::GetInstance()->RegisterComponent<Checkpoint>("Checkpoint");
    LocoMotor::ComponentsFactory::GetInstance()->RegisterComponent<RaceManager>("RaceManager");
    LocoMotor::ComponentsFactory::GetInstance()->RegisterComponent<Boost>("Boost");
    LocoMotor::ComponentsFactory::GetInstance()->RegisterComponent<SceneChangeButton>("SceneChangeButton");
    LocoMotor::ComponentsFactory::GetInstance()->RegisterComponent<EnemyAI>("EnemyAI");
    LocoMotor::ComponentsFactory::GetInstance()->RegisterComponent<Rotator>("Rotator");
    LocoMotor::ComponentsFactory::GetInstance()->RegisterComponent<CameraPanner>("CameraPanner");
    LocoMotor::ComponentsFactory::GetInstance()->RegisterComponent<Water>("Water");

    motor->RegisterGame("Juego de autos");

    LocoMotor::ScriptManager::GetInstance()->LoadSceneFromFile("Assets/Scenes/intro.lua");

#ifdef _DEBUG
    return "Juego de autos: Running in DEBUG";
#endif // _DEBUG
    return "Juego de autos: Running in RELEASE";
}