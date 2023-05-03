#include "Scene.h"
#include "GameObject.h"
#include "Transform.h"
#include "RaceManager.h"

#include "RigidBody.h"
#include "Boost.h"
#include "Boost.h"

using namespace JuegoDeAutos;
using namespace LocoMotor;

const std::string Boost::name = "Boost";

Boost::Boost() {
	thrust = 2000;
}

void Boost::Init(std::vector<std::pair<std::string, std::string>>& params) {
	for (int i = 0; i < params.size(); i++) {
		if (params[i].first == "thrust") {
			thrust = std::stof(params[i].second);
		}
	}
	//_body = nullptr;
}

void Boost::InitComponent() {

}

void Boost::Update(float dt) {

}

void Boost::OnCollisionEnter(GameObject* other)
{
 other->GetComponent<RigidBody>()->addForce(LMVector3(other->GetTransform()->GetRotation().Forward() * thrust));
}
