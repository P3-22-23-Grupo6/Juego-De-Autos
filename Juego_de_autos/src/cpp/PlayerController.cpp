#include "pch.h"
#include "PlayerController.h"
#include "GameObject.h"
#include "RaceManager.h"
#include <iostream>

//std::string PlayerController::name = "PlayerController";

PlayerController* PlayerController::_instance = nullptr;

PlayerController::PlayerController()
{
	_instance = this;

	raceManager = RaceManager::GetInstance();
}

PlayerController::~PlayerController()
{
}

void PlayerController::Init(std::vector<std::pair<std::string, std::string>>& params)
{
	std::cout << "PLayer Controller I am \n\n\n\n\n";
}

void PlayerController::Update(float dt)
{
	std::cout << "PLayer Controller I am \n\n\n\n\n";

	// Actualizar las posiciones del raceManager
	LMVector3 pos = gameObject->GetTransform().position;

	raceManager->UpdateCarPosition("player", pos.GetX(), pos.GetY(), pos.GetZ());
}

void PlayerController::InitComponent()
{
}


PlayerController* PlayerController::GetInstance()
{ return _instance; }