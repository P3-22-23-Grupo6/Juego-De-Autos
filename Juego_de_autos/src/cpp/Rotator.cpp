#include "Rotator.h"
#include "GameObject.h"
#include "Transform.h"
#include "RaceManager.h"

#include "RigidBody.h"
#include "Boost.h"

using namespace JuegoDeAutos;
using namespace LocoMotor;

const std::string Rotator::name = "Rotator";

Rotator::Rotator() {
	rotateVel = 0;
}

void Rotator::Init(std::vector<std::pair<std::string, std::string>>& params) {
	for (int i = 0; i < params.size(); i++) {
		if (params[i].first == "Speed") {
			rotateVel = std::stof(params[i].second);
		}
	}
	//_body = nullptr;
}

void Rotator::InitComponent() {

}

void Rotator::Update(float dt) {
	LMVector3 up = gameObject->GetTransform()->GetRotation().Up();
	LMQuaternion newRotation = gameObject->GetTransform()->GetRotation().Rotate(up, rotateVel * dt);
	gameObject->GetTransform()->SetRotation(newRotation);
}