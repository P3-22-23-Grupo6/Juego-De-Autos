#pragma once
#include "Component.h"

namespace LocoMotor {
	class RigidBody;
	class GameObject;
	class LMVector3;
}
namespace JuegoDeAutos {
	class RaceManager;
	class OilBlind : public  LocoMotor::Component {
	public:
		const static std::string name;
		static std::string GetName() {
			return "Boost";
		};
		OilBlind();
		void Init(std::vector<std::pair<std::string, std::string>>& params) override;
		void Start()override;

		void Update(float dt) override;

		/// @brief Does things when collides with an object
		/// @param other the object collided with the entity  
		void OnCollisionEnter(LocoMotor::GameObject* other);

	private:
		float _timeSplitted;
		LocoMotor::LMVector3 _oriPos;
		LocoMotor::LMVector3 _farPos;
		RaceManager* _rm;
		bool _splitted = false;
	};
}