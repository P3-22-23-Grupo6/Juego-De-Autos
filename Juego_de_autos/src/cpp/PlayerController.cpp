#include <iostream>

// Motor
#include "Transform.h"
#include "GameObject.h"
#include "Scene.h"
#include "RigidBody.h"
#include "MeshRenderer.h"
#include "InputManager.h"
#include "LMInputs.h"
#include "UITextLM.h"
#include "Camera.h"
#include "ScriptManager.h"

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
	rbComp = gameObject->GetComponent<LocoMotor::RigidBody>();

	rbComp->SetActivationState(LM_DISABLE_DEACTIVATION);

	inputMng = LocoMotor::InputManager::GetInstance();
	raceManager = RaceManager::GetInstance();

	cam = gameObject->GetScene()->GetCamera()->GetComponent<Camera>();

	velocityText = gameObject->GetScene()->GetObjectByName("velocityText")->GetComponent<UITextLM>();

	LMVector3 forw = gameObject->GetTransform()->GetRotation().Forward();
	rbComp->addForce(forw * 2000);

	UpdateUpDirection(0.02f);
}

void PlayerController::Update(float dt)
{
	if (inputMng->GetKey(LMKS_0))
	{
		ScriptManager::GetInstance()->LoadSceneFromFile("Assets/sc.lua");
		return;
	}

	// Lanza un raycast hacia el suelo y actualiza el vector UP del transform del coche
	// Con el proposito de seguir la carretera aunque sea una pared o un techo
	UpdateUpDirection(dt);

	// Comprobar si ya se puede mover el coche despues del countdown inicial
	//if (!raceManager->HasCountDownFinished())
	//	return;

	GetInput();

	//if (raceManager->HasCountDownFinished())
		MoveShip(dt);

	TurnShip(dt);

	CheckRespawn();
}


// Gestionar orientacion

void PlayerController::UpdateUpDirection(float dt)
{
	// Definir el punto inicial y la direccion del raycast
	LMVector3 from = gameObject->GetTransform()->GetPosition();
	LMVector3 to;

	LMVector3 upVector = gameObject->GetTransform()->GetRotation().Up();
	upVector.Normalize();
	double raycastDistance = 40;
	upVector = upVector * raycastDistance;
	to = from - upVector;

	if (rbComp->GetRaycastHit(from, to)) {
		inAir = false;
		rbComp->useGravity(LMVector3(0, 0, 0)); // TODO:
		LMVector3 n = rbComp->GethasRaycastHitNormal(from, to);
		n.Normalize();

		// Si hay mucha diferencia entre los vectores UP del suelo y la nave
		// Ignorarlo, esto bloquea el subirse a las paredes
		float angle = n.Angle(gameObject->GetTransform()->GetRotation().Up());
		if (angle > 0.5)
			return;
		//std::cout << "angle = " << angle << std::endl;

		//Intensidad con la que se va a actualizar el vector normal del coche
		float pitchIntensity = 60;
		LMVector3 newUp = n * pitchIntensity;
		gameObject->GetTransform()->SetUpwards(newUp);

		LMVector3 hitPos = rbComp->GetraycastHitPoint(from, to);
		double hoverDist = 12; // 7
		LMVector3 hoverDisplacement = LMVector3(n.GetX() * hoverDist, n.GetY() * hoverDist, n.GetZ() * hoverDist);
		gameObject->GetTransform()->SetPosition(hitPos + hoverDisplacement);
	}
	else//No se Detecta suelo, Caida
	{
		inAir = true;
		float autoRotIntensity = 300;
		rbComp->useGravity(LMVector3(0, gravityThrust, 0));
		gameObject->GetTransform()->SetUpwards(LMVector3(0, autoRotIntensity * dt / 1000, 0));
	}


	if (!inAirLastFrame && inAir)
		inputMng->RumbleController(.3, .2f);

	if (inAirLastFrame && !inAir)
		inputMng->RumbleController(1, .2f);

	inAirLastFrame = inAir;
}

void PlayerController::GetInput()
{

	// Almacenar valores de input
	accelerate = inputMng->GetKey(LMKS_W)
		|| inputMng->GetButton(LMC_A)
		|| inputMng->GetButton(LMC_RIGHTSHOULDER);

	reverseAccelerate= inputMng->GetKey(LMKS_S)
		|| inputMng->GetButton(LMC_B)
		|| inputMng->GetButton(LMC_LEFTSHOULDER);


	turnRight = inputMng->GetKey(LMKS_D);
	turnLeft = inputMng->GetKey(LMKS_A);

	joystickValue = inputMng->GetJoystickValue(0, InputManager::Horizontal);

	accTriggerValue = inputMng->GetTriggerValue(1);
	reverseAccTriggerValue = inputMng->GetTriggerValue(0);
	if (accTriggerValue > 0)accelerate = true;
	if (reverseAccTriggerValue > 0)reverseAccelerate = true;

	turning = (turnLeft || turnRight || abs(joystickValue) > joystickDeadzone);
}


// Gestionar movimiento linear/angular

