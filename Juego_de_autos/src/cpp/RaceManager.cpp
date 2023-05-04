// Motor
#include "LMVector.h"
#include "Scene.h"
#include "GameObject.h"
#include "Transform.h"
#include "UITextLM.h"
#include "LMSpline.h"

// Componentes juego
#include "RaceManager.h"
#include "Checkpoint.h"
#include "PlayerController.h"
#include "AudioSource.h"

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
	lapsText = gameObject->GetScene()->GetObjectByName("lapsText")->GetComponent<LocoMotor::UITextLM>();
	positionText = gameObject->GetScene()->GetObjectByName("positionText")->GetComponent<LocoMotor::UITextLM>();
	timerText = gameObject->GetScene()->GetObjectByName("timerText")->GetComponent<LocoMotor::UITextLM>();
	countdownText = gameObject->GetScene()->GetObjectByName("countdownText")->GetComponent<LocoMotor::UITextLM>();
	if (countdownText != nullptr)
		countdownNormalSize = countdownText->GetSizeX();

	gameObject->GetScene()->GetObjectByName("coche")
		->GetComponent<JuegoDeAutos::PlayerController>()->SetAcceleration(speeds[speedMode]);

	ranking.clear();
	RegisterPlayerCar("Player");

	carinfo.at(_playerId).rounds = 0;

	return;

	RegisterNPCCar("Enemy0");
	RegisterNPCCar("Enemy1");


	GameObject* enemy = gameObject->GetScene()->GetObjectByName("Enemy0");
	enemies.push_back(enemy);

	enemy = gameObject->GetScene()->GetObjectByName("Enemy1");
	enemies.push_back(enemy);

	if (gameObject->GetComponent<AudioSource>() != nullptr)
		gameObject->GetComponent<AudioSource>()->Set2D();
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
			}
			else if (countDownSeconds > 0 && countDownSeconds <= 3) {
				std::string countdownNumber = std::to_string(countDownSeconds);
				countdownText->ChangeText(countdownNumber);

				if (countDownSeconds == 3) {
					countdownText->SetTopColor(1, 0, 0);
					countdownText->SetBottomColor(0, 0, 0);
				}
				else if (countDownSeconds == 2) {
					countdownText->SetTopColor(1, .5, 0);
					countdownText->SetBottomColor(1, 0, 0);
				}
				else if (countDownSeconds == 1) {
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
			fps->ChangeText(std::to_string(1000 / (int)dt) + " fps");
	}


	// Update timer
	UpdateTimer(dt);
}

void RaceManager::CreateCheckpoints(std::vector<std::pair<std::string, std::string>>& params)
{

	// Comprobar si los datos introducidos desde LUA son validos
	// Informar de los datos mal declarados en LUA y solo tener en cuenta los buenos
#pragma region Comprobar Datos Validos
	std::vector<std::pair<std::string, std::string>> checkpointPositions_pairs;
	for (size_t i = 0; i < params.size(); i++) {
		std::string name = params[i].first;
		char checkpointNumber = name[name.size() - 1];
		name.erase(name.size() - 1, 1); // elimina el �ltimo car�cter
		if (name == "checkpoint") {

			try {
				if (!isdigit(checkpointNumber))
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
		return a.first.back() < b.first.back();
		});


#pragma region Convertir Coordenadas
	// Convertir las coordenadas de strings a LMVector3
	mainSpline->SetAutoCalc(true);
	for (size_t i = 0; i < checkpointPositions_pairs.size(); i++)
	{
		LMVector3 result = LMVector3::StringToVector(checkpointPositions_pairs[i].second);
		//Add points to Spline
		mainSpline->AddPoint(result * 20);
		RegisterCheckpointPosition(result);
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

bool RaceManager::Compare(const std::pair<std::string, std::string>& p1, const std::pair<std::string, std::string>& p2) {
	std::string s1 = p1.first;
	std::string s2 = p2.first;
	char last_char_s1 = s1.back(); // obtiene el �ltimo car�cter de la cadena s1
	char last_char_s2 = s2.back(); // obtiene el �ltimo car�cter de la cadena s2
	return last_char_s1 < last_char_s2; // compara los �ltimos caracteres de las cadenas
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


	//if (carId == "Enemy1") {
	//	std::cout << "Enemy1CheckpointIndex = " << checkpointIndex << std::endl;
	//	std::cout << "Enemy1Distance = " << distance << std::endl;
	//	std::cout << "Enemy1Rounds = " << carinfo.at(carId).rounds << std::endl;
	//}

	//std::cout << "DISTANCE TO NEXT CHECKPOINT " << distance << "\n";
	//std::cout << "GO TO CHECKPOINT NUMBER " << carinfo.at(_playerId).currentCheckpoint << "\n";
	if (distance < 250)
		return true;
	else
		return false;
}

void RaceManager::CheckpointReached(std::string carId)
{
	//std::cout << "CheckpointReached ";

	carinfo.at(carId).currentCheckpoint++;

	if (carinfo.at(carId).currentCheckpoint >= _checkpoints.size()) {
		carinfo.at(carId).currentCheckpoint = 0;
		carinfo.at(carId).rounds++;
		if (carId == _playerId && carinfo.at(carId).rounds >= _totalRounds) {
			raceCompleted = true;
		}
	}
	// Actualizar el siguiente checkpoint
}

LMVector3 RaceManager::GetPlayerLastCheckpointPosition()
{
	int checkpointIndex = carinfo.at(_playerId).currentCheckpoint;

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
	int playerRacePos = carsAhead + 1;
	//for (int i = 0; i < ranking.size(); i++)
	//	if (ranking[i] == _playerId)
	//		playerPos = i;

	std::string positionString;

	if (playerRacePos == 1)
		positionString = "1 st";
	else if (playerRacePos == 2)
		positionString = "2 nd";
	else if (playerRacePos == 3)
		positionString = "3 rd";

	positionText->ChangeText(positionString);


	//std::cout << "CURRENTPOSITION = " << positionString << std::endl;
}

void RaceManager::CountdownUIChanged()
{
	countdownAnimating = true;
	countdownCurrentSize = 0;
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