#include "SceneChangeButton.h"
#include "GameObject.h"
#include "RaceManager.h"
#include "Scene.h"
#include "UIImageLM.h"
#include "UITextLM.h"
#include "ScriptManager.h"
#include "MeshRenderer.h"
#include "AudioSource.h"

using namespace LocoMotor;
JuegoDeAutos::SceneChangeButton::SceneChangeButton()
{
	_onePlayerButton = nullptr;
	_twoPlayerButton = nullptr;
	_startGameButton = nullptr;
	_goToIntroButton = nullptr;
	_arrowLeft_Car = nullptr;
	_arrowRight_Car = nullptr;
	_vehiclePortraitImg = nullptr;
	_selectPlayerOne = nullptr;
	_selectPlayerTwo = nullptr;
	_trackPortraitImg = nullptr;
	_selectTrackButton = nullptr;
	vehicleIndex = 0;
	trackIndex = 0;
}

JuegoDeAutos::SceneChangeButton::~SceneChangeButton()
{
	_onePlayerButton = nullptr;
	_twoPlayerButton = nullptr;
	_startGameButton = nullptr;
	_goToIntroButton = nullptr;
	_vehicleInfoPanel = nullptr;
	_vehiclePortraitImg = nullptr;
	_selectPlayerOne = nullptr;
	_selectPlayerTwo = nullptr;
	_trackPortraitImg = nullptr;
	_trackArrowRightButton = nullptr;
	_trackArrowLeftButton = nullptr;
	_selectTrackButton = nullptr;
}

