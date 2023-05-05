// Motor
#include "LMVector.h"
#include "Scene.h"
#include "GameObject.h"
#include "Transform.h"
#include "UITextLM.h"
#include "LMSpline.h"
#include "MeshRenderer.h"
#include "ScriptManager.h"

// Componentes juego
#include "RaceManager.h"
#include "Checkpoint.h"
#include "PlayerController.h"
#include "AudioSource.h"
#include "EnemyAI.h"

// Extra
#include <algorithm>

using namespace JuegoDeAutos;
using namespace LocoMotor;
const std::string name = "RaceManager";

RaceManager* RaceManager::_instance = nullptr;

RaceManager::SpeedMode RaceManager::speedMode;

RaceManager::RaceManager()
{
	raceCompleted = false;
	fpsCounterUpdated = fpsCounterRefreshRate;
	mainSpline = nullptr;

	if (_instance == nullptr)
	{
		carinfo = std::map<std::string, CarInfo>();
		_instance = this;
	}
	else {
		delete this;
	}

}

RaceManager::~RaceManager()
{
	for (auto& cInfo : carinfo) {

	}
	carinfo.clear();
	mainSpline->ClearAll();
	delete mainSpline;
	mainSpline = nullptr;
	_instance = nullptr;
}

RaceManager* RaceManager::GetInstance()
{
	return _instance;
}

//void RaceManager::Init(std::vector<std::pair<std::string, std::string>>& params)
//{
//	//if (_instance == nullptr)_instance = this;
//	//else delete this;
//}

void RaceManager::InitComponent()
{
	//std::cout << "RaceManager START" << "\n" << "\n" << "\n" << "\n" << "\n";
}

void RaceManager::Init(std::vector<std::pair<std::string, std::string>>& params)
{
	std::cout << "RACEMANAGER INIT" << params.size() << std::endl << std::endl << std::endl;

	//std::string result = checkpointPositions[0];
	//std::cout << " (" << result << ")" << std::endl;

	mainSpline = new Spline();
	CreateCheckpoints(params);


	//LocoMotor::GameObject* prueba = gameObject->GetScene()->AddGameobject("prueba");
	//prueba->AddComponent("Transform");
	//prueba->AddComponent("UITextLM");
	//prueba->GetComponent<UITextLM>()->SetFont("BrunoAce");
	//prueba->GetComponent<UITextLM>()->SetPosition(0, .7);
	//prueba->GetComponent<UITextLM>()->AlignLeft();
	//prueba->GetComponent<UITextLM>()->ChangeText("HUJIAVFENJKAFE");
	//prueba->GetComponent<UITextLM>()->SetSize(0.1, 0.1);
	//prueba->GetComponent<UITextLM>()->SetBottomColor(1, 1, 1);
	//prueba->GetComponent<UITextLM>()->SetTopColor(1, 1, 1);
}

