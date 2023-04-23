#include "PlayerController.h"
#include "GameObject.h"
#include "Transform.h"
#include "RaceManager.h"
#include <iostream>

#include "RigidBodyComponent.h"
#include "InputManager.h"
#include "LMInputs.h"

//std::string PlayerController::name = "PlayerController";

PlayerController::PlayerController()
{
	raceManager = RaceManager::GetInstance();
}

PlayerController::~PlayerController()
{
}

void PlayerController::Init(std::vector<std::pair<std::string, std::string>>& params)
{
	std::cout << "PLayer Controller I am \n\n\n\n\n";
}


void PlayerController::InitComponent()
{
	// Referencias al componente rigidbody y al singleton InputManager
	rbComp = gameObject->GetComponent<LocoMotor::RigidBodyComponent>();
	inputMng = LocoMotor::InputManager::GetInstance();
}

void PlayerController::Update(float dt)
{
	// Mover el coche

	//rbComp = gameObject->GetComponent<LocoMotor::RigidBodyComponent>();
	//LocoMotor::InputManager* inputMng = LocoMotor::InputManager::GetInstance();
	
	//rbComp->useGravity(LMVector3(0, 0, 0));
	//rbComp->addForce(LMVector3(0, 0, 0));
	//bool b = inputMng->GetKey(LMKS_W);








	// Actualizar las posiciones del raceManager
	LMVector3 pos = gameObject->GetTransform()->GetPosition();
	raceManager->UpdateCarPosition("player", pos.GetX(), pos.GetY(), pos.GetZ());
}