void JuegoDeAutos::SceneChangeButton::Start()
{
	vehicleIndex = 0;
	trackIndex = 0;
	//Declare Buttons to add callbacks to
	GameObject* startGameButton = gameObject->GetScene()->GetObjectByName("startButton");
	//INTRO
	GameObject* onePlayerButton = gameObject->GetScene()->GetObjectByName("OnePlayerButton");
	GameObject* twoPlayerButton = gameObject->GetScene()->GetObjectByName("TwoPlayerButton");
	//CAR SELECTION
	GameObject* selectCarButton = gameObject->GetScene()->GetObjectByName("selectVehicleButton");
	GameObject* goToIntroButton = gameObject->GetScene()->GetObjectByName("goToIntroButton");
	GameObject* vehicleInfoPanel = gameObject->GetScene()->GetObjectByName("carInfoPanel");
	GameObject* vehiclePortrait = gameObject->GetScene()->GetObjectByName("Vehicle_Portrait");
	GameObject* arrowLeft_Car = gameObject->GetScene()->GetObjectByName("arrowLeftButton");
	GameObject* arrowRight_Car = gameObject->GetScene()->GetObjectByName("arrowRightButton");
	GameObject* selectPlayerOne = gameObject->GetScene()->GetObjectByName("selectPlayerOne");
	GameObject* selectPlayerTwo = gameObject->GetScene()->GetObjectByName("selectPlayerTwo");
	//TRACK SELECTION
	GameObject* trackPreview00 = gameObject->GetScene()->GetObjectByName("trackMesh00");
	GameObject* trackPreview01 = gameObject->GetScene()->GetObjectByName("trackMesh01");
	GameObject* trackArrowRightButton = gameObject->GetScene()->GetObjectByName("trackArrowRightButton");
	GameObject* trackArrowLeftButton = gameObject->GetScene()->GetObjectByName("trackArrowLeftButton");
	GameObject* trackPortraitImg = gameObject->GetScene()->GetObjectByName("Portrait_Track");
	GameObject* selectTrackButton = gameObject->GetScene()->GetObjectByName("selectTrackButton");

	//Get Components
	if (onePlayerButton != nullptr && onePlayerButton->GetComponent<UIImageLM>() != nullptr) {
		_onePlayerButton = onePlayerButton->GetComponent<UIImageLM>();
	}
	if (twoPlayerButton != nullptr && twoPlayerButton->GetComponent<UIImageLM>() != nullptr) {
		_twoPlayerButton = twoPlayerButton->GetComponent<UIImageLM>();
	}
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
	if (vehicleInfoPanel != nullptr && vehicleInfoPanel->GetComponent<UIImageLM>() != nullptr) {
		_vehicleInfoPanel = vehicleInfoPanel->GetComponent<UIImageLM>();
	}
	if (selectPlayerOne != nullptr && selectPlayerOne->GetComponent<UIImageLM>() != nullptr) {
		_selectPlayerOne = selectPlayerOne->GetComponent<UIImageLM>();
	}
	if (selectPlayerTwo != nullptr && selectPlayerTwo->GetComponent<UIImageLM>() != nullptr) {
		_selectPlayerTwo = selectPlayerTwo->GetComponent<UIImageLM>();
	}
	//TRACKS
	if (trackPreview00 != nullptr && trackPreview00->GetComponent<MeshRenderer>() != nullptr) {
		trackMesh00 = trackPreview00->GetComponent<MeshRenderer>();
	}
	if (trackPreview01 != nullptr && trackPreview01->GetComponent<MeshRenderer>() != nullptr) {
		trackMesh01 = trackPreview01->GetComponent<MeshRenderer>();
	}
	if (trackArrowRightButton != nullptr && trackArrowRightButton->GetComponent<UIImageLM>() != nullptr) {
		_trackArrowRightButton = trackArrowRightButton->GetComponent<UIImageLM>();
	}
	if (trackArrowLeftButton != nullptr && trackArrowLeftButton->GetComponent<UIImageLM>() != nullptr) {
		_trackArrowLeftButton = trackArrowLeftButton->GetComponent<UIImageLM>();
	}
	if (trackPortraitImg != nullptr && trackPortraitImg->GetComponent<UIImageLM>() != nullptr) {
		_trackPortraitImg = trackPortraitImg->GetComponent<UIImageLM>();
	}
	if (selectTrackButton != nullptr && selectTrackButton->GetComponent<UIImageLM>() != nullptr) {
		_selectTrackButton = selectTrackButton->GetComponent<UIImageLM>();
	}
	//PLAYER BUTTON INTRO
	if (_onePlayerButton != nullptr) {
		_onePlayerButton->CallOnClick([this]() {
			AudioSource* aSrc = gameObject->GetComponent<AudioSource>();
			if (aSrc)
				aSrc->Play("Assets/Sounds/Select2.wav");
			RaceManager::GetInstance()->numberOfPlayer = 1;
			ScriptManager::GetInstance()->LoadSceneFromFile("Assets/Scenes/carSelectMenu.lua");
			});
		_onePlayerButton->SetOnMouseImage("m_OnePlayerButton01");
		_onePlayerButton->SetPressedImage("m_OnePlayerButton01");
	}
	if (_twoPlayerButton != nullptr) {
		_twoPlayerButton->CallOnClick([this]() {
			AudioSource* aSrc = gameObject->GetComponent<AudioSource>();
			if (aSrc)
				aSrc->Play("Assets/Sounds/Select2.wav");
			RaceManager::GetInstance()->numberOfPlayer = 2;
			SetUIVisibility();
			ScriptManager::GetInstance()->LoadSceneFromFile("Assets/Scenes/carSelectMenu.lua");
			});
		_twoPlayerButton->SetOnMouseImage("m_TwoPlayerButton01");
		_twoPlayerButton->SetPressedImage("m_TwoPlayerButton01");
	}

	if (_goToIntroButton != nullptr) {
		_goToIntroButton->CallOnClick([this]() {
			AudioSource* aSrc = gameObject->GetComponent<AudioSource>();
			if (aSrc)
				aSrc->Play("Assets/Sounds/Select2.wav");

			ScriptManager::GetInstance()->LoadSceneFromFile("Assets/Scenes/intro.lua");
			/*if (sceneType == SCENE_TYPE::CAR_SELECT)
				ScriptManager::GetInstance()->LoadSceneFromFile("Assets/Scenes/intro.lua");
			else if (sceneType == SCENE_TYPE::TRACK_SELECT)
			{
				//Reset Values and Go Back
				ResetValues();
				sceneType = SCENE_TYPE::CAR_SELECT;
				playerOneReady = false;
				playerTwoReady = false;
				vehicleIndex = 0;
				trackIndex = 0;
				SetUIVisibility();
			}*/
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
			vehicleIndex--;
			if (vehicleIndex < 0) vehicleIndex = 4;
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
			vehicleIndex++;
			if (vehicleIndex > 4) vehicleIndex = 0;
			ChangeVehicle();
			});

		_arrowRight_Car->SetOnMouseImage("ArrowRight01");
		_arrowRight_Car->SetPressedImage("ArrowRight01");
	}
	//TRACK ARROW LEFT
	if (_trackArrowLeftButton != nullptr) {
		_trackArrowLeftButton->CallOnClick([this]() {
			AudioSource* aSrc = gameObject->GetComponent<AudioSource>();
			//Play Sound
			if (aSrc) aSrc->Play("Assets/Sounds/Select2.wav");
			trackIndex--;
			if (trackIndex < 0) trackIndex = 1;
			ChangeTrack();
			});

		_trackArrowLeftButton->SetOnMouseImage("ArrowLeft01");
		_trackArrowLeftButton->SetPressedImage("ArrowLeft01");
	}
	//TRACK ARROW RIGHT
	if (_trackArrowRightButton != nullptr) {
		_trackArrowRightButton->CallOnClick([this]() {
			AudioSource* aSrc = gameObject->GetComponent<AudioSource>();
			//Play Sound
			if (aSrc) aSrc->Play("Assets/Sounds/Select2.wav");
			trackIndex++;
			if (trackIndex > 1) trackIndex = 0;
			ChangeTrack();
			});

		_trackArrowRightButton->SetOnMouseImage("ArrowRight01");
		_trackArrowRightButton->SetPressedImage("ArrowRight01");
	}
	if (selectTrackButton != nullptr) {
		_selectTrackButton->CallOnClick([this]() {
			AudioSource* aSrc = gameObject->GetComponent<AudioSource>();
			if (aSrc)
				aSrc->Play("Assets/Sounds/Select2.wav");

			if (trackIndex == 1)
				ScriptManager::GetInstance()->LoadSceneFromFile("Assets/Scenes/SalaDebug.lua");
			if(RaceManager::numberOfPlayer == 1)
				ScriptManager::GetInstance()->LoadSceneFromFile("Assets/Scenes/testAreaDos.lua");
			else 
				ScriptManager::GetInstance()->LoadSceneFromFile("Assets/Scenes/testArea.lua");
			});
		_selectTrackButton->SetOnMouseImage("m_selectSelected");
		_selectTrackButton->SetPressedImage("m_selectSelected");
	}
	sceneType = SCENE_TYPE::CAR_SELECT;
	SetUIVisibility();
}

