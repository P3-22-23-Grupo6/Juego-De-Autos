#pragma once
#include "Component.h"

namespace LocoMotor {
	class RigidBody;
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

		void Init(std::vector<std::pair<std::string, std::string>>& params) override;
		//void Init(float thrust) {};
		void InitComponent() override;
		void Update(float dt) override;
		//void OnCollisionEnter(GameObject* other) override;
		/// @brief Does things when collides with an object
		/// @param other the object collided with the entity  
		void OnCollisionEnter(LocoMotor::GameObject* other);

	private:
		float thrust;
	};
}