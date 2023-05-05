#pragma once
#include "Component.h"

namespace LocoMotor {
	class GameObject;
	class Spline;
	class RigidBody;
}
namespace JuegoDeAutos {
	class RaceManager;

	class EnemyAI : public  LocoMotor::Component {
	public:
		const static std::string name;
		static std::string GetName() {
			return "EnemyAI";
		};
		EnemyAI();

		void Start() override;

		void Init(std::vector<std::pair<std::string, std::string>>& params) override;
		void InitComponent() override;
		void Update(float dt) override;
		//Activate the enemy so it starts moving
		void Activate();

	private:
		//Main method called each frame tu move the enemy along the spline
		void MoveEnemy();
		//Spline to follow
		LocoMotor::Spline* mySpline;
		float timeStep; //lastTimeStep
		//STATS
		float enemySpeed;
		//Separation from the middle of the road, it stays the same during the race
		float startSeparation;
		LocoMotor::RigidBody* rbComp;
		//Used in the initial Countdown
		bool _shouldMove;
	};
}