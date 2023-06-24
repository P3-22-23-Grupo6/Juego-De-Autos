#pragma once
#include "Component.h"

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
	private:
		void FollowSpline(float dt);
		void FollowEnemyCar(float dt);
		RaceManager* raceManager;
		LocoMotor::RigidBody* rbComp;
		LocoMotor::Spline* spline;
		float projectileSpeed;
		float timeStep;
		int totalNumbCheckpoints;
	};
}


