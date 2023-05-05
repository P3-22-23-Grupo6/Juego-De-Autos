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
	_shouldMove = false;
}

void JuegoDeAutos::EnemyAI::Start()
{
	RaceManager* rmngr = RaceManager::GetInstance();
	rbComp = gameObject->GetComponent<RigidBody>();
	if (rmngr == nullptr || rbComp == nullptr) {
		SetActive(false);
		return;
	}
	mySpline = rmngr->GetSpline();
	rbComp->UseGravity(LMVector3(0, 0, 0));
	enemySpeed = rmngr->GetSpeed() * 0.00004f;

	LMVector3 from = gameObject->GetTransform()->GetPosition();
	LMVector3 to;
	if (rbComp->GetRaycastHit(from, to)) {

		LMVector3 n = rbComp->GethasRaycastHitNormal(from, to);
		n.Normalize();

		// Si hay mucha diferencia entre los vectores UP del suelo y la nave
		// Ignorarlo, esto bloquea el subirse a las paredes
		float angle = n.Angle(gameObject->GetTransform()->GetRotation().Up());

		//Intensidad con la que se va a actualizar el vector normal del coche
		float pitchIntensity = 1000;
		LMVector3 newUp = n * pitchIntensity;
		gameObject->GetTransform()->SetUpwards(newUp);

	}
	enemySpeed += std::rand() % 80 * 0.0001f;
	MoveEnemy();
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

void EnemyAI::InitComponent() {

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
	MoveEnemy();
	
}
void EnemyAI::MoveEnemy()
{
	// Definir el punto inicial y la direccion del raycast
	LMVector3 from = gameObject->GetTransform()->GetPosition();
	LMVector3 to;

	LMVector3 upVector = gameObject->GetTransform()->GetRotation().Up();
	upVector.Normalize();
	double raycastDistance = 40;
	upVector = upVector * raycastDistance;
	to = from - upVector;

	gameObject->SetPosition(mySpline->Interpolate(timeStep) + gameObject->GetTransform()->GetRotation().Right() * startSeparation);

	if (rbComp->GetRaycastHit(from, to)) {

		LMVector3 n = rbComp->GethasRaycastHitNormal(from, to);
		n.Normalize();
		//Intensidad con la que se va a actualizar el vector normal del coche
		float pitchIntensity = 1000;
		LMVector3 newUp = n * pitchIntensity;
		gameObject->GetTransform()->SetUpwards(newUp);
	}
	else gameObject->GetTransform()->SetUpwards(LMVector3(0, 1, 0));
	////LookAt
	gameObject->GetTransform()->LookAt(mySpline->Interpolate(timeStep + 0.005f) + gameObject->GetTransform()->GetRotation().Right() * startSeparation);
}

void EnemyAI::Activate()
{
	_shouldMove = true;
}