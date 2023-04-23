#include "PlayerController.h"
#include "GameObject.h"
#include "Transform.h"
#include "RaceManager.h"
#include <iostream>
#include "RigidBodyComponent.h"

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
	// Mover el coche

	LocoMotor::RigidBodyComponent* rbComp = gameObject->GetComponent<LocoMotor::RigidBodyComponent>();

	//rbComp->useGravity(LMVector3(0, 0, 0));

	//rbComp->addForce(LMVector3(1, 1, 1));



	// Actualizar las posiciones del raceManager
	LMVector3 pos = gameObject->GetTransform()->GetPosition();
	raceManager->UpdateCarPosition("player", pos.GetX(), pos.GetY(), pos.GetZ());
}

void PlayerController::InitComponent()
{
}


PlayerController* PlayerController::GetInstance()
{ return _instance; }
