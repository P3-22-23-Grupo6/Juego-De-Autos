#include <iostream>

// Motor
#include "Transform.h"
#include "GameObject.h"
#include "RigidBodyComponent.h"
#include "InputManager.h"
#include "LMInputs.h"

// Componentes juego
#include "PlayerController.h"
#include "RaceManager.h"

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

	//gameObject->GetTransform()->SetPosition(LMVector3(30, 30, 30));
}


void PlayerController::InitComponent()
{

}

void PlayerController::Start()
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
	rbComp->useGravity(LMVector3(0, 0, 0)); // TODO:


	// RAYCAST
	//RigidBodyComponent* rbComp = GetComponent<RigidBodyComponent>();

	//rbComp->useGravity(LMVector3(0, 0, 0));


	LMVector3 from = gameObject->GetTransform()->GetPosition();
	LMVector3 to = from + LMVector3(0, -20, 0);

	LMVector3 upVector = gameObject->GetTransform()->GetRotation().Up();
	upVector.Normalize();
	double raycastDistance = 20;
	upVector = upVector * raycastDistance;
	to = from - upVector;

	if (rbComp->GetRaycastHit(from, to)) {
		LMVector3 n = rbComp->GethasRaycastHitNormal(from, to);

		// MOVIMIENTO CALCULADO CON MATES :TODO
		// if (!physicsBasedMovement) {
			//Intensidad con la que se va a actualizar el vector normal del coche
		float pitchIntensity = 40;
		LMVector3 newUp = n * pitchIntensity;
		gameObject->GetTransform()->SetUpwards(newUp);

		LMVector3 hitPos = rbComp->GetraycastHitPoint(from, to);
		double hoverDist = 7;
		LMVector3 hoverDisplacement = LMVector3(n.GetX() * hoverDist, n.GetY() * hoverDist, n.GetZ() * hoverDist);
		gameObject->GetTransform()->SetPosition(hitPos + hoverDisplacement);
		// }
	}


	bool acelerate = inputMng->GetKey(LMKS_W);
	if (acelerate) {

		// MOVIMIENTO CON FISICAS :TODO
		// Para que funcione, la gravedad tiene que estar activada y el objeto tener una masa distinta de 0

		rbComp->addForce(gameObject->GetTransform()->GetRotation().Forward() * 40 * dt);

	}

	//_rigidBody->AddForce(LMVector3(0, 0, 1));
	//SetPosition(LMVector3(100, 10, 10));
	//_node->Translate(0, 0, 1);

// Desacelerar la velocidad actual para que no haya tanto derrape

		//LMVector3 localVel = BulletToLm(rbComp->getBody()->getLinearVelocity());
	LMVector3 localVel = rbComp->GetLinearVelocity();

	LMVector3 forward = gameObject->GetTransform()->GetRotation().Forward();
	double angle = localVel.Angle(forward);

	double intensity = localVel.Magnitude();

	localVel.Normalize();
	LMVector3 invertedVelocity = localVel * -1;

	// Si el angulo entre la velocidad real del coche y la direccion en la que esta mirando es grande
	if (angle > .5f)
		rbComp->addForce(invertedVelocity * intensity / 20 * angle * dt);

	//std::cout << "\n" << "LOCAL VEL = " << localVel.GetX()
	//	<< ", " << localVel.GetY() << ", " << localVel.GetZ() << "\n";



	bool rotateRight = inputMng->GetKey(LMKS_D);
	float torqueStrengh = 5.f;
	if (rotateRight) {
		// TODO: quitar la referencia directa a btvector3 abajo tambien
		rbComp->ApplyTorqueImpulse(gameObject->GetTransform()->GetRotation().Up() * -torqueStrengh);
		//rbComp->getBody()->applyTorqueImpulse(btVector3(gameObject->GetTransform()->GetRotation().Up().GetX(), gameObject->GetTransform()->GetRotation().Up().GetY(), gameObject->GetTransform()->GetRotation().Up().GetZ()) * -torqueStrengh);
	}
	bool rotateLeft = inputMng->GetKey(LMKS_A);
	if (rotateLeft) {

		rbComp->ApplyTorqueImpulse(gameObject->GetTransform()->GetRotation().Up() * torqueStrengh);
	}

	//// std::cout << gameObject->GetTransform()->GetRotation().GetY() << std::endl;
	////rbComp->getBody()->applyTorqueImpulse(btVector3(0, 0, rbComp->getBody()->getTotalTorque().getZ()));
	////rbComp->FreezeRotation(LMVector3(1, 1, 0));

	// Comprobacion para que no gire demasiado rapido
	//if (rbComp->getBody()->getTotalTorque().length() > 10)
	//	rbComp->getBody()->applyTorqueImpulse(rbComp->getBody()->getTotalTorque() * -0.2f);

	//LMVector3 currentAngularVelocity = rbComp->Angul
	//std::cout << "\n" << "TURN VEL = " << currentAngularVelocity.GetX()
	//	<< ", " << currentAngularVelocity.GetY() << ", " << currentAngularVelocity.GetZ() << "\n";

	////if (!rotateLeft && !rotateRight)
	////	rbComp->getBody()->setAngularVelocity(LmToBullet(LMVector3(0, 0, 0)));

	//// Clampear la velocidad angular maxima permitida
	//float maxAngularVelocity = 3.5;
	//if (currentAngularVelocity.Magnitude() > maxAngularVelocity) {
	//	currentAngularVelocity.Normalize();
	//	// Conocer la direccion en la que se esta rotando (izquierda/derecha)
	//	double yAngVel = currentAngularVelocity.GetY();
	//	int direction = abs(yAngVel) / yAngVel;
	//	// Modificar el vector de la velocidad angular actual
	//	currentAngularVelocity = LMVector3(0, maxAngularVelocity * direction, 0);
	//}
	//// Añadir un drag angular para frenar la rotacion mas controladamente
	//double angularDrag = .7;
	//if (!rotateLeft && !rotateRight)
	//	currentAngularVelocity = LMVector3(currentAngularVelocity.GetX() * angularDrag,
	//		currentAngularVelocity.GetY() * angularDrag,
	//		currentAngularVelocity.GetZ() * angularDrag);

	//// Actualizar velocidad angular
	//rbComp->getBody()->setAngularVelocity(LmToBullet(currentAngularVelocity));

	//btScalar i = 0;
	//rbComp->getBody()->setFriction(i);

		// MOVIMIENTO CALCULADO CON MATES :TODO





	// Actualizar las posiciones del raceManager
	LMVector3 pos = gameObject->GetTransform()->GetPosition();
	raceManager->UpdateCarPosition("player", pos.GetX(), pos.GetY(), pos.GetZ());
}