#pragma once
#include "Component.h"

namespace LocoMotor {
	class UIImageLM;
}
namespace JuegoDeAutos {
	class SceneChangeButton : public LocoMotor::Component {
	public:
		SceneChangeButton();
		~SceneChangeButton();
		void Start() override;



	private:
		LocoMotor::UIImageLM* _raceButton;
	};
}

