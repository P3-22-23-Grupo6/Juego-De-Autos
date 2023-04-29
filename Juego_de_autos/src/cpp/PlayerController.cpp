#include <iostream>

// Motor
#include "Transform.h"
#include "GameObject.h"
#include "Scene.h"
#include "RigidBodyComponent.h"
#include "MeshRenderer.h"
#include "InputManager.h"
#include "LMInputs.h"
#include "UITextLM.h"

// Componentes juego
#include "PlayerController.h"
#include "RaceManager.h"
#include <AudioSource.h>

using namespace JuegoDeAutos;
using namespace LocoMotor;
//std::string PlayerController::name = "PlayerController";

PlayerController::PlayerController()
{

}

PlayerController::~PlayerController()
{
}

void PlayerController::InitComponent()
{

}

void PlayerController::Start()
{
	// Asignacion de referencias
	rbComp = gameObject->GetComponent<LocoMotor::RigidBodyComponent>();

	inputMng = LocoMotor::InputManager::GetInstance();
	raceManager = RaceManager::GetInstance();

	velocityText = gameObject->GetScene()->GetObjectByName("velocityText")->GetComponent<UITextLM>();


	// Como queremos que el coche se pege a las paredes y se ajuste a la normal
	// del suelo en cada momento, no utilizaremos la gravedad, pero si el resto de fisicas
	rbComp->useGravity(LMVector3(0, 0, 0)); // TODO:
}

void PlayerController::Update(float dt)
{
	// Lanza un raycast hacia el suelo y actualiza el vector UP del transform del coche
	// Con el proposito de seguir la carretera aunque sea una pared o un techo
	UpdateUpDirection();

	MoveShip(dt);

	TurnShip(dt);

	//LMVector3 p = gameObject->GetTransform()->GetPosition();
	//std::cout << "PLAYER POS = (" << p.GetX() 
	//					  << ", " << p.GetY() 
	//					  << ", " << p.GetZ() 
	//					  << ")" << std::endl;
}

// Gestionar orientacion

void PlayerController::UpdateUpDirection()
{
	// Definir el punto inicial y la direccion del raycast
	LMVector3 from = gameObject->GetTransform()->GetPosition();
	LMVector3 to;

	LMVector3 upVector = gameObject->GetTransform()->GetRotation().Up();
	upVector.Normalize();
	double raycastDistance = 20;
	upVector = upVector * raycastDistance;
	to = from - upVector;

	if (rbComp->GetRaycastHit(from, to)) {
		rbComp->useGravity(LMVector3(0, 0, 0)); // TODO:
		LMVector3 n = rbComp->GethasRaycastHitNormal(from, to);

		//Intensidad con la que se va a actualizar el vector normal del coche
		float pitchIntensity = 40;
		LMVector3 newUp = n * pitchIntensity;
		gameObject->GetTransform()->SetUpwards(newUp);

		LMVector3 hitPos = rbComp->GetraycastHitPoint(from, to);
		double hoverDist = 7;
		LMVector3 hoverDisplacement = LMVector3(n.GetX() * hoverDist, n.GetY() * hoverDist, n.GetZ() * hoverDist);
		gameObject->GetTransform()->SetPosition(hitPos + hoverDisplacement);
	}
	else rbComp->useGravity(LMVector3(0, -700, 0)); // TODO:
}

// Gestionar movimiento linear/angular

void PlayerController::MoveShip(float dt)
{
	// Almacenar valores de input
	accelerate = inputMng->GetKey(LMKS_W)
		|| inputMng->GetButton(LMC_A)
		|| inputMng->GetButton(LMC_RIGHTSHOULDER);
	// Aplicar fuerzas
	ApplyLinearForces(accelerate, dt);

	// Desaceleracion controlada
	LinearDrag(dt);

	// Mantener la UI actualizada
	UpdateVelocityUI();
}

void PlayerController::TurnShip(float dt)
{
	// Almacenar valores de input
	bool turnRight = inputMng->GetKey(LMKS_D);
	bool turnLeft = inputMng->GetKey(LMKS_A);

	double joystickValue;
	joystickValue = inputMng->GetJoystickValue(0, InputManager::Horizontal);

	bool turning = !turnLeft && !turnRight && abs(joystickValue) < joystickDeadzone;

	// Aplicar fuerzas
	ApplyAngularForces(turnLeft, turnRight, joystickValue, dt);


	// Compensar la perdida de velocidad de la nave en los giros, solo si se quiere acelerar la nave
	if (accelerate)
		ApplyExtraAcceleration(dt);


	// Definir variables necesarios para los calculos de las rotaciones
	LMVector3 currentAngularVelocity = rbComp->GetAngularVelocity();
	// Conocer la direccion en la que se esta rotando (izquierda/derecha)
	double yAngVel = currentAngularVelocity.GetY();
	int direction = abs(yAngVel) / yAngVel; // -1 : izquierda // 1 : derecha


	// Aplicar el drag angular si no se esta intentando rotar el coche
	if (turning)
		AngularDrag(currentAngularVelocity, direction);


	// Inclinar el meshRenderer de la nave para darle mejor sensacion al jugar
	TiltShip(currentAngularVelocity.Magnitude(), direction);
}

// Aplicar fuerzas

void PlayerController::ApplyLinearForces(bool accelerate, float dt)
{
	//std::cout << "linearDragIntensity = " << linearDragIntensity << "endl";

	if (accelerate)
		rbComp->addForce(gameObject->GetTransform()->GetRotation().Forward() * acceleration * dt);
}

