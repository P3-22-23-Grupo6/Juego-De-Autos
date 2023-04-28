#include "Checkpoint.h"
//#include "RenderScene.h"
#include "Scene.h"
#include "GameObject.h"
#include "Transform.h"
#include "RaceManager.h"
#include "PlayerController.h"
//#include "Node.h"

#include "RigidBodyComponent.h"
using namespace JuegoDeAutos;
using namespace LocoMotor;

const std::string Checkpoint::name = "CheckPoint";

int Checkpoint::numCheckpoints = 0;

Checkpoint::Checkpoint() {

	_checkpointIndex = numCheckpoints;
	numCheckpoints++;

	checked = false;

	
	raceManager = RaceManager::GetInstance();
	//_player_gObj = PlayerController::GetInstance()->gameObject;
	//_player_gObj = PlayerController::GetInstance()->gameObject;
}

void Checkpoint::InitComponent() {

	raceManager = RaceManager::GetInstance();
	//_player = PlayerController::GetInstance();


	raceManager->RegisterCheckpointPosition(gameObject->GetTransform()->GetPosition());
}

void Checkpoint::Update(float dt) {

	// COLISION

	//if (_rb->checkCollision(_player))
	//	// Comunicar al racemanager que este checkpoint ha sido alcanzado por el jugador
	//	std::cout << "COLLISION" << "\n" << "\n";



	// DISTANCIAS
	//float distance = (_player_gObj->GetTransform().position - gameObject->GetTransform().position).Magnitude();
	//float distance = (PlayerController::GetInstance()->gameObject->GetTransform().position - gameObject->GetTransform().position).Magnitude();

	//if (distance < 40) {

	//	raceManager->CheckpointReached("player");
	//}

	//std::cout << "CHECKPOINT NUMBER " << _checkpointIndex << "\n";
}
