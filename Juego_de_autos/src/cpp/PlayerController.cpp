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

	//gameObject->GetComponent<Mesh>
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


	velocityText = gameObject->GetScene()->GetObjectByName("velocityText")->GetComponent<UITextLM>();
}

void PlayerController::Update(float dt)
{
	//std::cout << "\n" << "LOCAL VEL = " << localVel.GetX()
//	<< ", " << localVel.GetY() << ", " << localVel.GetZ() << "\n"; :TODO

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


	bool acelerate = inputMng->GetKey(LMKS_W) || inputMng->GetButton(LMC_A) || inputMng->GetButton(LMC_RIGHTSHOULDER);
	if (acelerate)
		rbComp->addForce(gameObject->GetTransform()->GetRotation().Forward() * 40 * dt);

	velocityText->ChangeText(std::to_string(rbComp->GetLinearVelocity().Magnitude()) + " KM / H");


	// Desacelerar la velocidad actual para que no haya tanto derrape

	//LMVector3 localVel = BulletToLm(rbComp->getBody()->getLinearVelocity());
	LMVector3 localVel = rbComp->GetLinearVelocity();

	LMVector3 forward = gameObject->GetTransform()->GetRotation().Forward();
	double angle = localVel.Angle(forward);

	double intensity = localVel.Magnitude();

	localVel.Normalize();
	LMVector3 invertedVelocity = localVel * -1;

	// Si el angulo entre la velocidad real del coche y la direccion en la que esta mirando es grande
	// Aplicar una fuerza inversa a la velocidad actual para controlar el derrape
	if (angle > .5f)
		rbComp->addForce(invertedVelocity * intensity / 20 * angle * dt);


	// Giro
	bool rotateRight = inputMng->GetKey(LMKS_D);
	float torqueStrengh = 8.f;
	if (rotateRight)
		// TODO: quitar la referencia directa a btvector3 abajo tambien
		rbComp->ApplyTorqueImpulse(gameObject->GetTransform()->GetRotation().Up() * -torqueStrengh);
	//rbComp->getBody()->applyTorqueImpulse(btVector3(gameObject->GetTransform()->GetRotation().Up().GetX(), gameObject->GetTransform()->GetRotation().Up().GetY(), gameObject->GetTransform()->GetRotation().Up().GetZ()) * -torqueStrengh);

	bool rotateLeft = inputMng->GetKey(LMKS_A);
	if (rotateLeft)
		rbComp->ApplyTorqueImpulse(gameObject->GetTransform()->GetRotation().Up() * torqueStrengh);

	// Giro con joystick
	float joystickValue = inputMng->GetJoystickValue(0, InputManager::Horizontal);
	double deadZone = .05f;
	if (abs(joystickValue) >= deadZone)
		rbComp->ApplyTorqueImpulse(gameObject->GetTransform()->GetRotation().Up() * torqueStrengh * -joystickValue);





	LMVector3 currentAngularVelocity = rbComp->GetAngularVelocity();
	// Conocer la direccion en la que se esta rotando (izquierda/derecha)
	double yAngVel = currentAngularVelocity.GetY();
	int direction = abs(yAngVel) / yAngVel; // -1 : izquierda // 1 : derecha

	// Limitar la velocidad angular maxima
	float maxAngularVelocity = 3.5f;
	if (currentAngularVelocity.Magnitude() > maxAngularVelocity) {
		currentAngularVelocity.Normalize();
		// Modificar el vector de la velocidad angular actual
		currentAngularVelocity = LMVector3(0, maxAngularVelocity * direction, 0);
	}

	// Añadir un drag angular para frenar la rotacion mas controladamente
	double angularDrag = .7;
	if (!rotateLeft && !rotateRight && abs(joystickValue) < deadZone)
		currentAngularVelocity = LMVector3(currentAngularVelocity.GetX() * angularDrag,
			currentAngularVelocity.GetY() * angularDrag,
			currentAngularVelocity.GetZ() * angularDrag);

	// Actualizar velocidad angular
	rbComp->SetAngularVelocity(currentAngularVelocity);



	// Angulo maximo de la inclinacion visual del coche en grados
	double maxTiltAngle = 20;

	// Determina cuanto se inclina el coche, es un valor de 0 a 1
	double tiltAmount = currentAngularVelocity.Magnitude() / maxAngularVelocity;

	// Rotar SOLO la parte grafica del coche para mejor sensacion de juego
	// Teniendo en cuenta la velocidad angular
	gameObject->GetComponent<MeshRenderer>()->
		Rotate(LMVector3(0, 0, tiltAmount * maxTiltAngle * direction));

	// Actualizar las posiciones del raceManager
	LMVector3 pos = gameObject->GetTransform()->GetPosition();
	raceManager->UpdateCarPosition("player", pos.GetX(), pos.GetY(), pos.GetZ());
}