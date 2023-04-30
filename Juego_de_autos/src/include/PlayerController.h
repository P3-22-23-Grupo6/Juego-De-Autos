#pragma once
#include "Component.h"
#include "LMVector.h"

namespace LocoMotor {
	class RigidBodyComponent;
	class InputManager;
	class MeshRenderer;
	class UITextLM;
}

namespace JuegoDeAutos {
	class RaceManager;

	class PlayerController : public LocoMotor::Component
	{
	public:
		PlayerController();
		virtual ~PlayerController();

		void InitComponent() override;
		void Start()override;
		void Update(float dt)override;


		// Movimiento de la nave

		// Actualiza la direccion Up del componente Transform para que la nave siempre se posicione
		// a la misma distancia y direccion de la carretera respetando su rotacion
		// Esto es necesario para que la nave se quede "pegada" a la carretera en todo momento
		void UpdateUpDirection();

		// Metodos que se encargan de la gestion del movimiento linear/angular
		// Se encargan de llamar a los metodos de movimiento de forma ordenada y controlada
		void MoveShip(float dt);
		void TurnShip(float dt);

		// Dependiendo del Input recogido, estos metodos aplican fuerzas al rigidbody de la nave
		void ApplyLinearForces(bool accelerate, float dt);
		void ApplyAngularForces(bool turnLeft, bool turnRight, float joystickValue, float dt);

		void LimitMaxAngleVelocity(LocoMotor::LMVector3 currentAngularVelocity, int direction);
		void ApplyExtraAcceleration(float dt);

		// Estos metodos se encargan de aplicar un Drag linear/angular, para que el movimiento de la 
		// nave se sienta mas controlado y mejorar la experiencia de jugador
		void LinearDrag(float dt);
		void AngularDrag(LocoMotor::LMVector3 currentAngularVelocity, int direction);

		// Este metodo se encarga de inclinar levemente el componente MeshRenderer hacia los lados 
		// dependiendo de la rotacion actual de la nave (puramente estetico)
		void TiltShip(float currentAngularVelocity, int direction);

		// Actualiza el texto de velocidad y lo cambia de color
		void UpdateVelocityUI();

	private:
		RaceManager* raceManager;

		LocoMotor::RigidBodyComponent* rbComp;
		LocoMotor::InputManager* inputMng;

		LocoMotor::UITextLM* velocityText;

		float acceleration = 70;

		float maxAngularVelocity = 6;
		float angularForce = 8.f;

		float angularDragForce = .7f;
		float linearDragForce = 7;

		// Guarda la intensidad del drag en cada momento para usarlo como aceleracion extra
		float linearDragIntensity;

		float extraAceleration = 45;

		bool accelerate;

		float joystickDeadzone = .05f;
	};
}