void RaceManager::Start()
{
	std::cout << std::endl << "RACEMANAGER START = gameModeVelocity = " << speedMode
		<< std::endl << std::endl << std::endl << std::endl;

	// Referencias
	//lapsText = gameObject->GetScene()->GetObjectByName("lapsText")->GetComponent<LocoMotor::UITextLM>();
	//positionText = gameObject->GetScene()->GetObjectByName("positionText")->GetComponent<LocoMotor::UITextLM>();
	//timerText = gameObject->GetScene()->GetObjectByName("timerText")->GetComponent<LocoMotor::UITextLM>();
	//countdownText = gameObject->GetScene()->GetObjectByName("countdownText")->GetComponent<LocoMotor::UITextLM>();

	GameObject* lapstxt = gameObject->GetScene()->GetObjectByName("lapsText");
	if (lapsText != nullptr) {
		if (lapstxt->GetComponent<LocoMotor::UITextLM>() != nullptr)
			lapsText = lapstxt->GetComponent<LocoMotor::UITextLM>();
	}
	GameObject* postxt = gameObject->GetScene()->GetObjectByName("positionText");
	if (postxt != nullptr) {
		if (postxt->GetComponent<LocoMotor::UITextLM>() != nullptr)
			positionText = postxt->GetComponent<LocoMotor::UITextLM>();
	}
	GameObject* timetxt = gameObject->GetScene()->GetObjectByName("timerText");
	if (timetxt != nullptr) {
		if (timetxt->GetComponent<LocoMotor::UITextLM>() != nullptr)
			timerText = timetxt->GetComponent<LocoMotor::UITextLM>();
	}
	GameObject* countdtxt = gameObject->GetScene()->GetObjectByName("countdownText");
	if (countdtxt != nullptr) {
		if (countdtxt->GetComponent<LocoMotor::UITextLM>() != nullptr)
			countdownText = countdtxt->GetComponent<LocoMotor::UITextLM>();
	}
	GameObject* laptimertxt = gameObject->GetScene()->GetObjectByName("laptimerText");
	if (laptimertxt != nullptr) {
		if (laptimertxt->GetComponent<LocoMotor::UITextLM>() != nullptr)
			laptimerText = laptimertxt->GetComponent<LocoMotor::UITextLM>();
	}

	
	if (countdownText != nullptr)
		countdownNormalSize = countdownText->GetSizeX();

	ranking.clear();
	RegisterPlayerCar("Player");

	carinfo.at(_playerId).rounds = 0;



	int i = 1;
	while (gameObject->GetScene()->GetObjectByName("EnemyCar0" + std::to_string(i)) != nullptr) {
		std::cout << "EnemyCar0" + std::to_string(i) + " registered" << std::endl;
		RegisterNPCCar("EnemyCar0" + std::to_string(i));
		enemies.push_back(gameObject->GetScene()->GetObjectByName("EnemyCar0" + std::to_string(i)));
		i++;

	}


	if (gameObject->GetScene()->GetObjectByName("coche") != nullptr) {
		player = gameObject->GetScene()->GetObjectByName("coche");
		player->GetComponent<PlayerController>()->SetControllable(false);
	}



	if (gameObject->GetComponent<AudioSource>() != nullptr)
		gameObject->GetComponent<AudioSource>()->Set2D();

	//NO QUITAR AUN HASTA QUE ESTE LA SPLINE
	std::vector<GameObject*> waypointBalls = std::vector<GameObject*>();
	int maxBalls = 100;
	std::vector<std::pair<std::string, std::string>> pares = std::vector<std::pair<std::string, std::string>>();
	pares.push_back({ "file", "SphereDebug.mesh" });
	for (float i = 1; i < maxBalls; i++) {
		auto wayPointNew = gameObject->GetScene()->AddGameobject("WayPointProc" + std::to_string(i));
		wayPointNew->AddComponent("Transform");
		wayPointNew->AddComponent("MeshRenderer", pares);
		wayPointNew->GetComponent<MeshRenderer>()->PreStart();
		//nuevaSpl->RecalcTangents();
		waypointBalls.push_back(wayPointNew);
	}
	for (int i = 1; i < waypointBalls.size(); i++) {
		waypointBalls[i]->SetScale(LMVector3(3.0f, 3.0f, 3.0f));
		waypointBalls[i]->SetPosition(mainSpline->Interpolate((float)i / maxBalls));
	}
}

