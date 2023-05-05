#include "Checkpoint.h"
//#include "RenderScene.h"
#include "Scene.h"
#include "GameObject.h"
#include "Transform.h"
#include "RaceManager.h"
#include "PlayerController.h"
//#include "Node.h"

#include "RigidBody.h"
using namespace JuegoDeAutos;
using namespace LocoMotor;

const std::string Checkpoint::name = "CheckPoint";

int Checkpoint::numCheckpoints = 0;

Checkpoint::Checkpoint() {

	_checkpointIndex = numCheckpoints;
	numCheckpoints++;
	checked = false;
	raceManager = RaceManager::GetInstance();
}

void Checkpoint::InitComponent() {

	raceManager = RaceManager::GetInstance();
	raceManager->RegisterCheckpointPosition(gameObject->GetTransform()->GetPosition());
}
