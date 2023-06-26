#pragma once
#include "Component.h"
#include "LMVector.h"

namespace LocoMotor {
	class RigidBody;
	class Spline;
	class GameObject;
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
		void FollowSpline(float dt);
		void FollowEnemyCar(float dt);
		bool IsInChaseRange();
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


