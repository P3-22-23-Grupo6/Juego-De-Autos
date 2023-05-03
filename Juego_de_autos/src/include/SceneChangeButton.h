#pragma once
#include "Component.h"

namespace LocoMotor {
	class UIImageLM;
	class UITextLM;
}
namespace JuegoDeAutos {
	class SceneChangeButton : public LocoMotor::Component {
	public:
		SceneChangeButton();
		~SceneChangeButton();
		void Start() override;


	private:

		void ChangeVelocity();

		LocoMotor::UIImageLM* _raceButton;
		LocoMotor::UIImageLM* _speedButton;
		LocoMotor::UITextLM* _speedText;

		enum SpeedType {low, middle, high};
		SpeedType currentSpeed;
	};
}