void PlayerController::MoveShip(float dt)
{
	// Aplicar fuerzas
	ApplyLinearForces(dt);

	// Desaceleracion controlada
	LinearDrag(dt);

	// Mantener la UI actualizada
	UpdateVelocityUI();


	AdjustFov();
}

void PlayerController::TurnShip(float dt)
{

	// Aplicar fuerzas
	ApplyAngularForces(dt);

	if (!inAir) {
		float currentVel = rbComp->GetLinearVelocity().Magnitude();
		if (!reverseAccelerate) {
			LMVector3 forw = gameObject->GetTransform()->GetRotation().Forward();
			forw.Normalize();
			rbComp->SetLinearVelocity(forw * currentVel);
		}
	}


	// Definir variables necesarios para los calculos de las rotaciones
	LMVector3 currentAngularVelocity = rbComp->GetAngularVelocity();
	// Conocer la direccion en la que se esta rotando (izquierda/derecha)
	double yAngVel = gameObject->GetTransform()->GetRotation().Rotate(currentAngularVelocity).GetY();
	int direction = abs(yAngVel) / yAngVel; // -1 : izquierda // 1 : derecha


	LimitMaxAngleVelocity(currentAngularVelocity, direction);

	// Aplicar el drag angular si no se esta intentando rotar el coche
	if (!turning)
		AngularDrag(currentAngularVelocity, direction);


	// Inclinar el meshRenderer de la nave para darle mejor sensacion al jugar
	TiltShip(currentAngularVelocity.Magnitude(), direction);
}


// Aplicar fuerzas

void PlayerController::ApplyLinearForces(float dt)
{
	if (accelerate && reverseAccelerate)return;
	if (accelerate) {

		LMVector3 forw = gameObject->GetTransform()->GetRotation().Forward();
		forw.Normalize();

		if (physicsBasedMovement) {
			if (accTriggerValue > 0) rbComp->addForce(forw * acceleration * accTriggerValue);
			else rbComp->addForce(forw * acceleration);
		}
		else {
			LMVector3 pos = gameObject->GetTransform()->GetPosition();
			gameObject->GetTransform()->SetPosition(pos + forw * dt * .6f);
		}
	}
	else if (reverseAccelerate) {
		LMVector3 forw = gameObject->GetTransform()->GetRotation().Forward();
		forw.Normalize();

		if (physicsBasedMovement) {
			if (reverseAccTriggerValue > 0) rbComp->addForce(forw * reversingAcceleration * reverseAccTriggerValue);
			else rbComp->addForce(forw * reversingAcceleration);
		}
		else {
			LMVector3 pos = gameObject->GetTransform()->GetPosition();
			gameObject->GetTransform()->SetPosition(pos + forw * dt * .6f);
		}
	}
}

void PlayerController::ApplyAngularForces(float dt)
{
	// Activar desactivar Gyroscopio
	if (inputMng->GetButtonDown(LMC_DPAD_UP))
	{
		useGyro = !useGyro;
		if (useGyro)
			EnableGyro();
		else
			DisableGyro();
	}

	if (physicsBasedMovement) {
		if (turnRight)
			// TODO: quitar la referencia directa a btvector3 abajo tambien
			rbComp->ApplyTorqueImpulse(gameObject->GetTransform()->GetRotation().Up() * -angularForce * dt);
		//rbComp->getBody()->applyTorqueImpulse(btVector3(gameObject->GetTransform()->GetRotation().Up().GetX(), gameObject->GetTransform()->GetRotation().Up().GetY(), gameObject->GetTransform()->GetRotation().Up().GetZ()) * -torqueStrengh);

		if (turnLeft)
			rbComp->ApplyTorqueImpulse(gameObject->GetTransform()->GetRotation().Up() * angularForce * dt);


		// Si hay un mando conectado, saber si se va a usar el giroscopio o no
		// Usar el Gyroscopio
		if (useGyro) {
			gyroValue = inputMng->GetGyroscopeAngle(InputManager::Horizontal);
			// Adaptar el valor a la jugabilidad
			gyroValue *= 30;
			// Clampear el valor
			if (gyroValue > maxGyroValue)
				gyroValue = maxGyroValue;
			else if (gyroValue < -maxGyroValue)
				gyroValue = -maxGyroValue;

			rbComp->ApplyTorqueImpulse(gameObject->GetTransform()->GetRotation().Up() * angularForce * gyroValue * dt);
		}
		// Usar el Joystick
		else {
			joystickValue *= .5f;
			// Giro con joystick
			if (abs(joystickValue) >= joystickDeadzone)
				rbComp->ApplyTorqueImpulse(gameObject->GetTransform()->GetRotation().Up() * angularForce * -joystickValue * dt);
		}
	}

	else {

		if (turnRight) {
			float newRotationVelocity = currentRotationVelocity - rotationAcceleration;
			if (newRotationVelocity > -maxRotationVelocity)
				currentRotationVelocity -= rotationAcceleration;
		}

		else if (turnLeft) {
			float newRotationVelocity = currentRotationVelocity + rotationAcceleration;
			if (newRotationVelocity < maxRotationVelocity)
				currentRotationVelocity += rotationAcceleration;

		}

		else {
			if (currentRotationVelocity > 0.05)
				currentRotationVelocity -= rotationDecceleration;
			else if (currentRotationVelocity < -0.05)
				currentRotationVelocity += rotationDecceleration;
			else currentRotationVelocity = 0;
		}

		LMVector3 up = gameObject->GetTransform()->GetRotation().Up();
		LMQuaternion newRotation = gameObject->GetTransform()->GetRotation().Rotate(up, currentRotationVelocity * dt);
		gameObject->GetTransform()->SetRotation(newRotation);
	}

	//std::cout << "Rotation = ( " << r.GetX() << ", " << r.GetY() << ", " << r.GetZ() << ")" << std::endl;
}


