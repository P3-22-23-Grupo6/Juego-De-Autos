#include "Scene.h"
#include "GameObject.h"
#include "Transform.h"
#include "RaceManager.h"
#include "AudioSource.h"

#include "RigidBody.h"
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
}

void Boost::OnCollisionEnter(GameObject* other)
{
	other->GetComponent<RigidBody>()->AddForce(LMVector3(other->GetTransform()->GetRotation().Forward() * thrust));
	if (gameObject->GetComponent<AudioSource>() != nullptr)
		gameObject->GetComponent<AudioSource>()->Play("Assets/Sounds/BoostSFX.wav");
}