void RaceManager::Update(float dt)
{
	// Actualizar la posicion de todos los coches enemigos (la del player se hace desde el propio script de PlayerController)

	//GameObject* enemy = enemies[0];
	//UpdateCarPosition("Enemy0", enemy->GetTransform()->GetPosition());
	//UpdateCarPosition("Enemy1", enemy->GetTransform()->GetPosition());

	//std::cout << "RACEMANAGER INFO : " << "\n" << "\n" << "\n" << "\n" << "\n";

	// Comprobar si algun coche ha llegado a algun checkpoint
	// En caso afirmativo, notificarlo


	if (HasCarReachedCheckpoint(_playerId))
		CheckpointReached(_playerId);

	//if (HasCarReachedCheckpoint("Enemy0"))
	//	CheckpointReached("Enemy0");

	//if (HasCarReachedCheckpoint("Enemy1"))
	//	CheckpointReached("Enemy1");


	//for (size_t i = 0; i < enemies.size(); i++)
	//{
	//	std::string enemyId = "Enemy" + std::to_string(i);

	//	//if (HasCarReachedCheckpoint(enemyId)){}
	//		//CheckpointReached(enemyId);
	//}


	UpdateRanking();

	// Update Laps Text
	if (lapsText != nullptr) {
		std::string s = std::to_string(carinfo.at(_playerId).rounds) + " / 3";
		lapsText->ChangeText(s);
	}

	// Update Countdown
	if (countdownText != nullptr) {
		if (countdownTimer > -1) {
			countdownTimer -= dt * timeConstant;
			countDownSeconds = (int)floor(countdownTimer);

			if (countDownSeconds != countDownSecondsLastFrame && countDownSeconds != -1)
				CountdownUIChanged();

			if (countDownSeconds == 0 || countDownSeconds == -1) {
				countdownFinished = true;
				countdownText->SetBottomColor(0, 1, 0);
				countdownText->ChangeText("GO!");
				if (player != nullptr)
					player->GetComponent<PlayerController>()->SetControllable(true);
				if (enemies.size() > 0)
					for (size_t i = 0; i < enemies.size(); i++) {
						EnemyAI* ai = enemies[i]->GetComponent<EnemyAI>();
						if(ai)
							ai->Activate();
					}
						

			}
			else if (countDownSeconds > 0 && countDownSeconds <= 3) {
				std::string countdownNumber = std::to_string(countDownSeconds);
				countdownText->ChangeText(countdownNumber);

				if (countDownSeconds == 3) {
					if (countDownSeconds != countDownSecondsLastFrame && gameObject->GetComponent<AudioSource>() != nullptr) gameObject->GetComponent<AudioSource>()->Play("Assets/Sounds/Final_03.wav");
					countdownText->SetTopColor(1, 0, 0);
					countdownText->SetBottomColor(0, 0, 0);
				}
				else if (countDownSeconds == 2) {
					if (countDownSeconds != countDownSecondsLastFrame && gameObject->GetComponent<AudioSource>() != nullptr) gameObject->GetComponent<AudioSource>()->Play("Assets/Sounds/Final_02.wav");
					countdownText->SetTopColor(1, .5, 0);
					countdownText->SetBottomColor(1, 0, 0);
				}
				else if (countDownSeconds == 1) {
					if (countDownSeconds != countDownSecondsLastFrame && gameObject->GetComponent<AudioSource>() != nullptr) gameObject->GetComponent<AudioSource>()->Play("Assets/Sounds/Final_01.wav");
					countdownText->SetTopColor(1, 1, 0);
					countdownText->SetBottomColor(1, .5, 0);
				}
			}
			else countdownText->ChangeText("");


			countDownSecondsLastFrame = countDownSeconds;
		}

		// Animating text
		if (countdownAnimating) {

			if (countdownCurrentSize < countdownNormalSize) {
				countdownCurrentSize += dt * timeConstant;
				countdownText->SetSize(countdownCurrentSize, countdownCurrentSize);
			}
			else
				countdownAnimating = false;
		}
	}

	if (fpsCounterUpdated < fpsCounterRefreshRate)fpsCounterUpdated += dt * timeConstant;
	else {
		fpsCounterUpdated = 0;
		UITextLM* fps = gameObject->GetComponent<UITextLM>();
		if (fps != nullptr)
			fps->ChangeText(std::to_string(1000 / ((int)dt+1)) + " fps");
	}

	//Si termina la carrera a los 3 segundos te envia al menu
	if (raceCompleted) {
		if (endTimerStart < 0) {
			endTimerStart = dt * timeConstant;
		}
		else {
			endTimerCurrent += dt * timeConstant;
			if (endTimerCurrent - endTimerStart > 3 && !ended) {
				ended = true;
				ScriptManager::GetInstance()->LoadSceneFromFile("Assets/Scenes/menu.lua");
			}

		}
	}


	// Update timer
	UpdateTimer(dt);
}

