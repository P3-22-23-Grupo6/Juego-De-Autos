#pragma once
#include "Component.h"
#include "LMVector.h"

namespace LocoMotor {
	class RigidBody;
	class Spline;
}

namespace JuegoDeAutos{
	class RaceManager;
	class Projectile : public  LocoMotor::Component
	{
	public:
		const static std::string name;
		static std::string GetName() {
			return "Projectile";
		};
		Projectile();
		void Init(std::vector<std::pair<std::string, std::string>>& params) override;
		void Start()override;
		void Update(float dt) override;
		void OnEnable();
		void OnDisable();
	private:
		/// @brief Method to call when the projectile is far from the enemy car,
		/// so it will follow the spline.
		void FollowSpline(float dt);
		/// @brief Method to call when the projectile is near the enemy car.
		void FollowEnemyCar(float dt);
		/// @brief Method to know whether the enemy car is close or not.
		bool IsInChaseRange();
		/// @brief Method to know whether the enemy car is in impact range or not.
		bool IsInImpactRange();
		RaceManager* raceManager;
		LocoMotor::RigidBody* rbComp;
		LocoMotor::Spline* spline;
		LocoMotor::LMVector3 initialPos;
		float projectileSpeed;
		float timeStep;
		int totalNumbCheckpoints;
	};
}


