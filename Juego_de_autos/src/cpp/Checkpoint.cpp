#include "Checkpoint.h"
//#include "RenderScene.h"
#include "Scene.h"
#include "GameObject.h"
#include "RaceManager.h"
//#include "Node.h"

#include "pch.h"
#include "RigidBodyComponent.h"

using namespace LocoMotor;

const std::string Checkpoint::name = "CheckPoint";

Checkpoint::Checkpoint() {
	_player = nullptr;
	_checkpointIndex = 0;
	checked = false;

	
	raceManager = RaceManager::GetInstance();
}

//LocoMotor::Checkpoint::Checkpoint(GameObject* player, int checkpointIndex) {
//
//	_player = player;
//	_checkpointIndex = checkpointIndex;
//	_rb = nullptr;
//	checked = false;
//}

void Checkpoint::Start(LocoMotor::GameObject* player, int checkpointIndex) {

	_player = player;
	_checkpointIndex = checkpointIndex;
	checked = false;

	////// Acceder al componente Rigidbody
	////_rb = gameObject->GetComponent<RigidBodyComponent>();
	////if (_rb == nullptr)
	////	std::cout << "[ERROR] : Rigidbody needed for Checkpoint";
}

void Checkpoint::Update(float dt) {

	// COLISION

	//if (_rb->checkCollision(_player))
	//	// Comunicar al racemanager que este checkpoint ha sido alcanzado por el jugador
	//	std::cout << "COLLISION" << "\n" << "\n";


	// DISTANCIAS
	float distance = (_player->GetTransform().position - gameObject->GetTransform().position).Magnitude();

	if (distance < 40)
		checked = true;


	std::cout << "DISTANCE = " << distance << "\n";
}
