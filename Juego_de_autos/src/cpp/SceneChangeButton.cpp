#include "SceneChangeButton.h"
#include "GameObject.h"
#include "RaceManager.h"
#include "Scene.h"
#include "UIImageLM.h"
#include "UITextLM.h"
#include "ScriptManager.h"
#include "AudioSource.h"
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
	GameObject* racebut = gameObject->GetScene()->GetObjectByName("raceButton");
	GameObject* background = gameObject->GetScene()->GetObjectByName("LocomotorImg");
	
	if (racebut != nullptr) {
		if (racebut->GetComponent<UIImageLM>() != nullptr)
			_raceButton = racebut->GetComponent<UIImageLM>();
	}
	GameObject* speedbut = gameObject->GetScene()->GetObjectByName("speedButton");
	if (speedbut != nullptr) {
		if (speedbut->GetComponent<UIImageLM>() != nullptr) {
			_speedButton = speedbut->GetComponent<UIImageLM>();
			if (_speedButton->gameObject->GetComponent<UITextLM>() != nullptr)
				_speedText = _speedButton->gameObject->GetComponent<UITextLM>();
		}
	}

	if (_speedButton != nullptr) {
		_speedButton->CallOnClick([this]() {
			AudioSource* aSrc = gameObject->GetComponent<AudioSource>();
			if (aSrc)
				aSrc->Play("Assets/Sounds/Select.wav");
			ChangeVelocity();
			});
		_speedButton->SetOnMouseImage("UIPanel2");
		_speedButton->SetPressedImage("UIPanel3");
	}

	if (_raceButton != nullptr) {
		_raceButton->CallOnClick([this]() {
			AudioSource* aSrc = gameObject->GetComponent<AudioSource>();
			if (aSrc)
				aSrc->Play("Assets/Sounds/Select2.wav");
			ScriptManager::GetInstance()->LoadSceneFromFile("Assets/Scenes/testArea.lua");
		});
		_raceButton->SetOnMouseImage("UIPanel2");
		_raceButton->SetPressedImage("UIPanel3");
	}

	switch (RaceManager::speedMode)
	{
	case JuegoDeAutos::RaceManager::low:
		if(_speedText)
		_speedText->ChangeText("100cc");
		break;
	case JuegoDeAutos::RaceManager::middle:
		if (_speedText)
		_speedText->ChangeText("200cc");
		break;
	case JuegoDeAutos::RaceManager::high:
		if (_speedText)
		_speedText->ChangeText("500cc");
		break;
	default:
		break;
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
		if (_speedText)
		_speedText->ChangeText("100cc");
		break;
	case JuegoDeAutos::RaceManager::middle:
		if (_speedText)
		_speedText->ChangeText("200cc");
		break;
	case JuegoDeAutos::RaceManager::high:
		if (_speedText)
		_speedText->ChangeText("500cc");
		break;
	default:
		break;
	}
}
