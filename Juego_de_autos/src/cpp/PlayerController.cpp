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

void JuegoDeAutos::PlayerController::Init(std::vector<std::pair<std::string, std::string>>& params)
{
	for (int i = 0; i < params.size(); i++) {
		if (params[i].first == "PlayerIndex") {
			playerIndex = std::stof(params[i].second);
		}
		if (params[i].first == "PlayerSpeed") {
			acceleration = std::stof(params[i].second);
		}
	}
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
	raceManager = RaceManager::GetInstance();
	//acceleration = 120;// raceManager->GetSpeed();
	lastUpwardDir = LMVector3(0, 1, 0);

	forw = tr->GetRotation().Forward();
	rbComp->UseGravity(LMVector3(0, 0, 0));

	
	//Create Car Model Child
	carModel = sceneMng->AddObjectRuntime("playerCarModel" + std::to_string(playerIndex));
	carModel->AddComponent("Transform");
	carModel->AddComponent("MeshRenderer");
	carModel->GetComponent<Transform>()->InitRuntime(tr->GetPosition());

	//Create Billboard
	carBillboard = sceneMng->AddObjectRuntime("carBillboard" + std::to_string(playerIndex));
	carBillboard->AddComponent("Transform");
	carBillboard->AddComponent("MeshRenderer");
	carBillboard->GetComponent<Transform>()->InitRuntime(tr->GetPosition() + LMVector3(0, 1.f, 0));
	carBillboard->GetComponent<MeshRenderer>()->InitRuntime("BillboardRacers.mesh");

	int carIndexTemp = playerIndex == 0 ? raceManager->carModelPlayerOne : raceManager->carModelPlayerTwo;
	switch (carIndexTemp)
	{
		default: break;
		case 0: carModel->GetComponent<MeshRenderer>()->InitRuntime("BlueFalcon.mesh");
			
			break;
		case 1: carModel->GetComponent<MeshRenderer>()->InitRuntime("Eagle.mesh"); break;
		case 2: carModel->GetComponent<MeshRenderer>()->InitRuntime("Pelican.mesh"); break;
		case 3: carModel->GetComponent<MeshRenderer>()->InitRuntime("Flamingo.mesh"); break;
	}
	std::string materialAssigned = "m_RacerGizmo0" + std::to_string(carIndexTemp);
	carBillboard->GetComponent<MeshRenderer>()->ChangeMaterial(materialAssigned);
	meshComp = carModel->GetComponent<LocoMotor::MeshRenderer>();

	if (gameObject->GetScene()->GetCamera() != nullptr)
		cam = gameObject->GetScene()->GetCamera()->GetComponent<Camera>();

	//Velocity Text
	GameObject* vltxt = gameObject->GetScene()->GetObjectByName("velocityText");
	if (vltxt != nullptr && vltxt->GetComponent<UITextLM>() != nullptr) {
		velocityText = vltxt->GetComponent<UITextLM>();
	}
	lastPos = tr->GetPosition();
	tr->AddChild(carModel->GetTransform());
	carModel->GetTransform()->AddChild(carBillboard->GetTransform());
	tr->SetPosition(lastPos);
}



