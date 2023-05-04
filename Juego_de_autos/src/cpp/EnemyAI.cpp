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
}

void JuegoDeAutos::EnemyAI::Start()
{
	mySpline = RaceManager::GetInstance()->GetSpline();
	rbComp = gameObject->GetComponent<RigidBody>();
	rbComp->UseGravity(LMVector3(0, 0, 0));

	LMVector3 from = gameObject->GetTransform()->GetPosition();
	LMVector3 to;
	if (rbComp->GetRaycastHit(from, to)) {

		LMVector3 n = rbComp->GethasRaycastHitNormal(from, to);
		n.Normalize();

		// Si hay mucha diferencia entre los vectores UP del suelo y la nave
		// Ignorarlo, esto bloquea el subirse a las paredes
		float angle = n.Angle(gameObject->GetTransform()->GetRotation().Up());
		if (angle > 0.9f)
			return;

		//Intensidad con la que se va a actualizar el vector normal del coche
		float pitchIntensity = 1000;
		LMVector3 newUp = n * pitchIntensity;
		gameObject->GetTransform()->SetUpwards(newUp);

		//LMVector3 hitPos = rbComp->GetraycastHitPoint(from, to);
		//double hoverDist = 12; // 7
		//LMVector3 hoverDisplacement = LMVector3(n.GetX() * hoverDist, n.GetY() * hoverDist, n.GetZ() * hoverDist);
		//gameObject->GetTransform()->SetPosition(hitPos + hoverDisplacement + (mySpline->Interpolate(timeStep) - gameObject->GetTransform()->GetPosition()) * 0.2f);
	}

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
	timeStep += enemySpeed * dt/1000.0f;
	if (timeStep > 1) {
		timeStep = 0.0f;
	}
	// Definir el punto inicial y la direccion del raycast
	LMVector3 from = gameObject->GetTransform()->GetPosition();
	LMVector3 to;

	LMVector3 upVector = gameObject->GetTransform()->GetRotation().Up();
	upVector.Normalize();
	double raycastDistance = 40;
	upVector = upVector * raycastDistance;
	to = from - upVector;

	gameObject->SetPosition(mySpline->Interpolate(timeStep));
	//rbComp->AddForce(mySpline->Interpolate(timeStep));
	//gameObject->GetTransform()->SetPosition(gameObject->GetTransform()->GetPosition() + 
	//										(mySpline->Interpolate(timeStep) - gameObject->GetTransform()->GetPosition()) * 0.2f);
	//LMVector3 newPos = mySpline->Interpolate(timeStep) ;
	//gameObject->GetTransform()->SetPosition(newPos);

	if (rbComp->GetRaycastHit(from, to)) {
		
		LMVector3 n = rbComp->GethasRaycastHitNormal(from, to);
		n.Normalize();
	
		// Si hay mucha diferencia entre los vectores UP del suelo y la nave
		// Ignorarlo, esto bloquea el subirse a las paredes
		float angle = n.Angle(gameObject->GetTransform()->GetRotation().Up());
		if (angle > 0.9f)
			return;
		
		//Intensidad con la que se va a actualizar el vector normal del coche
		float pitchIntensity = 1000;
		LMVector3 newUp = n * pitchIntensity;
		gameObject->GetTransform()->SetUpwards(newUp);
	
		//LMVector3 hitPos = rbComp->GetraycastHitPoint(from, to);
		//double hoverDist = 12; // 7
		//LMVector3 hoverDisplacement = LMVector3(n.GetX() * hoverDist, n.GetY() * hoverDist, n.GetZ() * hoverDist);
		//gameObject->GetTransform()->SetPosition(hitPos + hoverDisplacement + (mySpline->Interpolate(timeStep) - gameObject->GetTransform()->GetPosition()) * 0.2f);
	}

	//newPos = newPos + gameObject->GetTransform()->GetRotation().Right() * startSeparation;
	////LookAt
	gameObject->GetTransform()->LookAt(mySpline->Interpolate(timeStep + 0.005f));
	////Set Position
	//double hoverDist = 12; // 7
	//LMVector3 hoverDisplacement = LMVector3(n.GetX() * hoverDist, n.GetY() * hoverDist, n.GetZ() * hoverDist);
}
