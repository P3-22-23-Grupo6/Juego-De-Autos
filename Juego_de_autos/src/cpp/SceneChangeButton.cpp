#include "SceneChangeButton.h"
#include "GameObject.h"
#include "RaceManager.h"
#include "Scene.h"
#include "UIImageLM.h"
#include "UITextLM.h"
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
	_speedButton = gameObject->GetScene()->GetObjectByName("speedButton")->GetComponent<UIImageLM>();
	_speedText = _speedButton->gameObject->GetComponent<UITextLM>();

	if (_speedButton != nullptr) {
		_speedButton->CallOnClick([this]() {

			ChangeVelocity();
			});
	}

	if (_raceButton != nullptr) {
		_raceButton->CallOnClick([]() {
			ScriptManager::GetInstance()->LoadSceneFromFile("Assets/scene.lua");
			std::cout << "hola\n";
		});
	}
}

void JuegoDeAutos::SceneChangeButton::ChangeVelocity()
{
	int speedIndex = (int)currentSpeed;
	if (speedIndex + 1 < 3)
		speedIndex++;
	else speedIndex = 0;

	currentSpeed = (SpeedType) speedIndex;

	switch (currentSpeed)
	{
	case JuegoDeAutos::SceneChangeButton::low:
		_speedText->ChangeText("100CC");
		break;
	case JuegoDeAutos::SceneChangeButton::middle:
		_speedText->ChangeText("200CC");
		break;
	case JuegoDeAutos::SceneChangeButton::high:
		_speedText->ChangeText("500CC");
		break;
	default:
		break;
	}
}
