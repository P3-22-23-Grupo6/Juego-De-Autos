#include "Scene.h"
#include "GameObject.h"
#include "Transform.h"
#include "LMSpline.h"

#include "RigidBody.h"
#include "EnemyAI.h"

using namespace JuegoDeAutos;
using namespace LocoMotor;

const std::string EnemyAI::name = "EnemyAI";

EnemyAI::EnemyAI() {
	mySpline = nullptr;
	timeStep = 0;
	enemySpeed = 0;
	startSeparation = 0;
}

void EnemyAI::Init(std::vector<std::pair<std::string, std::string>>& params) {
	for (int i = 0; i < params.size(); i++) {
		if (params[i].first == "enemySpeed") {
			enemySpeed = std::stof(params[i].second);
		}
		else if (params[i].first == "StartSeparation") {
			startSeparation = std::stof(params[i].second);
		}
		else if (params[i].first == "Spline") {
			startSeparation = std::stof(params[i].second);
		}
	}
	//_body = nullptr;
}

void EnemyAI::InitComponent() {

}

void EnemyAI::Update(float dt) {
	timeStep += 0.0005f * enemySpeed;
	if (timeStep > 1) {
		timeStep = 0.0f;
	}
	LMVector3 from = gameObject->GetTransform()->GetPosition();
	LMVector3 to = from + LMVector3(0, -20, 0);

	LMVector3 upVector = gameObject->GetTransform()->GetRotation().Up();
	upVector.Normalize();
	RigidBody* rbComp = gameObject->GetComponent<RigidBody>();
	double raycastDistance = 7;
	upVector = upVector * raycastDistance;
	to = from - upVector;

	if (rbComp->GetRaycastHit(from, to)) {
		LMVector3 n = rbComp->GethasRaycastHitNormal(from, to);
		LMVector3 newUp = n * 40;
		gameObject->GetTransform()->SetUpwards(newUp);
	}

	//Interpolate Position
	LMVector3 newPos = mySpline->Interpolate(timeStep);
	newPos = newPos + gameObject->GetTransform()->GetRotation().Right() * startSeparation;
	//LookAt
	gameObject->GetTransform()->LookAt(newPos);
	//Set Position
	gameObject->SetPosition(newPos);
}