void PlayerController::ApplyAngularForces(bool turnLeft, bool turnRight, float joystickValue, float dt)
{
	if (turnRight)
		// TODO: quitar la referencia directa a btvector3 abajo tambien
		rbComp->ApplyTorqueImpulse(gameObject->GetTransform()->GetRotation().Up() * -angularForce);
	//rbComp->getBody()->applyTorqueImpulse(btVector3(gameObject->GetTransform()->GetRotation().Up().GetX(), gameObject->GetTransform()->GetRotation().Up().GetY(), gameObject->GetTransform()->GetRotation().Up().GetZ()) * -torqueStrengh);

	if (turnLeft)
		rbComp->ApplyTorqueImpulse(gameObject->GetTransform()->GetRotation().Up() * angularForce);


	joystickValue *= .5f;
	// Giro con joystick
	if (abs(joystickValue) >= joystickDeadzone)
		rbComp->ApplyTorqueImpulse(gameObject->GetTransform()->GetRotation().Up() * angularForce * -joystickValue);
}

void JuegoDeAutos::PlayerController::ApplyExtraAcceleration(float dt)
{
	// Compensar la perdida de velocidad de un giro aumentando la aceleracion
	// Solo si se intenta acelerar

	LMVector3 currentAngularVelocity = rbComp->GetAngularVelocity();
	// Conocer la direccion en la que se esta rotando (izquierda/derecha)
	double yAngVel = currentAngularVelocity.GetY();
	int direction = abs(yAngVel) / yAngVel; // -1 : izquierda // 1 : derecha

	float angularIntensity = currentAngularVelocity.Magnitude() * extraAceleration;

	std::cout << "angularIntensity = " << angularIntensity;

	rbComp->addForce(gameObject->GetTransform()->GetRotation().Forward() * angularIntensity * dt);
}

// Aplicar Drag

void PlayerController::LinearDrag(float dt)
{
	// Desacelerar la velocidad actual para que no haya tanto derrape
	//LMVector3 localVel = BulletToLm(rbComp->getBody()->getLinearVelocity());
	LMVector3 localVel = rbComp->GetLinearVelocity();

	LMVector3 forward = gameObject->GetTransform()->GetRotation().Forward();
	float angle = localVel.Angle(forward);
	float intensity = (localVel.Magnitude() * linearDragForce) / 20;
	linearDragIntensity = intensity;
	localVel.Normalize();
	LMVector3 invertedVelocity = localVel * -1;

	// Si el angulo entre la velocidad real del coche y la direccion en la que esta mirando es grande
	// Aplicar una fuerza inversa a la velocidad actual para controlar el derrape
	if (angle > .01f)
		rbComp->addForce(invertedVelocity * intensity * angle * dt);
}

void PlayerController::AngularDrag(LMVector3 currentAngularVelocity, int direction)
{
	// Limitar la velocidad angular maxima
	if (currentAngularVelocity.Magnitude() > maxAngularVelocity) {
		currentAngularVelocity.Normalize();
		// Modificar el vector de la velocidad angular actual
		currentAngularVelocity = LMVector3(0, maxAngularVelocity * direction, 0);
	}

	// Añadir un drag angular para frenar la rotacion mas controladamente
	//double angularDrag = .7;
	currentAngularVelocity = LMVector3(currentAngularVelocity.GetX() * angularDragForce,
		currentAngularVelocity.GetY() * angularDragForce,
		currentAngularVelocity.GetZ() * angularDragForce);

	// Actualizar velocidad angular
	rbComp->SetAngularVelocity(currentAngularVelocity);
}

// Tilt

void PlayerController::TiltShip(float currentAngularVelocity, int direction)
{
	// Angulo maximo de la inclinacion visual del coche en grados
	double maxTiltAngle = 20;

	// Determina cuanto se inclina el coche, es un valor de 0 a 1
	double tiltAmount = currentAngularVelocity / maxAngularVelocity;

	// Rotar SOLO la parte grafica del coche para mejor sensacion de juego
	// Teniendo en cuenta la velocidad angular
	gameObject->GetComponent<MeshRenderer>()->
		Rotate(LMVector3(0, 0, tiltAmount * maxTiltAngle * direction));

	// Actualizar las posiciones del raceManager
	LMVector3 pos = gameObject->GetTransform()->GetPosition();
	raceManager->UpdateCarPosition("Player", pos);
}

// UI

void PlayerController::UpdateVelocityUI()
{
	// Para mostrar la velocidad se redondea la magnitud 
	// del vector de velocidad y se actualiza el texto
	int velocityClean = round(rbComp->GetLinearVelocity().Magnitude());
	velocityText->ChangeText(std::to_string(velocityClean) + " KM / H");

	// Se utiliza para saber el tono de rojo del texto segun la velocidad actual
	double highVelocityIndicator = 700;
	double colorIntensity = ((double)velocityClean) / highVelocityIndicator;
	if (colorIntensity > 1) colorIntensity = 1;
	double inverseColor = 1 - colorIntensity;
	velocityText->SetTopColor(1, inverseColor, inverseColor);
	velocityText->SetBottomColor(1, inverseColor, inverseColor);

	gameObject->GetComponent<AudioSource>()->SetFreq((velocityClean / 300.f) + 0.9f);
}