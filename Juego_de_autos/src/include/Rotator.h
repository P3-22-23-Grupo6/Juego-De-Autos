#pragma once
#include "Component.h"

namespace LocoMotor {
	class GameObject;
}
namespace JuegoDeAutos {
	class Rotator : public  LocoMotor::Component {
	public:
		const static std::string name;
		static std::string GetName() {
			return "Rotator";
		};
		Rotator();

		void Init(std::vector<std::pair<std::string, std::string>>& params) override;
		void InitRuntime(float rotSpeed);
		/// @brief Updates the rotation
		/// @param dt deltatime
		void Update(float dt) override;

	private:
		float rotateVel;
	};
}