void RaceManager::CreateCheckpoints(std::vector<std::pair<std::string, std::string>>& params)
{
	std::cout << "CHECKPOINT DEBUG" << std::endl << std::endl
		<< std::endl << std::endl << std::endl << std::endl;

	// Comprobar si los datos introducidos desde LUA son validos
	// Informar de los datos mal declarados en LUA y solo tener en cuenta los buenos
#pragma region Comprobar Datos Validos
	std::vector<std::pair<std::string, std::string>> checkpointPositions_pairs;
	for (size_t i = 0; i < params.size(); i++) {
		std::string name = params[i].first;
		char checkpointNumber = name[name.size() - 1];
		//name.erase(name.size() - 1, 1); // elimina el �ltimo car�cter

		std::string checkName = name.substr(0, 10);
		std::string checkpointNumber_ = name.substr(10);
		std::cout << "checkpointNumber = " << checkpointNumber_ << std::endl << std::endl;

		if (checkName == "checkpoint") {

			try {
				if (!IsInt(checkpointNumber_))
					throw std::invalid_argument("Numero de checkpoint no valido");
				checkpointPositions_pairs.push_back(params[i]);
			}
			catch (std::invalid_argument& e) {
				std::cerr << "Error: " << e.what() << std::endl;
			}
		}
	}
#pragma endregion


	// Ordenar las posiciones de los checkpoints
	std::sort(checkpointPositions_pairs.begin(), checkpointPositions_pairs.end(), [](const auto& a, const auto& b) {
		int one = std::stoi(a.first.substr(10));
	int two = std::stoi(b.first.substr(10));
	return one < two;
		});


#pragma region Convertir Coordenadas
	// Convertir las coordenadas de strings a LMVector3
	//mainSpline->SetAutoCalc(true);
	for (size_t i = 0; i < checkpointPositions_pairs.size(); i++)
	{
		LMVector3 result = LMVector3::StringToVector(checkpointPositions_pairs[i].second);
		//Add points to Spline
		mainSpline->AddPoint(result * 20);
		RegisterCheckpointPosition(result * 20);
	}
#pragma endregion


	std::cout << "CHECKPOINTS = " << _checkpoints.size() << std::endl;
	for (size_t i = 0; i < _checkpoints.size(); i++)
	{
		LMVector3 result = _checkpoints[i];
		std::cout << "Checkpoint_" << i << " = (" << result.GetX()
			<< ", " << result.GetY() << ", " << result.GetZ() << ")" << std::endl;
	}
}

bool RaceManager::IsInt(const std::string& str) {
	try {
		std::stoi(str);
		return true;
	}
	catch (const std::exception&) {
		return false;
	}
}

void RaceManager::RegisterCheckpointPosition(LMVector3 checkpointPos)
{
	_checkpoints.push_back(checkpointPos);
}

void RaceManager::RegisterPlayerCar(std::string carId)
{
	CarInfo carInfo = { 0,0,  LMVector3() };
	carinfo.insert(std::pair<std::string, CarInfo>(carId, carInfo));
	//ranking.push_back(carId);
	_playerId = carId;
}

void RaceManager::RegisterNPCCar(std::string carId)
{
	CarInfo carInfo = { 0,0,  LMVector3() };

	carinfo.insert(std::pair<std::string, CarInfo>(carId, carInfo));
	ranking.push_back(carId);
}

void RaceManager::UpdateCarPosition(std::string carId, LMVector3 newPosition)
{
	//std::cout << "carId = " << carId;

	carinfo.at(carId).position.SetX(newPosition.GetX());
	carinfo.at(carId).position.SetY(newPosition.GetY());
	carinfo.at(carId).position.SetZ(newPosition.GetZ());
}