// Aplicar Drag

void PlayerController::LinearDrag(float dt)
{
	// Desacelerar la velocidad actual para que no haya tanto derrape
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
		rbComp->addForce(invertedVelocity * intensity * angle);
}

void PlayerController::AngularDrag(LMVector3 currentAngularVelocity, int direction)
{
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
	double maxTiltAngle = 50;

	// Determina cuanto se inclina el coche, es un valor de 0 a 1
	double tiltAmount = currentAngularVelocity / maxAngularVelocity * 0.25f;

	// Rotar SOLO la parte grafica del coche para mejor sensacion de juego
	// Teniendo en cuenta la velocidad angular
	gameObject->GetComponent<MeshRenderer>()->
		Rotate(LMVector3(0, 0, tiltAmount * maxTiltAngle * direction));

	// Actualizar las posiciones del raceManager
	LMVector3 pos = gameObject->GetTransform()->GetPosition();
	if (raceManager != nullptr)
		raceManager->UpdateCarPosition("Player", pos);
}


// Metodos extra

void PlayerController::LimitMaxAngleVelocity(LMVector3 currentAngularVelocity, int direction)
{
	// Limitar la velocidad angular maxima
	if (abs(gameObject->GetTransform()->GetRotation().Rotate(currentAngularVelocity).GetY()) > maxAngularVelocity) {
		currentAngularVelocity.Normalize();
		// Modificar el vector de la velocidad angular actual
		currentAngularVelocity = currentAngularVelocity * maxAngularVelocity;
	}

	// Actualizar velocidad angular
	rbComp->SetAngularVelocity(currentAngularVelocity);
}

void PlayerController::AdjustFov()
{
	// Actualizar el fov
	LMVector3 localVel = rbComp->GetLinearVelocity();
	float fovOne = (localVel.Magnitude() / 600);
	if (fovOne > 1) fovOne = 1;
	float fov = fovOne * maxExtraFov + initialFov;
	cam->SetFOV(fov);
}

void JuegoDeAutos::PlayerController::CheckRespawn()
{
	// Si la nave se cae al agua, acceder al ultimo chekpoint
	if (gameObject->GetTransform()->GetPosition().GetY() < -900)
	{
		LMVector3 lastCheckpointPos = raceManager->GetPlayerLastCheckpointPosition();
		gameObject->GetTransform()->SetPosition(lastCheckpointPos);
		rbComp->SetLinearVelocity(LMVector3(0, 0, 0));
		rbComp->SetAngularVelocity(LMVector3(0, 0, 0));
	}
}


// UI

void PlayerController::UpdateVelocityUI()
{
	int velocityClean = round(rbComp->GetLinearVelocity().Magnitude());
	gameObject->GetComponent<AudioSource>()->SetFreq((velocityClean / 300.f) + 0.9f);

	// Para mostrar la velocidad se redondea la magnitud 
	// del vector de velocidad y se actualiza el texto
	if (velocityText == nullptr) return;
	velocityText->ChangeText(std::to_string(velocityClean / 6) + " KM / H");

	// Se utiliza para saber el tono de rojo del texto segun la velocidad actual
	double highVelocityIndicator = 1000;
	double colorIntensity = ((double)velocityClean) / highVelocityIndicator;
	if (colorIntensity > 1) colorIntensity = 1;
	double inverseColor = 1 - colorIntensity;

	LMVector3 color = LMVector3(1, inverseColor, inverseColor);
	velocityText->SetTopColor(color.GetX(), color.GetY(), color.GetZ());
	velocityText->SetBottomColor(color.GetX(), color.GetY() / 2, color.GetZ());

	inputMng->SetControllerLedColor(colorIntensity, 0, 0);
}

void JuegoDeAutos::PlayerController::EnableGyro()
{
	inputMng->ResetGyroscope();
	useGyro = true;
	inputMng->ActivateGyroscopeWhenConnected();
	inputMng->EnableControllerGyroscope();
	gyroValue = 0;
}

void JuegoDeAutos::PlayerController::DisableGyro()
{
	useGyro = false;
	inputMng->DisableControllerGyroscope();
	gyroValue = 0;
}

void JuegoDeAutos::PlayerController::SetAcceleration(float newAcceleration)
{
	acceleration = newAcceleration;
}
