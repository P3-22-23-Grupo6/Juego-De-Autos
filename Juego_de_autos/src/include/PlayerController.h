#pragma once
#include "Component.h"
#include "LMVector.h"

namespace LocoMotor {
	class RigidBody;
	class InputManager;
	class MeshRenderer;
	class UITextLM;
	class Camera;
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
		void UpdateUpDirection(float dt);

		// Almacena el input de esta ejecucion
		void GetInput();

		// Metodos que se encargan de la gestion del movimiento linear/angular
		// Se encargan de llamar a los metodos de movimiento de forma ordenada y controlada
		void MoveShip(float dt);
		void TurnShip(float dt);

		// Dependiendo del Input recogido, estos metodos aplican fuerzas al rigidbody de la nave
		void ApplyLinearForces(float dt);
		void ApplyAngularForces(float dt);

		// Estos metodos se encargan de aplicar un Drag linear/angular, para que el movimiento de la 
		// nave se sienta mas controlado y mejorar la experiencia de jugador
		void LinearDrag(float dt);
		void AngularDrag(LocoMotor::LMVector3 currentAngularVelocity, int direction);

		// Este metodo se encarga de inclinar levemente el componente MeshRenderer hacia los lados 
		// dependiendo de la rotacion actual de la nave (puramente estetico)
		void TiltShip(float currentAngularVelocity, int direction);

		// Limita la velocidad maxima angular para que el coche no pueda girar rapidisimo
		void LimitMaxAngleVelocity(LocoMotor::LMVector3 currentAngularVelocity, int direction);
		// Ajusta la Fov de la camara dependiendo de la actual velocidad lineal de la nave
		void AdjustFov();
		void CheckRespawn();

		// Actualiza el texto de velocidad y lo cambia de color
		void UpdateVelocityUI();

		void EnableGyro();

		void DisableGyro();

	private:

		// Referencias
		RaceManager* raceManager;
		LocoMotor::RigidBody* rbComp;
		LocoMotor::InputManager* inputMng;
		LocoMotor::UITextLM* velocityText;
		LocoMotor::Camera* cam;

		// Paremetros de movimiento
			// Fisicas
		float acceleration = 1000;
		float maxAngularVelocity = 4;
		float angularForce = .5f;
		float angularDragForce = .6f;
		float linearDragForce = 40;
		float gravityThrust = -1600;
			// Matematicas
				// Linear
				
				// Rotacion
		float currentRotationVelocity = 0;
		float maxRotationVelocity = .1f;
		float rotationAcceleration = .01f;
		float rotationDecceleration = .02f;

		// Controles
		float extraAceleration = 30;
		float joystickDeadzone = .05f;
		bool useGyro = false;
		float maxGyroValue = 8;

		// Fov
		float initialFov = 60;
		float maxExtraFov = 15;

		// Almacenar informacion
			// Controles
				// Devuelve true si en esta ejecucion se tiene presionado el boton de acelerar (mando o teclado)
		bool accelerate;
		bool turnRight;
		bool turnLeft;
		float joystickValue;
		float triggerValue;
		float gyroValue;

		// Devuelve true si se esta girando
		bool turning;
		bool inAir;
		bool inAirLastFrame;

			// Guarda la intensidad del drag en cada momento para usarlo como aceleracion extra
		float linearDragIntensity;

		bool physicsBasedMovement = true;
	};
}