bool RaceManager::HasCarReachedCheckpoint(std::string carId)
{
	int checkpointIndex = carinfo.at(carId).currentCheckpoint;

	LMVector3 targetCheckpointPosition = _checkpoints[checkpointIndex];
	LMVector3 carPosition = carinfo.at(carId).position;

	float distance = (targetCheckpointPosition - carPosition).Magnitude();


	if (carId == _playerId) {
		std::cout << "PlayerCheckpointIndex = " << checkpointIndex << std::endl;
		std::cout << "PlayerDistance = " << distance << std::endl;
		std::cout << "PlayerRounds = " << carinfo.at(carId).rounds << std::endl;
	}

	//std::cout << "DISTANCE TO NEXT CHECKPOINT " << distance << "\n";
	//std::cout << "GO TO CHECKPOINT NUMBER " << carinfo.at(_playerId).currentCheckpoint << "\n";
	if (distance < 300)
		return true;
	else
		return false;
}

void RaceManager::CheckpointReached(std::string carId)
{
	//std::cout << "CheckpointReached ";

	carinfo.at(carId).currentCheckpoint++;
	std::cout << "Car " << carId << " reached checkpoint " << carinfo.at(carId).currentCheckpoint << std::endl;
	if (carinfo.at(carId).currentCheckpoint >= _checkpoints.size()) {
		carinfo.at(carId).currentCheckpoint = 0;
		carinfo.at(carId).rounds++;

		float thislapTime = currentTime - lastlapTime;
		if (thislapTime < bestlapTime)
			bestlapTime = thislapTime;
		lastlapTime = currentTime;

		int min, sec, mil;
		SecondsToTimer(bestlapTime, min, sec, mil);
		std::string s = NumToString(min, 2)
			+ ":" + NumToString(sec, 2)
			+ ":" + NumToString(mil, 3);
		laptimerText->ChangeText(s);

		if (carId == _playerId && carinfo.at(carId).rounds >= _totalRounds)
			OnRaceFinished();

		else if (carId == _playerId && carinfo.at(carId).rounds >= _totalRounds - 1)
			OnLastLap();
	}
	// Actualizar el siguiente checkpoint
}

LMVector3 RaceManager::GetPlayerLastCheckpointPosition()
{
	int checkpointIndex = carinfo.at(_playerId).currentCheckpoint;

	if (checkpointIndex > 62 && checkpointIndex < 75)
		checkpointIndex = 62;

	checkpointIndex--;
	if (checkpointIndex < 0)
		checkpointIndex = _checkpoints.size() - 1;

	return _checkpoints[checkpointIndex];
}

LocoMotor::Spline* JuegoDeAutos::RaceManager::GetSpline()
{
	return mainSpline;
}

