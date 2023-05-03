#pragma once
#include "Component.h"

namespace LocoMotor {
	class GameObject;
	class Spline;
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

		void Init(std::vector<std::pair<std::string, std::string>>& params) override;
		void InitComponent() override;
		void Update(float dt) override;

	private:
		LocoMotor::Spline* mySpline;
		float timeStep; //lastTimeStep
		//STATS
		float enemySpeed;
		float enemyMaxAcc;
		float startSeparation;
	};
}