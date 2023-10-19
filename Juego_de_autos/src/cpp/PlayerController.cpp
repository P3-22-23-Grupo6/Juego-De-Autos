#include <iostream>

// Motor
#include "Transform.h"
#include "GameObject.h"
#include "Scene.h"
#include "RigidBody.h"
#include "MeshRenderer.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "LMInputs.h"
#include "UITextLM.h"
#include "Camera.h"
#include "ScriptManager.h"

// Componentes juego
#include "PlayerController.h"
#include "RaceManager.h"
#include <AudioSource.h>
#include <AudioListener.h>

using namespace JuegoDeAutos;
using namespace LocoMotor;

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
	counter = 0.0f;
	// Asignacion de referencias
	tr = gameObject->GetTransform();
	rbComp = gameObject->GetComponent<LocoMotor::RigidBody>();
	if (rbComp == nullptr) {
		SetActive(false);
		return;
	}
	rbComp->SetActivationState(LM_DISABLE_DEACTIVATION);
	//DESACTIVAR GRAVEDAD FISICA PARA EL COCHE
	rbComp->UseGravity(LMVector3(0, 0, 0));

	inputMng = LocoMotor::InputManager::GetInstance();
	sceneMng = LocoMotor::SceneManager::GetInstance();
	acceleration = 50;// raceManager->GetSpeed();
	lastUpwardDir = LMVector3(0,1,0);
	//Create Billboard
	carBillboard = sceneMng->AddObjectRuntime("carBillboard");
	carBillboard->AddComponent("Transform");
	carBillboard->AddComponent("MeshRenderer");
	carBillboard->GetComponent<Transform>()->InitRuntime(LMVector3(0, 2, 0));
	carBillboard->GetComponent<MeshRenderer>()->InitRuntime("BillboardRacers.mesh");
	carBillboard->GetComponent<MeshRenderer>()->ChangeMaterial("m_Billboards");
	carBillboard->GetTransform()->Start();
	//Create Car Model Child
	carModel = sceneMng->AddObjectRuntime("playerCarModel");
	carModel->AddComponent("Transform");
	carModel->AddComponent("MeshRenderer");
	carModel->GetComponent<Transform>()->InitRuntime(LMVector3(0, 5, 0));
	carModel->GetComponent<MeshRenderer>()->InitRuntime("BlueFalcon.mesh");
	carModel->GetTransform()->Start();
	meshComp = carModel->GetComponent<LocoMotor::MeshRenderer>();

	tr->AddChild(carBillboard->GetTransform());
	tr->AddChild(carModel->GetTransform());

	if(gameObject->GetScene()->GetCamera()!=nullptr)
		cam = gameObject->GetScene()->GetCamera()->GetComponent<Camera>();

	//Velocity Text
	GameObject* vltxt = gameObject->GetScene()->GetObjectByName("velocityText");
	if (vltxt != nullptr && vltxt->GetComponent<UITextLM>() != nullptr) {
		velocityText = vltxt->GetComponent<UITextLM>();
	}
	forw = tr->GetRotation().Forward();
}

void PlayerController::Update(float dt)
{
	counter += dt;
	/*LMVector3 newPos;
	newPos = newPos.Lerp(carModel->GetTransform()->GetPosition(), 
		carModel->GetTransform()->GetPosition() + LMVector3(0, 0.1f + 0.2f * _CMATH_::sin(counter / 100.0f * 0.7f), 0),
		counter/100.0f *0.1f);

	carModel->GetTransform()->SetPosition(newPos);*/
	//Set Forward Vector
	forw = tr->GetRotation().Forward();
	forw.Normalize();
	//Set Upward Vector
	SetUpwards(dt);

	GetInput();

	MoveShip(dt);

	TurnShip(dt);
	// 
	//// Actualizar las posiciones del raceManager
	//if (raceManager != nullptr)
	//{
	//	raceManager->UpdateCarPosition("Player", tr->GetPosition());
	//	CheckRespawn();
	//}
}


// Gestionar orientacion