void RaceManager::UpdateRanking()
{
	if (positionText == nullptr)
		return;

	// Saber cuantos coches tiene por delante el player
	int carsAhead = 0;

	// Que coches estan justo en la misma ronda que el jugador y cuantos estan por delante
	std::vector<std::string> carsInSameRound;

	int playerRounds = carinfo.at(_playerId).rounds;

	for (size_t i = 0; i < ranking.size(); i++)
	{
		std::string enemyName = ranking[i];

		int enemyRound = carinfo.at(enemyName).rounds;

		// Si va por delante, a�adirlo a coches que van por delante directamente
		if (enemyRound > playerRounds)
			carsAhead++;

		// Si va en la misma ronda, guardar su nombre para comprobar mas tarde los checkpoints
		else if (enemyRound == playerRounds)
			carsInSameRound.push_back(enemyName);
	}

	// Que coches estan justo en el mismo checkpoint que el jugador y cuantos estan por delante
	std::vector<std::string> carsInSameCheckpoint;

	int playerCheckpoint = carinfo.at(_playerId).currentCheckpoint;

	for (size_t i = 0; i < carsInSameRound.size(); i++)
	{
		std::string enemyName = carsInSameRound[i];

		int enemyCheckpoint = carinfo.at(enemyName).currentCheckpoint;

		// Si va por delante, a�adirlo a coches que van por delante directamente
		if (enemyCheckpoint > playerCheckpoint)
			carsAhead++;

		// Si va en la misma ronda, guardar su nombre para comprobar mas tarde los checkpoints
		else if (enemyCheckpoint == playerCheckpoint)
			carsInSameCheckpoint.push_back(enemyName);
	}


	//std::cout << "CARS IN SAME CHECKPOINT = " << std::endl;
	//for (size_t i = 0; i < carsInSameCheckpoint.size(); i++)
	//	std::cout << i << " = " << carsInSameCheckpoint[i] << std::endl;

	// Entre los coches que estan en el mismo checkpoint calcular usando distancias cuantos coches estan por delante del jugador

	LMVector3 playerPos = carinfo.at(_playerId).position;
	LMVector3 checkpointPos = _checkpoints[playerCheckpoint];
	double playerDistanceToCheckpoint = (playerPos - checkpointPos).Magnitude();

	for (size_t i = 0; i < carsInSameCheckpoint.size(); i++)
	{
		std::string enemyName = carsInSameCheckpoint[i];

		LMVector3 enemyPos = carinfo.at(enemyName).position;
		LMVector3 enemyCheckpointPos = _checkpoints[carinfo.at(enemyName).currentCheckpoint];
		double enemyDistanceToCheckpoint = (enemyPos - enemyCheckpointPos).Magnitude();

		// Si va por delante, a�adirlo a coches que van por delante directamente
		if (enemyDistanceToCheckpoint < playerDistanceToCheckpoint)
			carsAhead++;
	}


	// Posicion del jugador respecto al resto de coches en la carrera
	playerRacePos = carsAhead + 1;
	//for (int i = 0; i < ranking.size(); i++)
	//	if (ranking[i] == _playerId)
	//		playerPos = i;

	std::string positionString = std::to_string(playerRacePos);

	if (playerRacePos == 1)
		positionString += "st";
	else if (playerRacePos == 2)
		positionString += "nd";
	else if (playerRacePos == 3)
		positionString += "rd";
	else
		positionString += "th";

	positionText->ChangeText(positionString);


	//std::cout << "CURRENTPOSITION = " << positionString << std::endl;
}

void RaceManager::CountdownUIChanged()
{
	
	countdownAnimating = true;
	countdownCurrentSize = 0;
	if(countdownText)
	countdownText->SetSize(0, 0);
}

void RaceManager::UpdateTimer(float dt)
{
	if (!countdownFinished) return;

	currentTime += dt * 0.001;

	int min, sec, mil;
	SecondsToTimer(currentTime, min, sec, mil);
	std::string s = NumToString(min, 2)
		+ ":" + NumToString(sec, 2)
		+ ":" + NumToString(mil, 3);
	//std::string s = std::to_string(min)
	//	+ ":" + std::to_string(sec)
	//	+ ":" + std::to_string(mil);
	if(timerText)
	timerText->ChangeText(s);
}

void RaceManager::SecondsToTimer(float _sec, int& min, int& sec, int& mil)
{
	min = floor(_sec / 60);
	sec = floor(_sec - min * 60);

	double entero;
	double fraccion = std::modf(_sec, &entero);
	mil = static_cast<int>(std::round(fraccion * 1000.0));
}

std::string RaceManager::NumToString(int num, int numZeros) {

	std::string s;

	if (numZeros == 2) {
		if (num < 10)
			s = "0" + std::to_string(num);
		else
			s = std::to_string(num);
	}
	else if (numZeros == 3) {

		if (num < 100)
			s = "0" + std::to_string(num);
		else if (num < 10)
			s = "00" + std::to_string(num);
		else
			s = std::to_string(num);
	}

	return s;
}

bool RaceManager::HasCountDownFinished()
{
	return countdownFinished;
}

void RaceManager::OnLastLap() {
	if (gameObject->GetComponent<AudioSource>() != nullptr)
		gameObject->GetComponent<AudioSource>()->SetFreq(1.5f);
}

float RaceManager::GetSpeed() {
	return speeds[speedMode];
}

void RaceManager::OnRaceFinished() {
	raceCompleted = true;
	if (player != nullptr)
		player->GetComponent<PlayerController>()->SetControllable(false);

	if (countdownText) {
		countdownText->ChangeText(std::to_string(playerRacePos));
		countdownText->SetSize(countdownNormalSize * 1.5f, countdownNormalSize * 1.5f);
	}
	
}