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
	_startGameButton = nullptr;
	_selectCarButton = nullptr;
	_goToIntroButton = nullptr;
}

JuegoDeAutos::SceneChangeButton::~SceneChangeButton()
{
	_startGameButton = nullptr;
	_selectCarButton = nullptr;
	_goToIntroButton = nullptr;
}

void JuegoDeAutos::SceneChangeButton::Start()
{
	//Declare Buttons to add callbacks to
	GameObject* startGameButton = gameObject->GetScene()->GetObjectByName("startButton");
	GameObject* selectCarButton = gameObject->GetScene()->GetObjectByName("selectVehicleButton");
	GameObject* goToIntroButton = gameObject->GetScene()->GetObjectByName("goToIntroButton");

	GameObject* arrowLeft_Car = gameObject->GetScene()->GetObjectByName("arrowLeftButton");
	GameObject* arrowRight_Car = gameObject->GetScene()->GetObjectByName("arrowRightButton");
	
	//Get Components
	if (startGameButton != nullptr && startGameButton->GetComponent<UIImageLM>() != nullptr) {
		_startGameButton = startGameButton->GetComponent<UIImageLM>();
	}
	if (selectCarButton != nullptr && selectCarButton->GetComponent<UIImageLM>() != nullptr) {
		_selectCarButton = selectCarButton->GetComponent<UIImageLM>();
	}
	if (goToIntroButton != nullptr && goToIntroButton->GetComponent<UIImageLM>() != nullptr) {
		_goToIntroButton = goToIntroButton->GetComponent<UIImageLM>();
	}
	if (arrowLeft_Car != nullptr && arrowLeft_Car->GetComponent<UIImageLM>() != nullptr) {
		_arrowLeft_Car = arrowLeft_Car->GetComponent<UIImageLM>();
	}
	if (arrowRight_Car != nullptr && arrowRight_Car->GetComponent<UIImageLM>() != nullptr) {
		_arrowRight_Car = arrowRight_Car->GetComponent<UIImageLM>();
	}
	/*GameObject* speedbut = gameObject->GetScene()->GetObjectByName("speedButton");
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
	}*/

	if (_startGameButton != nullptr) {
		_startGameButton->CallOnClick([this]() {
			AudioSource* aSrc = gameObject->GetComponent<AudioSource>();
			if (aSrc)
				aSrc->Play("Assets/Sounds/Select2.wav");
			ScriptManager::GetInstance()->LoadSceneFromFile("Assets/Scenes/menu.lua");
		});
		_startGameButton->SetOnMouseImage("UIPanel2");
		_startGameButton->SetPressedImage("UIPanel3");
	}
	if (_selectCarButton != nullptr) {
		_selectCarButton->CallOnClick([this]() {
			AudioSource* aSrc = gameObject->GetComponent<AudioSource>();
			if (aSrc)
				aSrc->Play("Assets/Sounds/Select2.wav");
			ScriptManager::GetInstance()->LoadSceneFromFile("Assets/Scenes/testArea.lua");
			});
		_selectCarButton->SetOnMouseImage("m_selectVehicleButtonSelected");
		_selectCarButton->SetPressedImage("m_selectVehicleButtonSelected");
	}
	if (_goToIntroButton != nullptr) {
		_goToIntroButton->CallOnClick([this]() {
			AudioSource* aSrc = gameObject->GetComponent<AudioSource>();
			if (aSrc)
				aSrc->Play("Assets/Sounds/Select2.wav");
			ScriptManager::GetInstance()->LoadSceneFromFile("Assets/Scenes/intro.lua");
			});
		_goToIntroButton->SetOnMouseImage("m_BackButtonSelected");
		_goToIntroButton->SetPressedImage("m_BackButtonSelected");
	}
	//ARROW LEFT
	if (_arrowLeft_Car != nullptr) {
		_arrowLeft_Car->CallOnClick([this]() {
			AudioSource* aSrc = gameObject->GetComponent<AudioSource>();
			if (aSrc)
				aSrc->Play("Assets/Sounds/Select2.wav");
			ScriptManager::GetInstance()->LoadSceneFromFile("Assets/Scenes/intro.lua");
			});
		_arrowLeft_Car->SetOnMouseImage("ArrowLeft01");
		_arrowLeft_Car->SetPressedImage("ArrowLeft01");
	}
	//ARROW RIGHT
	if (_arrowRight_Car != nullptr) {
		_arrowRight_Car->CallOnClick([this]() {
			AudioSource* aSrc = gameObject->GetComponent<AudioSource>();
			if (aSrc)
				aSrc->Play("Assets/Sounds/Select2.wav");
			ScriptManager::GetInstance()->LoadSceneFromFile("Assets/Scenes/intro.lua");
			});
		_arrowRight_Car->SetOnMouseImage("ArrowRight01");
		_arrowRight_Car->SetPressedImage("ArrowRight01");
	}
	//switch (RaceManager::speedMode)
	//{
	//case JuegoDeAutos::RaceManager::low:
	//	if(_speedText)
	//	_speedText->ChangeText("100cc");
	//	break;
	//case JuegoDeAutos::RaceManager::middle:
	//	if (_speedText)
	//	_speedText->ChangeText("200cc");
	//	break;
	//case JuegoDeAutos::RaceManager::high:
	//	if (_speedText)
	//	_speedText->ChangeText("500cc");
	//	break;
	//default:
	//	break;
	//}
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
