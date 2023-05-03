#include "SceneChangeButton.h"
#include "GameObject.h"
#include "RaceManager.h"
#include "Scene.h"
#include "UIImageLM.h"
#include "ScriptManager.h"
using namespace LocoMotor;
JuegoDeAutos::SceneChangeButton::SceneChangeButton()
{
	_raceButton = nullptr;
}

JuegoDeAutos::SceneChangeButton::~SceneChangeButton()
{
	_raceButton = nullptr;
}

void JuegoDeAutos::SceneChangeButton::Start()
{
	RaceManager::gameModeVelocity = RaceManager::GameModeVelocity::high;

	_raceButton = gameObject->GetScene()->GetObjectByName("raceButton")->GetComponent<UIImageLM>();

	//_button = gameObject->GetComponent<UIImageLM>();
	if (_raceButton != nullptr) {
		_raceButton->CallOnClick([]() {
			ScriptManager::GetInstance()->LoadSceneFromFile("Assets/scene.lua");
			std::cout << "hola\n";
		});
	}
}
