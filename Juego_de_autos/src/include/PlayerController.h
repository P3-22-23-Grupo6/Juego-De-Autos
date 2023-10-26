
#pragma once
#include "Component.h"
#include "LMVector.h"

namespace LocoMotor {
	class RigidBody;
	class Transform;
	class InputManager;
	class SceneManager;
	class MeshRenderer;
	class UITextLM;
	class Camera;
}

namespace JuegoDeAutos {
	class RaceManager;

	class PlayerController : public LocoMotor::Component
	{
	public:
		float counter;
		PlayerController();
		virtual ~PlayerController();

		void Init(std::vector<std::pair<std::string, std::string>>& params) override;

		void InitComponent() override;


		void Start()override;
		/// @brief Updates the component 
		/// @param dt delta time
		void Update(float dt)override;


		// Movimiento de la nave

		// Actualiza la direccion Up del componente Transform para que la nave siempre se posicione
		// a la misma distancia y direccion de la carretera respetando su rotacion
		// Esto es necesario para que la nave se quede "pegada" a la carretera en todo momento

		/// @brief Updates the direcction Up of the Transform component, so the ship is always at the
		/// same distance and rotation 
		/// @param dt delta time 
		void SetUpwards(float dt);

		// Almacena el input de esta ejecucion

		/// @brief Gets the input on that frame
		void GetInput();

		// Metodos que se encargan de la gestion del movimiento linear/angular
		// Se encargan de llamar a los metodos de movimiento de forma ordenada y controlada

		/// @brief Moves the ship using linear forces
		void MoveShip(float dt);
		/// @brief Moves the ship using angular forces
		void TurnShip(float dt);
		void TiltShip(float dt);

		// Dependiendo del Input recogido, estos metodos aplican fuerzas al rigidbody de la nave

		/// @brief Applies linear force
		/// @param dt delta time
		void ApplyLinearForces(float dt);
		/// @brief Applies angular force
		/// @param dt delta time
		void ApplyAngularForces(float dt);

		/// @brief Applies an angular drag
		/// @param currentAngularVelocity Current angular velocity
		/// @param direction Current direction 
		void AngularDrag(LocoMotor::LMVector3 currentAngularVelocity, int direction);

		// Este metodo se encarga de inclinar levemente el componente MeshRenderer hacia los lados 
		// dependiendo de la rotacion actual de la nave (puramente estetico)

		/// @brief Tilts the mesh renderer depending on the actual rotation
		/// @param currentAngularVelocity Current angular velocity
		/// @param direction Current direction 
		void SwayShip(float currentAngularVelocity, int direction);

		// Limita la velocidad maxima angular para que el coche no pueda girar rapidisimo
		/// @brief Limits the maximum angular velocity 
		/// @param currentAngularVelocity Current angular velocity
		/// @param direction Current direction 
		void LimitMaxAngleVelocity(LocoMotor::LMVector3 currentAngularVelocity, int direction);
		/// @brief Sets the FOV of the camera according to the velocity of the ship
		void AdjustFov();
		/// @brief Checks and respawns the ship on the last checkpoint if it goes under the water
		void CheckRespawn();

		/// @brief Updates the text and the color of the velocity text on the UI
		void UpdateVelocityUI();

		/// @brief Enables the gyroscope
		void EnableGyro();
		/// @brief Disables the gyroscope
		void DisableGyro();
		/// @brief Sets a new acceleration force
		/// @param newAcceleration The acceletration
		void SetAcceleration(float newAcceleration);

		/// @brief Enables or disables input for the ship
		/// @param controllable True if the ship is controllable
		void SetControllable(bool controllable);

		void OnCollisionEnter(LocoMotor::GameObject* other) override;

	private:

		//CarModel
		LocoMotor::GameObject* carModel;
		LocoMotor::GameObject* carBillboard;//TODO Temporal
		LocoMotor::Transform* tr;
		LocoMotor::LMVector3 forw;
		LocoMotor::LMVector3 lastUpwardDir;
		LocoMotor::LMVector3 lastPos;
		// Referencias
		RaceManager* raceManager;
		LocoMotor::RigidBody* rbComp;
		LocoMotor::MeshRenderer* meshComp;
		LocoMotor::InputManager* inputMng;
		LocoMotor::SceneManager* sceneMng;
		LocoMotor::UITextLM* velocityText;
		LocoMotor::Camera* cam;

		// Paremetros de movimiento
		float acceleration = 50;//r
		float reversingAcceleration = 50;//r
		float maxAngularVelocity = 4;
		float angularForce = 0.4f;//r
		float angularDragForce = .6f;
		float raycastDistance = 4;//r
		float angleThreshold = 0.9f;//r
		float gravityMultiplier = 90;//r

		//Gamepad
		float joystickDeadzone = .001f;
		bool useGyro = false;
		float maxGyroValue = 8;

		// Fov
		float initialFov = 50;
		float maxExtraFov = 10;

		// Almacenar informacion
			// Controles
				// Devuelve true si en esta ejecucion se tiene presionado el boton de acelerar (mando o teclado)
		bool accelerate;
		bool reverseAccelerate;
		bool turnRight;
		bool turnLeft;
		bool tiltLeft;
		bool tiltRight;
		float joystickValue;
		float accTriggerValue;
		float reverseAccTriggerValue;
		float gyroValue;

		// Devuelve true si se esta girando
		bool turning;
		bool tilting;
		bool inAir;
		bool inAirLastFrame;

		// Guarda la intensidad del drag en cada momento para usarlo como aceleracion extra
		float linearDragIntensity;
		bool activeInput = false;

		int playerIndex;//First Player
	};
}