#include "SceneChangeButton.h"
#include "GameObject.h"
#include "RaceManager.h"
#include "UIImageLM.h"
#include "ScriptManager.h"
using namespace LocoMotor;
JuegoDeAutos::SceneChangeButton::SceneChangeButton()
{
	_button = nullptr;
}

JuegoDeAutos::SceneChangeButton::~SceneChangeButton()
{
	_button = nullptr;
}

void JuegoDeAutos::SceneChangeButton::Start()
{
	RaceManager::gameModeVelocity = RaceManager::GameModeVelocity::high;

	_button = gameObject->GetComponent<UIImageLM>();
	if (_button != nullptr) {
		_button->CallOnClick([]() {
			ScriptManager::GetInstance()->LoadSceneFromFile("Assets/scene.lua");
			std::cout << "hola\n";
		});
	}
}
