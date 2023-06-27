#include "Projectile.h"

// Componentes motor
#include "RigidBody.h"
#include "GameObject.h"
#include "Transform.h"
#include "LMSpline.h"
#include "Scene.h"

// Componentes juego
#include "RaceManager.h"

using namespace LocoMotor;
using namespace JuegoDeAutos;

Projectile::Projectile()
{
	raceManager = nullptr;
	rbComp = nullptr;
	spline = nullptr;
	projectileSpeed = 0;
	timeStep = 0;
	totalNumbCheckpoints = 0;
}

void Projectile::Init(std::vector<std::pair<std::string, std::string>>& params)
{
	for (int i = 0; i < params.size(); i++) {
		if (params[i].first == "speed") {
			projectileSpeed = std::stof(params[i].second);
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
	
	if (IsInChaseRange()) {
		FollowEnemyCar(dt);
		if (IsInImpactRange()) {
			raceManager->StunFirstEnemyCar();
			SetActive(false);
		}
	}
	else FollowSpline(dt);
}

void JuegoDeAutos::Projectile::OnEnable()
{
	if (gameObject->GetScene()->GetObjectByName("coche") != nullptr) {
		// Moves the projectile to the player car position
		gameObject->SetPosition(gameObject->GetScene()->GetObjectByName("coche")->GetTransform()->GetPosition());
	}
	if (raceManager == nullptr) {
		SetActive(false);
		return;
	}
	// Calculates the current position of the player in the spline,
	// so the projectile can follow the spline from that position.
	int lastPlayerCheckpoint = raceManager->GetPlayerLastCheckpointIndex();
	timeStep = (float)(lastPlayerCheckpoint - 2) / totalNumbCheckpoints;
	if (timeStep > 1 || timeStep < 0) {
		timeStep = 0.0f;
	}
}

void JuegoDeAutos::Projectile::OnDisable()
{
	// Hides the projectile and remains inactive until a new usage
	gameObject->SetPosition(initialPos);
}


void JuegoDeAutos::Projectile::FollowSpline(float dt)
{
	LMVector3 from = gameObject->GetTransform()->GetPosition();
	LMVector3 to;

	LMVector3 upVector = gameObject->GetTransform()->GetRotation().Up();
	upVector.Normalize();
	double raycastDistance = 80;
	upVector = upVector * raycastDistance;
	to = from - upVector;

	// Follow the spline
	gameObject->SetPosition(spline->Interpolate(timeStep));

	if (rbComp->GetRaycastHit(from, to)) {

		LMVector3 n = rbComp->GethasRaycastHitNormal(from, to);
		n.Normalize();
		float pitchIntensity = 40;
		LMVector3 newUp = n * pitchIntensity;
		gameObject->GetTransform()->SetUpwards(newUp);
	}
	else gameObject->GetTransform()->SetUpwards(LMVector3(0, 1, 0));
}

void JuegoDeAutos::Projectile::FollowEnemyCar(float dt)
{
	LMVector3 pos = gameObject->GetTransform()->GetPosition();
	LMVector3 to;

	LMVector3 upVector = gameObject->GetTransform()->GetRotation().Up();
	upVector.Normalize();
	double raycastDistance = 80;
	upVector = upVector * raycastDistance;
	to = pos - upVector;

	LMVector3 dir = raceManager->GetFirstEnemyPos() - gameObject->GetTransform()->GetPosition();
	dir.Normalize();
	// Moves the projectile towards the enemy car
	gameObject->SetPosition(pos + dir * dt * .6f);

	if (rbComp->GetRaycastHit(pos, to)) {

		LMVector3 n = rbComp->GethasRaycastHitNormal(pos, to);
		n.Normalize();
		float pitchIntensity = 40;
		LMVector3 newUp = n * pitchIntensity;
		gameObject->GetTransform()->SetUpwards(newUp);
	}
	else gameObject->GetTransform()->SetUpwards(LMVector3(0, 1, 0));
}

bool Projectile::IsInChaseRange() 
{
	float minRange = 200;
	return (raceManager->GetFirstEnemyPos() - gameObject->GetTransform()->GetPosition()).Magnitude() < minRange;
}

bool Projectile::IsInImpactRange()
{
	float minRange = 50;
	return (raceManager->GetFirstEnemyPos() - gameObject->GetTransform()->GetPosition()).Magnitude() < minRange;
}