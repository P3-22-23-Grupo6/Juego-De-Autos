#include "Scene.h"
#include "GameObject.h"
#include "Transform.h"
#include "LMSpline.h"
#include "RaceManager.h"

#include "RigidBody.h"
#include "EnemyAI.h"

using namespace JuegoDeAutos;
using namespace LocoMotor;

const std::string EnemyAI::name = "EnemyAI";

EnemyAI::EnemyAI() {
	rbComp = nullptr;
	mySpline = nullptr;
	timeStep = 0;
	enemySpeed = 0;
	startSeparation = 0;
	_shouldMove = true;
	tr = nullptr;
	lastPos = LMVector3();
	grounded = false;
}

void EnemyAI::Init(std::vector<std::pair<std::string, std::string>>& params) {
	for (int i = 0; i < params.size(); i++) {
		if (params[i].first == "enemySpeed") {
			enemySpeed = std::stof(params[i].second);
		}
		else if (params[i].first == "StartSeparation") {
			startSeparation = std::stof(params[i].second);
		}
	}
	//_body = nullptr;
}

void JuegoDeAutos::EnemyAI::Start()
{
	tr = gameObject->GetTransform();
	RaceManager* rmngr = RaceManager::GetInstance();
	rbComp = gameObject->GetComponent<RigidBody>();
	if (rmngr == nullptr || rbComp == nullptr) {
		SetActive(false);
		return;
	}
	mySpline = rmngr->GetSpline();
	rbComp->UseGravity(LMVector3(0, 0, 0));
	enemySpeed = rmngr->GetSpeed() * enemySpeed;
	
	lastPos = tr->GetPosition();
	SetUpwards();

	//Sinceramente no se me ocurre una mejor forma, esto funciona :L
	enemySpeed /= 10000.0f;
}



void EnemyAI::Update(float dt) {
	if (!_shouldMove)
	{
		_shouldMove = RaceManager::GetInstance()->HasCountDownFinished();
		return;
	}

	timeStep += enemySpeed * dt/1000.0f;
	if (timeStep > 1) {
		timeStep = 0.0f;
	}
	MoveEnemy(dt);
	
}
void EnemyAI::MoveEnemy(float dt)
{
	SetUpwards();
	LMVector3 finalPos;
	finalPos = finalPos.Lerp(lastPos, mySpline->Interpolate(timeStep), timeStep);
	finalPos = finalPos + gameObject->GetTransform()->GetRotation().Right() * startSeparation;
	gameObject->SetPosition(finalPos);
	lastPos = finalPos;
	////LookAt
	float newLookAt = timeStep + 0.1f;
	if (timeStep > 1.0f) timeStep = 0.0f;
	gameObject->GetTransform()->LookAt(mySpline->Interpolate(newLookAt) + tr->GetRotation().Right() * startSeparation);
}

void JuegoDeAutos::EnemyAI::SetUpwards()
{
	LMVector3 from = tr->GetPosition();
	LMVector3 to;
	LMVector3 upVector = tr->GetRotation().Up();
	upVector.Normalize();
	upVector = upVector * 10.0f;
	to = from - upVector;
	if (rbComp->GetRaycastHit(from, to)) {
		grounded = true;
		LMVector3 n = rbComp->GethasRaycastHitNormal(from, to);
		n.Normalize();
		//Limit Upwards if groundStep is too big
		if (n.Angle(tr->GetRotation().Up()) > 0.9f) grounded = false;
		//New Up Position based on Ground Normal
		tr->SetUpwards(n * 100.0f);
	}
	else
	{
		grounded = false;
		tr->SetUpwards(LMVector3(0, 1, 0));
	}
}

void EnemyAI::Activate()
{
	_shouldMove = true;
}