void PlayerController::SetUpwards(float dt)
{
	LMVector3 newUpDirection;
	// Definir el punto inicial y la direccion del raycast
	LMVector3 from = tr->GetPosition();
	LMVector3 to;
	LMVector3 upVector = tr->GetRotation().Up();
	upVector.Normalize();
	to = to * raycastDistance;
	to = from - upVector;

	//Grounded
	if (rbComp->GetRaycastHit(from, to)) {
		inAir = false;
		//Get Surface below Normal Vector
		LMVector3 n = rbComp->GethasRaycastHitNormal(from, to);
		n.Normalize();

		// Angle difference threshold
		if (n.Angle(upVector) > angleThreshold) newUpDirection = lastUpwardDir;
		else newUpDirection = n;
		//LMVector3 hitPos = rbComp->GetraycastHitPoint(from, to);
		//tr->SetPosition(hitPos + n * raycastDistance);
	}
	//Not Grounded
	else
	{
		inAir = true;
		float autoRotIntensity = 30;
		rbComp->AddForce(LMVector3(0, -1 * gravityMultiplier,0));
		newUpDirection = LMVector3(0, autoRotIntensity * dt / 100.0f, 0);//1;
	}
	//Lerp Between last upwards and current, and apply
	LMVector3 finalDir;
	finalDir = finalDir.Lerp(lastUpwardDir, newUpDirection, dt / 100.0f);
	tr->SetUpwards(finalDir);

	lastUpwardDir = finalDir;
	inAirLastFrame = inAir;
	//InAir Check
	/*if (!inAirLastFrame && inAir)
		inputMng->RumbleController(.3, .2f);

	if (inAirLastFrame && !inAir)
		inputMng->RumbleController(1, .2f);*/

	
}

void PlayerController::GetInput()
{
	// Almacenar valores de input
	accelerate = inputMng->GetKey(LMKS_W)
		|| inputMng->GetButton(LMC_A)
		|| inputMng->GetButton(LMC_RIGHTSHOULDER);

	reverseAccelerate = inputMng->GetKey(LMKS_S)
		|| inputMng->GetButton(LMC_B)
		|| inputMng->GetButton(LMC_LEFTSHOULDER);


	turnRight = inputMng->GetKey(LMKS_D);
	turnLeft = inputMng->GetKey(LMKS_A);

	tiltLeft = inputMng->GetKey(LMKS_Q);
	tiltRight = inputMng->GetKey(LMKS_E);

	joystickValue = inputMng->GetJoystickValue(0, InputManager::Horizontal);

	accTriggerValue = inputMng->GetTriggerValue(1);
	reverseAccTriggerValue = inputMng->GetTriggerValue(0);
	if (accTriggerValue > 0)accelerate = true;
	if (reverseAccTriggerValue > 0)reverseAccelerate = true;

	turning = (turnLeft || turnRight || abs(joystickValue) > joystickDeadzone);
	tilting = (tiltLeft || tiltRight);
}

// Gestionar movimiento linear/angular
void PlayerController::MoveShip(float dt)
{
	// Aplicar fuerzas
	//TiltShip(dt);
	ApplyLinearForces(dt);
	// Desaceleracion controlada
	LinearDrag(dt);

	// Mantener la UI actualizada
	UpdateVelocityUI();
	//AdjustFov();
}

void PlayerController::TurnShip(float dt)
{
	// Aplicar fuerzas
	ApplyAngularForces(dt);
	return;
	if (!inAir) {
		float currentVel = rbComp->GetLinearVelocity().Magnitude();
		if (!reverseAccelerate) {
			rbComp->SetLinearVelocity(forw * currentVel);
		}
	}
	// Definir variables necesarios para los calculos de las rotaciones
	LMVector3 currentAngularVelocity = rbComp->GetAngularVelocity();
	// Conocer la direccion en la que se esta rotando (izquierda/derecha)

	double yAngVel = tr->GetRotation().Rotate(currentAngularVelocity).GetY();
	if (yAngVel == 0)yAngVel = 0.0001;
	int direction = abs(yAngVel) / yAngVel; // -1 : izquierda // 1 : derecha


	LimitMaxAngleVelocity(currentAngularVelocity, direction);

	// Aplicar el drag angular si no se esta intentando rotar el coche
	if (!turning)
		AngularDrag(currentAngularVelocity, direction);

	// Inclinar el meshRenderer hijo de la nave para darle mejor sensacion al jugar
	SwayShip(currentAngularVelocity.Magnitude(), direction);
}

// Aplicar fuerzas
void PlayerController::ApplyLinearForces(float dt)
{
	//if (accelerate && reverseAccelerate)return;
	if (accelerate) {
		if (accTriggerValue > 0) rbComp->AddForce(forw * acceleration * accTriggerValue);//controller
		else rbComp->AddForce(forw * acceleration);//keyboard
	}
	else if (reverseAccelerate) {
		LMVector3 backw = forw;
		backw = backw * -1;
		if (reverseAccTriggerValue > 0) rbComp->AddForce(backw * -acceleration * 0.5f * reverseAccTriggerValue);
		else rbComp->AddForce(backw * acceleration);
	}
}

