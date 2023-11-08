#include "Scene.h"
#include "GameObject.h"
#include "Transform.h"
#include "RaceManager.h"
#include "RigidBody.h"
#include "PlayerController.h"
#include "Water.h"

using namespace JuegoDeAutos;
using namespace LocoMotor;

const std::string Water::name = "Water";

Water::Water() {
}

void Water::Init(std::vector<std::pair<std::string, std::string>>& params) {
	
}

void Water::OnCollisionEnter(GameObject* other)
{
	PlayerController* ply = other->GetComponent<PlayerController>();
	if (ply == nullptr) return;
	other->GetComponent<PlayerController>()->KillPlayer();
}
