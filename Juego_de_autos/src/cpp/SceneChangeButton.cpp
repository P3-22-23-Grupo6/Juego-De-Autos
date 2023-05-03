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

	_raceButton = gameObject->GetScene()->GetObjectByName("raceButton")->GetComponent<UIImageLM>();
	_speedButton = gameObject->GetScene()->GetObjectByName("speedButton")->GetComponent<UIImageLM>();
	_speedText = _speedButton->gameObject->GetComponent<UITextLM>();

	if (_speedButton != nullptr) {
		_speedButton->CallOnClick([this]() {
			ChangeVelocity();
			});
	}

	if (_raceButton != nullptr) {
		_raceButton->CallOnClick([this]() {
			ScriptManager::GetInstance()->LoadSceneFromFile("Assets/scene.lua");
			std::cout << "hola\n";
		});
	}
}

void JuegoDeAutos::SceneChangeButton::ChangeVelocity()
{
	RaceManager::SpeedMode aux = RaceManager::speedMode;

	int speedIndex = (int) aux;
	if (speedIndex + 1 < 3)
		speedIndex++;
	else speedIndex = 0;

	aux = (RaceManager::SpeedMode)speedIndex;
	RaceManager::speedMode = aux;

	switch (aux)
	{
	case JuegoDeAutos::RaceManager::low:
		_speedText->ChangeText("100cc");
		break;
	case JuegoDeAutos::RaceManager::middle:
		_speedText->ChangeText("200cc");
		break;
	case JuegoDeAutos::RaceManager::high:
		_speedText->ChangeText("500cc");
		break;
	default:
		break;
	}
}