void PlayerController::ApplyAngularForces(float dt)
{
	if (turnRight)
		rbComp->ApplyTorqueImpulse(tr->GetRotation().Up() * -angularForce * dt);
	
	if (turnLeft)
		rbComp->ApplyTorqueImpulse(tr->GetRotation().Up() * angularForce * dt);
	
	// Activar desactivar Gyroscopio
	/*if (inputMng->GetButtonDown(LMC_DPAD_UP))
	{
		useGyro = !useGyro;
		if (useGyro)
			EnableGyro();
		else
			DisableGyro();
	}
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

		rbComp->ApplyTorqueImpulse(tr->GetRotation().Up() * angularForce * gyroValue * dt);
	}
	// Usar el Joystick
	else {
		joystickValue *= .5f;
		// Giro con joystick
		if (abs(joystickValue) >= joystickDeadzone)
			rbComp->ApplyTorqueImpulse(tr->GetRotation().Up() * angularForce * -joystickValue * dt);
	}*/
}

void PlayerController::TiltShip(float dt)
{
	if (tiltRight)
	{
		rbComp->ApplyTorqueImpulse(tr->GetRotation().Right() * -angularForce * dt);
	}

	if (tiltLeft)
	{
		rbComp->ApplyTorqueImpulse(tr->GetRotation().Right() * angularForce * dt);
	}
}


// Aplicar Drag
void PlayerController::LinearDrag(float dt)
{
	// Desacelerar la velocidad actual para que no haya tanto derrape
	LMVector3 localVel = rbComp->GetLinearVelocity();

	float angle = localVel.Angle(forw);
	float intensity = (localVel.Magnitude() * linearDragForce) / 20;
	linearDragIntensity = intensity;
	localVel.Normalize();
	LMVector3 invertedVelocity = localVel * -1;

	// Si el angulo entre la velocidad real del coche y la direccion en la que esta mirando es grande
	// Aplicar una fuerza inversa a la velocidad actual para controlar el derrape
	if (angle > .01f)
		rbComp->AddForce(invertedVelocity * intensity * angle);
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
void PlayerController::SwayShip(float currentAngularVelocity, int direction)
{
	// Angulo maximo de la inclinacion visual del coche en grados
	double maxTiltAngle = 10;

	// Determina cuanto se inclina el coche, es un valor de 0 a 1
	double tiltAmount = currentAngularVelocity / maxAngularVelocity;
	// Rotar SOLO la parte grafica del coche para mejor sensacion de juego
	// Teniendo en cuenta la velocidad angular
	if (carModel != nullptr)
	{
		//printf("\n Tilt: %.2f", tiltAmount);
		//meshComp->Rotate(LMVector3(0, tiltAmount * direction * 30, tiltAmount * maxTiltAngle * direction));
		//carModel->GetTransform()->SetLocalRotation(carModel->GetTransform()->GetLocalEulerRotation() + 
		//	LMVector3(0, tiltAmount * direction * 30, tiltAmount * maxTiltAngle * direction));
	}
}


// Metodos extra
void PlayerController::LimitMaxAngleVelocity(LMVector3 currentAngularVelocity, int direction)
{
	// Limitar la velocidad angular maxima
	if (abs(tr->GetRotation().Rotate(currentAngularVelocity).GetY()) > maxAngularVelocity) {
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
	if(cam!=nullptr)
	cam->SetFOV(fov);
}

void JuegoDeAutos::PlayerController::CheckRespawn()
{
	// Si la nave se cae al agua, acceder al ultimo chekpoint
	if (tr->GetPosition().GetY() < -550)
	{
		LMVector3 lastCheckpointPos = raceManager->GetPlayerLastCheckpointPosition();
		tr->SetPosition(lastCheckpointPos + LMVector3(0, 50, 0));
		rbComp->SetLinearVelocity(LMVector3(0, 0, 0));
		rbComp->SetAngularVelocity(LMVector3(0, 0, 0));
	}
}


// UI
void PlayerController::UpdateVelocityUI()
{
	int velocityClean = round(rbComp->GetLinearVelocity().Magnitude());
	AudioSource* auSrc = gameObject->GetComponent<AudioSource>();
	if (auSrc)
		auSrc->SetFreq((rbComp->GetLinearVelocity().Magnitude() / ((1300.f + acceleration * .75f) + (acceleration * -1)) + 0.85f));

	// Para mostrar la velocidad se redondea la magnitud 
	// del vector de velocidad y se actualiza el texto
	if (velocityText == nullptr) return;
	velocityText->ChangeText(std::to_string(velocityClean / 6) + " KM / H");

	LMVector3 color = LMVector3(0.8f, 0.1f, 0.2f);
	velocityText->SetTopColor(color.GetX(), color.GetY(), color.GetZ());
	velocityText->SetBottomColor(color.GetX(), color.GetY(), color.GetZ());

	inputMng->SetControllerLedColor(0.5f, 0, 0);
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

void JuegoDeAutos::PlayerController::SetControllable(bool controllable)
{
	this->activeInput = controllable;
}

void JuegoDeAutos::PlayerController::OnCollisionEnter(GameObject* other)
{
	gameObject->GetComponent<AudioSource>()->PlayOneShot("Assets/Sounds/lowDown.wav", tr->GetPosition());
}
