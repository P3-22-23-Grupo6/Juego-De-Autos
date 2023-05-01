#pragma once
#include "Component.h"

namespace LocoMotor {
	class RigidBodyComponent;
	class GameObject;
}
namespace JuegoDeAutos {
	class RaceManager;

	//class LocoMotor::GameObject;

	class Boost : public  LocoMotor::Component {
	public:
		const static std::string name;
		static std::string GetName() {
			return "Boost";
		};
		Boost();

		void InitComponent() override;
		void Update(float dt) override;
		//void OnCollisionEnter(GameObject* other) override;
		void OnCollisionEnter(LocoMotor::GameObject* other);

	private:
	};
}