void JuegoDeAutos::SceneChangeButton::SetUIVisibility()
{
	//SCENE VISIBILITY
	if (_vehiclePortraitImg != nullptr) _vehiclePortraitImg->SetVisibility(sceneType == SCENE_TYPE::CAR_SELECT);
	if (_vehicleInfoPanel != nullptr) _vehicleInfoPanel->SetVisibility(sceneType == SCENE_TYPE::CAR_SELECT);
	if (_selectPlayerOne != nullptr) _selectPlayerOne->SetInteractive(sceneType == SCENE_TYPE::CAR_SELECT);
	if (_selectPlayerTwo != nullptr) _selectPlayerTwo->SetInteractive(sceneType == SCENE_TYPE::CAR_SELECT);
	if (_arrowLeft_Car != nullptr) _arrowLeft_Car->SetInteractive(sceneType == SCENE_TYPE::CAR_SELECT);
	if (_arrowRight_Car != nullptr) _arrowRight_Car->SetInteractive(sceneType == SCENE_TYPE::CAR_SELECT);
	//TRACK
	if (_selectTrackButton != nullptr) _selectTrackButton->SetInteractive(sceneType == SCENE_TYPE::TRACK_SELECT);
	if (_trackArrowRightButton != nullptr) _trackArrowRightButton->SetInteractive(sceneType == SCENE_TYPE::TRACK_SELECT);
	if (_trackArrowLeftButton != nullptr) _trackArrowLeftButton->SetInteractive(sceneType == SCENE_TYPE::TRACK_SELECT);
	if (_trackPortraitImg != nullptr) _trackPortraitImg->SetVisibility(sceneType == SCENE_TYPE::TRACK_SELECT);
	if (trackMesh00 != nullptr) trackMesh00->SetVisible(sceneType == SCENE_TYPE::TRACK_SELECT);
	//Car Selection
	if (_selectPlayerTwo != nullptr) _selectPlayerTwo->SetInteractive(RaceManager::numberOfPlayer == 2 && sceneType == SCENE_TYPE::CAR_SELECT);
	if (_selectPlayerOne != nullptr)
	{
		if(RaceManager::numberOfPlayer == 1) _selectPlayerOne->SetPosition(0.7f, 0.74f);
		_selectPlayerOne->SetInteractive(sceneType == SCENE_TYPE::CAR_SELECT);
	}
}
void JuegoDeAutos::SceneChangeButton::SetPlayerReady(int playerIndex)
{
	if (vehicleIndex >= 4) vehicleIndex = rand() % (3 - 0 + 1) + 0;
	if (playerIndex == 0)
	{
		playerOneReady = true;
		RaceManager::CarModel aux = (RaceManager::CarModel)vehicleIndex;
		RaceManager::carModelPlayerOne = aux;
	}
	else
	{
		playerTwoReady = true;
		RaceManager::CarModel aux = (RaceManager::CarModel)vehicleIndex;
		RaceManager::carModelPlayerTwo = aux;
	}
	//ONE PLAYER
	if ((RaceManager::numberOfPlayer == 1 && playerOneReady) || (playerTwoReady && playerOneReady))
		//ScriptManager::GetInstance()->LoadSceneFromFile("Assets/Scenes/trackSelectMenu.lua");
		sceneType = SCENE_TYPE::TRACK_SELECT;
		SetUIVisibility();
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
	switch (vehicleIndex)
	{
	default: break;
	case 0: newPortrait = "Portrait_Falcon"; _vehicleInfoPanel->ChangeImage("m_carInfoPanelFalcon"); break;
	case 1: newPortrait = "Portrait_Eagle"; _vehicleInfoPanel->ChangeImage("m_carInfoPanelEagle"); break;
	case 2: newPortrait = "Portrait_Pelican"; _vehicleInfoPanel->ChangeImage("m_carInfoPanelPelican"); break;
	case 3: newPortrait = "Portrait_Flamingo"; _vehicleInfoPanel->ChangeImage("m_carInfoPanelFlamingo"); break;
	case 4: newPortrait = "Portrait_Generic"; _vehicleInfoPanel->ChangeImage("m_carInfoPanelGeneric"); break;
	}
	_vehiclePortraitImg->ChangeImage(newPortrait);
}

void JuegoDeAutos::SceneChangeButton::ChangeTrack()
{
	//Change IMAGE
	std::string newPortrait = trackIndex == TRACK_TYPE::CIRCUITO_PLAYA ? "Portrait_TrackOne" : "Portrait_TrackTwo";
	_trackPortraitImg->ChangeImage(newPortrait);

	//Esta hecho con el culo pero arrays/listas petan en cambio de escena yalosiento equisde
	if (trackIndex == TRACK_TYPE::CIRCUITO_PLAYA)
	{
		trackMesh00->SetVisible(true);
		trackMesh01->SetVisible(false);
	}
	else if(trackIndex == TRACK_TYPE::SALA_DEBUG)
	{
		trackMesh00->SetVisible(false);
		trackMesh01->SetVisible(true);
	}
}

void JuegoDeAutos::SceneChangeButton::ResetValues()
{
	sceneType = SCENE_TYPE::CAR_SELECT;
	playerOneReady = false;
	playerTwoReady = false;
	vehicleIndex = 0;
	trackIndex = 0;
	_selectPlayerOne->SetImage("m_PlayerOneSelect00");
	_selectPlayerTwo->SetImage("m_PlayerTwoSelect00");
}
