#pragma once
#include "Component.h"

namespace LocoMotor {
	class GameObject;
	class Transform;
}
namespace JuegoDeAutos {
	class CameraPanner : public  LocoMotor::Component {
	public:
		const static std::string name;
		static std::string GetName() {
			return "CameraPanner";
		};
		CameraPanner();
		void Init(std::vector<std::pair<std::string, std::string>>& params) override;
		/// @brief Does things when collides with an object
		/// @param other the object collided with the entity  
		void Start() override;
		void Update(float dt) override;
	private:
		float panSpeed;
		LocoMotor::Transform* tr;
	};
}