void PlayerController::Update(float dt)
{
	counter += dt;
	/*LMVector3 newPos; TEST LERPING
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
	//Tilting/Drifting
	if (tilting && tiltAmount < 2.0f) tiltAmount += 0.02f;
	else if (!tilting) tiltAmount = 1.0f;
	//Air Tilt
	if (inAir)
	{
		if (airTime < 16.0f) airTime += 0.2f;
	}
	else
	{
		if (airTime > 0.0f) airTime -= 2.0f;
		else airTime = 0.0f;
	}

	MoveShip(dt);

	TurnShip(dt);
	 
	// Actualizar las posiciones del raceManager
	if (raceManager != nullptr)
	{
		//raceManager->UpdateCarPosition("Player", tr->GetPosition());
		CheckRespawn();
	}
}


// Gestionar orientacion

void PlayerController::SetUpwards(float dt)
{
	LMVector3 newUpDirection;
	LMVector3 from = tr->GetPosition();
	LMVector3 to;

	LMVector3 upVector = tr->GetRotation().Up();
	upVector.Normalize();
	upVector = upVector * 10.0f;
	to = from - upVector;

	//Grounded
	if (rbComp->GetRaycastHit(from, to)) {
		inAir = false;
		LMVector3 n = rbComp->GethasRaycastHitNormal(from, to);
		n.Normalize();

		if (n.Angle(tr->GetRotation().Up()) > 0.9f) return;

		//Lerp Between last upwards and current, and apply
		LMVector3 finalDir;
		LMVector3 newUpDirection = n	 * 100.0f;
		finalDir = finalDir.Lerp(lastUpwardDir, newUpDirection, dt / 1000.0f);
		tr->SetUpwards(newUpDirection);

		lastUpwardDir = finalDir;
		inAirLastFrame = inAir;

		LMVector3 hitPos = rbComp->GetraycastHitPoint(from, to);
		double hoverDist = 1.0f; // 7
		LMVector3 newPos = n * hoverDist + hitPos;
		LMVector3 finalPos;
		finalPos = finalPos.Lerp(lastPos, newPos, 1.0f);
		tr->SetPosition(finalPos);
		lastPos = finalPos;
		return;
	}
	//Not Grounded
	else
	{
		inAir = true;
		float autoRotIntensity = 100;
		rbComp->AddForce(LMVector3(0, -1 * gravityMultiplier, 0));
		newUpDirection = LMVector3(0, 1, 0);
	}
	//Lerp Between last upwards and current, and apply
	LMVector3 finalDir;
	finalDir = finalDir.Lerp(lastUpwardDir, newUpDirection, dt / 100.0f);
	tr->SetUpwards(finalDir);
	lastPos = finalDir;
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
	
	accelerate = inputMng->GetKey(LMKS_UP)
		|| inputMng->GetButton(LMC_A);

	reverseAccelerate = inputMng->GetKey(LMKS_DOWN)
		|| inputMng->GetButton(LMC_B);

	turnRight = inputMng->GetKey(LMKS_RIGHT);
	turnLeft = inputMng->GetKey(LMKS_LEFT);

	tiltLeft = inputMng->GetButton(LMC_LEFTSHOULDER);
	tiltRight = inputMng->GetButton(LMC_RIGHTSHOULDER);

	joystickValue = inputMng->GetJoystickValue(0, InputManager::Horizontal);

	//accTriggerValue = inputMng->GetTriggerValue(1);
	//reverseAccTriggerValue = inputMng->GetTriggerValue(0);
	//
	//if (accTriggerValue > 0)accelerate = true;
	//if (reverseAccTriggerValue > 0) reverseAccelerate = true;

	turning = (turnLeft || turnRight || abs(joystickValue) > joystickDeadzone);
	tilting = (tiltLeft || tiltRight);
}

// Gestionar movimiento linear/angular
void PlayerController::MoveShip(float dt)
{
	// Aplicar fuerzas
	//TiltShip(dt); MINE; AUN NO IMPLEMENTADO
	ApplyLinearForces(dt);

	// Mantener la UI actualizada
	UpdateVelocityUI();
	AdjustFov();
}

void PlayerController::TurnShip(float dt)
{
	// Aplicar fuerzas
	ApplyAngularForces(dt);
	if (!inAir && !reverseAccelerate)
		rbComp->SetLinearVelocity(forw * rbComp->GetLinearVelocity().Magnitude());

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
	else if (reverseAccelerate && !inAir) {
		if (rbComp->GetLinearVelocity().Magnitude() < 0.2f)
		{
			//Retroceder
		
		}
		else//Frenar
		{
			LMVector3 backw = forw;
			backw = backw * -1;
			if (reverseAccTriggerValue > 0) rbComp->SetLinearVelocity(rbComp->GetLinearVelocity() * 0.95f * -reverseAccTriggerValue);
			else rbComp->SetLinearVelocity(rbComp->GetLinearVelocity() * 0.95f);
		}
		
	}
	//if (tiltRight) {
	//	//rbComp->AddForce();//keyboard
	//	LMVector3 newDirA = tr->GetRotation().Right();
	//	newDirA.Normalize();
	//	rbComp->AddForce(newDirA * acceleration * 5.0f);
	//}
	//if (tiltLeft) {
	//	//rbComp->AddForce();//keyboard
	//	LMVector3 newDirA = tr->GetRotation().Right();
	//	newDirA.Normalize();
	//	rbComp->AddForce(newDirA * -acceleration * 5.0f);
	//}
	//if (tilting) rbComp->SetLinearVelocity(rbComp->GetLinearVelocity() * 0.9f);
}

void PlayerController::ApplyAngularForces(float dt)
{
	float multiplierRot = 1.0f;
	if (tilting && turning ) multiplierRot = 1.9f;
	if (turnRight)
		rbComp->ApplyTorqueImpulse(tr->GetRotation().Up() * multiplierRot * -angularForce * dt / 100.0f);

	if (turnLeft)
		rbComp->ApplyTorqueImpulse(tr->GetRotation().Up() * multiplierRot * angularForce * dt / 100.0f);

	// Activar desactivar Gyroscopio
	if (inputMng->GetButtonDown(LMC_DPAD_UP))
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
		gyroValue *= 2;
		// Clampear el valor
		if (gyroValue > maxGyroValue)
			gyroValue = maxGyroValue;
		else if (gyroValue < -maxGyroValue)
			gyroValue = -maxGyroValue;

		rbComp->ApplyTorqueImpulse(tr->GetRotation().Up() * angularForce * gyroValue * dt);
	}
	// Usar el Joystick
	else {
		joystickValue *= .042f;
		// Giro con joystick
		if (abs(joystickValue) >= joystickDeadzone)
			rbComp->ApplyTorqueImpulse(tr->GetRotation().Up() * multiplierRot * angularForce * -joystickValue);
	}
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

void PlayerController::AngularDrag(LMVector3 currentAngularVelocity, int direction)
{
	// Añadir un drag angular para frenar la rotacion mas controladamente
	//double angularDrag = .7;
	currentAngularVelocity = LMVector3(currentAngularVelocity.GetX() * angularDragForce,
		currentAngularVelocity.GetY() * angularDragForce,
		currentAngularVelocity.GetZ() * angularDragForce);

	// Actualizar velocidad angular
	//if (tilting) currentAngularVelocity * 5.0f;
	rbComp->SetAngularVelocity(currentAngularVelocity);
}


// Tilt
void PlayerController::SwayShip(float currentAngularVelocity, int direction)
{
	double maxTiltAngle = (2.0f * rbComp->GetLinearVelocity().Magnitude()) + 5;
	double angularTilt = currentAngularVelocity / maxAngularVelocity;

	if (carModel == nullptr) return;

	//printf("\n Tilt: %.2f", tiltAmount);
	carModel->GetTransform()->SetLocalRotation(carModel->GetTransform()->GetLocalRotation() + tr->GetRotation().Rotate(tr->GetRotation().Forward(),
		(angularTilt * maxTiltAngle  * -direction)));
	//carModel->GetTransform()->SetLocalRotation(carModel->GetTransform()->GetLocalRotation() + tr->GetRotation().Rotate(tr->GetRotation().Up(),
	//	(angularTilt * maxTiltAngle * direction * tiltAmount)));
	carModel->GetTransform()->SetLocalRotation(carModel->GetTransform()->GetLocalRotation() + tr->GetRotation().Rotate(tr->GetRotation().Right(),
		(-airTime * 2.0f)));
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
	float fovOne = (localVel.Magnitude() / 60);
	if (fovOne > 1) fovOne = 1;
	float fov = fovOne * maxExtraFov + initialFov;
	if (cam != nullptr)
		cam->SetFOV(fov);
}

void JuegoDeAutos::PlayerController::CheckRespawn()
{
	// Si la nave se cae al agua, acceder al ultimo chekpoint
	if (tr->GetPosition().GetY() < -200)
	{
		KillPlayer();
		
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

void JuegoDeAutos::PlayerController::KillPlayer()
{
	if (raceManager == nullptr) return;
	LMVector3 lastCheckpointPos = raceManager->GetPlayerLastCheckpointPosition();
	tr->SetPosition(lastCheckpointPos + LMVector3(0, 50, 0));
	rbComp->SetLinearVelocity(LMVector3(0, 0, 0));
	rbComp->SetAngularVelocity(LMVector3(0, 0, 0));
}
