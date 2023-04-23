#include "PlayerController.h"
#include "GameObject.h"
#include "Transform.h"
#include "RaceManager.h"
#include <iostream>

#include "RigidBodyComponent.h"
#include "InputManager.h"
#include "LMInputs.h"

//std::string PlayerController::name = "PlayerController";

PlayerController::PlayerController()
{

}

PlayerController::~PlayerController()
{
}

void PlayerController::Init(std::vector<std::pair<std::string, std::string>>& params)
{
	std::cout << "PLayer Controller I am \n\n\n\n\n";

	gameObject->GetTransform()->SetPosition(LMVector3(30, 30, 30));
}


void PlayerController::InitComponent()
{
	// Referencias al componente rigidbody y al singleton InputManager
	rbComp = gameObject->GetComponent<LocoMotor::RigidBodyComponent>();

	inputMng = LocoMotor::InputManager::GetInstance();
	raceManager = RaceManager::GetInstance();

}

void PlayerController::Update(float dt)
{
	// Como queremos que el coche se pege a las paredes y se ajuste a la normal
	// del suelo en cada momento, no utilizaremos la gravedad, pero si el resto de fisicas
	//rbComp->useGravity(LMVector3(0, 0, 0)); // TODO:


	// RAYCAST

	//RigidBodyComponent* rbComp = gameObject->GetComponent<RigidBodyComponent>();

	//rbComp->useGravity(LMVector3(0, 0, 0));

	////// Se inicializan los valores necesarios para el uso de un Raycast
	//LMVector3 from = gameObject->GetTransform()->GetPosition();
	//LMVector3 to = from + LMVector3(0, -20, 0);

	//LMVector3 upVector = gameObject->GetTransform()->GetRotation().Up();
	//upVector.Normalize();
	//double raycastDistance = 20;
	//upVector = upVector * raycastDistance;
	//to = from - upVector;

	//if (rbComp->GetRaycastHit(from, to)) {
	//	LMVector3 n = rbComp->GethasRaycastHitNormal(from, to);

	//	// MOVIMIENTO CALCULADO CON MATES :TODO
	//	// if (!physicsBasedMovement) {
	//		//Intensidad con la que se va a actualizar el vector normal del coche
	//	float pitchIntensity = 40;
	//	LMVector3 newUp = n * pitchIntensity;
	//	gameObject->GetTransform()->SetUpwards(newUp);

	//	LMVector3 hitPos = rbComp->GetraycastHitPoint(from, to);
	//	double hoverDist = 7;
	//	LMVector3 hoverDisplacement = LMVector3(n.GetX() * hoverDist, n.GetY() * hoverDist, n.GetZ() * hoverDist);
	//	gameObject->GetTransform()->SetPosition(hitPos + hoverDisplacement);
	//	// }
	//}
	//else {
	//	//// Si no detecta suelo, que se caiga
	//	//if (!physicsBasedMovement)
	//	//	localVelocity = localVelocity + LMVector3(0, -.2f, 0);
	//}



	//bool acelerate = inputMng->GetKey(LMKS_W);
	//if (true) {

	//	// MOVIMIENTO CON FISICAS :TODO
	//	// Para que funcione, la gravedad tiene que estar activada y el objeto tener una masa distinta de 0
	//	//gameObject->GetComponent<RigidBodyComponent>()->addForce(gameObject->GetTransform()->GetRotation().Forward() * 40 * dt);
	//	gameObject->GetComponent<RigidBodyComponent>()->addForce(LMVector3(5, 5, 5));
	//}




	// Actualizar las posiciones del raceManager
	LMVector3 pos = gameObject->GetTransform()->GetPosition();
	raceManager->UpdateCarPosition("player", pos.GetX(), pos.GetY(), pos.GetZ());
}