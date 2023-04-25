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

	TurnShip();
}


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
}

// Gestionar movimiento linear/angular

void PlayerController::MoveShip(float dt)
{
	// Almacenar valores de input
	bool accelerate = inputMng->GetKey(LMKS_W) 
				   || inputMng->GetButton(LMC_A) 
				   || inputMng->GetButton(LMC_RIGHTSHOULDER);
	// Aplicar fuerzas
	ApplyLinearForces(accelerate, dt);

	// Desaceleracion controlada
	LinearDrag(dt);

	// Mantener la UI actualizada
	UpdateVelocityUI();
}

void PlayerController::TurnShip()
{
	// Almacenar valores de input
	bool turnRight = inputMng->GetKey(LMKS_D);
	bool turnLeft = inputMng->GetKey(LMKS_A);

	double joystickValue;
	joystickValue = inputMng->GetJoystickValue(0, InputManager::Horizontal);


	// Aplicar fuerzas
	ApplyAngularForces(turnLeft, turnRight, joystickValue);


	// Definir variables necesarios para los calculos de las rotaciones
	LMVector3 currentAngularVelocity = rbComp->GetAngularVelocity();
	// Conocer la direccion en la que se esta rotando (izquierda/derecha)
	double yAngVel = currentAngularVelocity.GetY();
	int direction = abs(yAngVel) / yAngVel; // -1 : izquierda // 1 : derecha


	// Aplicar el drag angular si no se esta intentando rotar el coche
	if (!turnLeft && !turnRight && abs(joystickValue) < joystickDeadzone)
		AngularDrag(currentAngularVelocity, direction);


	// Inclinar el meshRenderer de la nave para darle mejor sensacion al jugar
	TiltShip(currentAngularVelocity.Magnitude(), direction);
}

// Aplicar fuerzas

void PlayerController::ApplyLinearForces(bool accelerate, float dt)
{
	if (accelerate)
		rbComp->addForce(gameObject->GetTransform()->GetRotation().Forward() * 40 * dt);
}

void PlayerController::ApplyAngularForces(bool turnLeft, bool turnRight, double joystickValue)
{
	float torqueStrengh = 8.f;
	if (turnRight)
		// TODO: quitar la referencia directa a btvector3 abajo tambien
		rbComp->ApplyTorqueImpulse(gameObject->GetTransform()->GetRotation().Up() * -torqueStrengh);
	//rbComp->getBody()->applyTorqueImpulse(btVector3(gameObject->GetTransform()->GetRotation().Up().GetX(), gameObject->GetTransform()->GetRotation().Up().GetY(), gameObject->GetTransform()->GetRotation().Up().GetZ()) * -torqueStrengh);

	if (turnLeft)
		rbComp->ApplyTorqueImpulse(gameObject->GetTransform()->GetRotation().Up() * torqueStrengh);


	// Giro con joystick
	if (abs(joystickValue) >= joystickDeadzone)
		rbComp->ApplyTorqueImpulse(gameObject->GetTransform()->GetRotation().Up() * torqueStrengh * -joystickValue);
}

// Aplicar Drag

void PlayerController::LinearDrag(float dt)
{
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
	double angularDrag = .7;
	currentAngularVelocity = LMVector3(currentAngularVelocity.GetX() * angularDrag,
		currentAngularVelocity.GetY() * angularDrag,
		currentAngularVelocity.GetZ() * angularDrag);

	// Actualizar velocidad angular
	rbComp->SetAngularVelocity(currentAngularVelocity);
}

// Tilt

void PlayerController::TiltShip(double currentAngularVelocity, int direction)
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
	raceManager->UpdateCarPosition("player", pos.GetX(), pos.GetY(), pos.GetZ());
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
}