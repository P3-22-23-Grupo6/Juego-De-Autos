#include "Projectile.h"

// Componentes motor
#include "RigidBody.h"
#include "GameObject.h"
#include "Transform.h"
#include "LMSpline.h"
#include "Scene.h"

// Componentes juego
#include "RaceManager.h"
#include "EnemyAI.h"

#include <iostream>

using namespace LocoMotor;
using namespace JuegoDeAutos;

Projectile::Projectile()
{
	raceManager = nullptr;
	rbComp = nullptr;
	projectileSpeed = 0.02;
	timeStep = 0;
	totalNumbCheckpoints = 0;
}

void Projectile::Init(std::vector<std::pair<std::string, std::string>>& params)
{
	for (int i = 0; i < params.size(); i++) {
		if (params[i].first == "thrust") {
			
		}
	}
}

void JuegoDeAutos::Projectile::Start()
{
	raceManager = RaceManager::GetInstance();
	if (raceManager == nullptr) {
		SetActive(false);
		return;
	}
	rbComp = gameObject->GetComponent<LocoMotor::RigidBody>();
	rbComp->UseGravity(LMVector3(0, 0, 0));
	spline = raceManager->GetSpline();
	totalNumbCheckpoints = raceManager->GetTotalNumberOfCheckpoints();
	initialPos = gameObject->GetTransform()->GetPosition();
	SetActive(false);
}

void Projectile::Update(float dt)
{
	timeStep += projectileSpeed * dt / 1000.0f;
	if (timeStep > 1) {
		timeStep = 0.0f;
	}
	//std::cout << timeStep << "\n";
	if (IsCloseToEnemy())FollowEnemyCar(dt);
	else FollowSpline(dt);
}

void JuegoDeAutos::Projectile::OnEnable()
{
	/*if (gameObject->GetScene()->GetObjectByName("coche") != nullptr) {
		gameObject->SetPosition(gameObject->GetScene()->GetObjectByName("coche")->GetTransform()->GetPosition());
	}*/
	if (raceManager == nullptr) {
		SetActive(false);
		return;
	}
	int lastPlayerCheckpoint = raceManager->GetPlayerLastCheckpointIndex();
	timeStep = (float)(lastPlayerCheckpoint - 2) / totalNumbCheckpoints;
	if (timeStep > 1 || timeStep < 0) {
		timeStep = 0.0f;
	}
}

void JuegoDeAutos::Projectile::OnDisable()
{
	gameObject->SetPosition(initialPos);
}

void Projectile::OnCollisionEnter(GameObject* other)
{
	if (gameObject->GetComponent<EnemyAI>() != nullptr) {
		std::cout << "Choque enemigo\n";
		SetActive(false);
	}
}

void JuegoDeAutos::Projectile::FollowSpline(float dt)
{
	std::cout << "Siguiendo carretera\n";
	LMVector3 from = gameObject->GetTransform()->GetPosition();
	LMVector3 to;

	LMVector3 upVector = gameObject->GetTransform()->GetRotation().Up();
	upVector.Normalize();
	double raycastDistance = 80;
	upVector = upVector * raycastDistance;
	to = from - upVector;

	gameObject->SetPosition(spline->Interpolate(timeStep));

	if (rbComp->GetRaycastHit(from, to)) {

		LMVector3 n = rbComp->GethasRaycastHitNormal(from, to);
		n.Normalize();
		//Intensidad con la que se va a actualizar el vector normal del coche
		float pitchIntensity = 40;
		LMVector3 newUp = n * pitchIntensity;
		gameObject->GetTransform()->SetUpwards(newUp);
	}
	else gameObject->GetTransform()->SetUpwards(LMVector3(0, 1, 0));
}

void JuegoDeAutos::Projectile::FollowEnemyCar(float dt)
{
	std::cout << "Siguiendo coche\n";
	LMVector3 pos = gameObject->GetTransform()->GetPosition();
	LMVector3 to;

	LMVector3 upVector = gameObject->GetTransform()->GetRotation().Up();
	upVector.Normalize();
	double raycastDistance = 80;
	upVector = upVector * raycastDistance;
	to = pos - upVector;

	//LMVector3 forw = gameObject->GetTransform()->GetRotation().Forward();
	//forw.Normalize();
	LMVector3 dir = raceManager->GetFirstEnemyPos() - gameObject->GetTransform()->GetPosition();
	dir.Normalize();
	gameObject->SetPosition(pos + dir * dt * .6f);

	if (rbComp->GetRaycastHit(pos, to)) {

		LMVector3 n = rbComp->GethasRaycastHitNormal(pos, to);
		n.Normalize();
		//Intensidad con la que se va a actualizar el vector normal del coche
		float pitchIntensity = 40;
		LMVector3 newUp = n * pitchIntensity;
		gameObject->GetTransform()->SetUpwards(newUp);
	}
	else gameObject->GetTransform()->SetUpwards(LMVector3(0, 1, 0));
}

bool Projectile::IsCloseToEnemy() 
{
	float minRange = 100;
	return (raceManager->GetFirstEnemyPos() - gameObject->GetTransform()->GetPosition()).Magnitude() < minRange;
}
