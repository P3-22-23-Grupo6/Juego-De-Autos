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
	_goToIntroButton = nullptr;
	_arrowLeft_Car = nullptr;
	_arrowRight_Car = nullptr;
	_vehiclePortraitImg = nullptr;
	_selectPlayerOne = nullptr;
	_selectPlayerTwo = nullptr;
	vehicleIndex = 0;
}

JuegoDeAutos::SceneChangeButton::~SceneChangeButton()
{
	_startGameButton = nullptr;
	_goToIntroButton = nullptr;
	_vehiclePortraitImg = nullptr;
	_selectPlayerOne = nullptr;
	_selectPlayerTwo = nullptr;
}

void JuegoDeAutos::SceneChangeButton::Start()
{
	//Declare Buttons to add callbacks to
	GameObject* startGameButton = gameObject->GetScene()->GetObjectByName("startButton");
	GameObject* selectCarButton = gameObject->GetScene()->GetObjectByName("selectVehicleButton");
	GameObject* goToIntroButton = gameObject->GetScene()->GetObjectByName("goToIntroButton");
	GameObject* vehiclePortrait = gameObject->GetScene()->GetObjectByName("Vehicle_Portrait");

	GameObject* arrowLeft_Car = gameObject->GetScene()->GetObjectByName("arrowLeftButton");
	GameObject* arrowRight_Car = gameObject->GetScene()->GetObjectByName("arrowRightButton");
	GameObject* selectPlayerOne = gameObject->GetScene()->GetObjectByName("selectPlayerOne");
	GameObject* selectPlayerTwo = gameObject->GetScene()->GetObjectByName("selectPlayerTwo");
	
	//Get Components
	if (startGameButton != nullptr && startGameButton->GetComponent<UIImageLM>() != nullptr) {
		_startGameButton = startGameButton->GetComponent<UIImageLM>();
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
	if (vehiclePortrait != nullptr && vehiclePortrait->GetComponent<UIImageLM>() != nullptr) {
		_vehiclePortraitImg = vehiclePortrait->GetComponent<UIImageLM>();
	}
	if (selectPlayerOne != nullptr && selectPlayerOne->GetComponent<UIImageLM>() != nullptr) {
		_selectPlayerOne = selectPlayerOne->GetComponent<UIImageLM>();
	}
	if (selectPlayerTwo != nullptr && selectPlayerTwo->GetComponent<UIImageLM>() != nullptr) {
		_selectPlayerTwo = selectPlayerTwo->GetComponent<UIImageLM>();
	}

	if (_startGameButton != nullptr) {
		_startGameButton->CallOnClick([this]() {
			AudioSource* aSrc = gameObject->GetComponent<AudioSource>();
			if (aSrc)
				aSrc->Play("Assets/Sounds/Select2.wav");
			ScriptManager::GetInstance()->LoadSceneFromFile("Assets/Scenes/carSelectMenu.lua");
		});
		_startGameButton->SetOnMouseImage("UIPanel2");
		_startGameButton->SetPressedImage("UIPanel3");
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
	//PLAYER SELECT
	if (_selectPlayerOne != nullptr) {
		_selectPlayerOne->CallOnClick([this]() {
			if (playerOneReady) return;
			AudioSource* aSrc = gameObject->GetComponent<AudioSource>();
			if (aSrc)
				aSrc->Play("Assets/Sounds/Select2.wav");
			_selectPlayerOne->SetOnMouseImage("m_PlayerReady");
			_selectPlayerOne->SetPressedImage("m_PlayerReady");
			_selectPlayerOne->SetImage("m_PlayerReady");
			SetPlayerReady(0);
			});
		_selectPlayerOne->SetOnMouseImage("m_PlayerOneSelect01");
		_selectPlayerOne->SetPressedImage("m_PlayerOneSelect01");
	}
	if (_selectPlayerTwo != nullptr) {
		_selectPlayerTwo->CallOnClick([this]() {
			if (playerTwoReady) return;
			AudioSource* aSrc = gameObject->GetComponent<AudioSource>();
			if (aSrc)
				aSrc->Play("Assets/Sounds/Select2.wav");
			_selectPlayerTwo->SetOnMouseImage("m_PlayerReady");
			_selectPlayerTwo->SetPressedImage("m_PlayerReady");
			_selectPlayerTwo->SetImage("m_PlayerReady");
			SetPlayerReady(1);
			});
		_selectPlayerTwo->SetOnMouseImage("m_PlayerTwoSelect01");
		_selectPlayerTwo->SetPressedImage("m_PlayerTwoSelect01");
	}
	//ARROW LEFT
	if (_arrowLeft_Car != nullptr) {
		_arrowLeft_Car->CallOnClick([this]() {
			//Play Sound
			AudioSource* aSrc = gameObject->GetComponent<AudioSource>();
			if (aSrc) aSrc->Play("Assets/Sounds/Select2.wav");
			//Select Next Car
			vehicleIndex++;
			if (vehicleIndex > 1) vehicleIndex = 0;
			ChangeVehicle();
			});

		_arrowLeft_Car->SetOnMouseImage("ArrowLeft01");
		_arrowLeft_Car->SetPressedImage("ArrowLeft01");
	}
	//ARROW RIGHT
	if (_arrowRight_Car != nullptr) {
		_arrowRight_Car->CallOnClick([this]() {
			AudioSource* aSrc = gameObject->GetComponent<AudioSource>();
			//Play Sound
			if (aSrc) aSrc->Play("Assets/Sounds/Select2.wav");
			//Select Previous Car	
			vehicleIndex--;
			if (vehicleIndex < 0) vehicleIndex = 1;
			ChangeVehicle();
			});

		_arrowRight_Car->SetOnMouseImage("ArrowRight01");
		_arrowRight_Car->SetPressedImage("ArrowRight01");
	}
	////PLAYER SELECT ONE
	//if (_playerSelect1Button != nullptr) {
	//	_playerSelect1Button->CallOnClick([this]() {
	//		AudioSource* aSrc = gameObject->GetComponent<AudioSource>();
	//		//Play Sound
	//		if (aSrc) aSrc->Play("Assets/Sounds/Select2.wav");
	//		
	//		_playerSelect1Button->SetOnMouseImage("m_PlayerReady");
	//		_playerSelect1Button->SetOnMouseImage("m_PlayerReady");
	//		_playerSelect1Button->SetPressedImage("m_PlayerReady");
	//		});

	//	_playerSelect1Button->SetOnMouseImage("m_PlayerOneSelect01");
	//	_playerSelect1Button->SetPressedImage("m_PlayerOneSelect01");
	//}
	//if (_playerSelect2Button != nullptr) {
	//	_playerSelect2Button->CallOnClick([this]() {
	//		AudioSource* aSrc = gameObject->GetComponent<AudioSource>();
	//		//Play Sound
	//		if (aSrc) aSrc->Play("Assets/Sounds/Select2.wav");
	//		
	//		_playerSelect2Button->SetOnMouseImage("m_PlayerReady");
	//		_playerSelect2Button->SetOnMouseImage("m_PlayerReady");
	//		_playerSelect2Button->SetPressedImage("m_PlayerReady");
	//		});

	//	_playerSelect2Button->SetOnMouseImage("m_PlayerTwoSelect01");
	//	_playerSelect2Button->SetPressedImage("m_PlayerTwoSelect01");
	//}
}

void JuegoDeAutos::SceneChangeButton::SetPlayerReady(int playerIndex)
{
	if (playerIndex == 0)
	{
		playerOneCarIndex = vehicleIndex;
		playerOneReady = true;
	}
	else
	{
		playerOneCarIndex = vehicleIndex;
		playerTwoReady = true;
	}
	if(playerTwoReady && playerOneReady) 
		ScriptManager::GetInstance()->LoadSceneFromFile("Assets/Scenes/trackSelectMenu.lua");
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

void JuegoDeAutos::SceneChangeButton::ChangeVehicle()
{
	std::string newPortrait = "Portrait_Falcon";
	switch (vehicleIndex){
	
	default: break;
	case 0: newPortrait = "Portrait_Falcon"; break;
	case 1: newPortrait = "Portrait_Eagle"; break;
	//case 2: newPortrait = "Portrait_Flamingo"; break;
	//case 2: newPortrait = "Portrait_Robin"; break;
	}
	std::cout << "\n\nChanging to: " << newPortrait<<vehicleIndex;
	_vehiclePortraitImg->ChangeImage(newPortrait);
}
