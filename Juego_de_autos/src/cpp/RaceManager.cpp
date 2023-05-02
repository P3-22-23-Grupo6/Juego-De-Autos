// Motor
#include "LMVector.h"
#include "Scene.h"
#include "GameObject.h"
#include "Transform.h"
#include "UITextLM.h"

// Componentes juego
#include "RaceManager.h"
#include "Checkpoint.h"

using namespace JuegoDeAutos;
using namespace LocoMotor;
const std::string name = "RaceManager";

RaceManager* RaceManager::_instance = nullptr;
RaceManager::RaceManager()
{
	raceCompleted = false;

	if (_instance == nullptr)
		_instance = this;
	else delete this;

	this->carinfo = std::map<std::string, CarInfo>();
}

RaceManager::~RaceManager()
{
	for (auto& cInfo : carinfo) {

	}
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

void RaceManager::Start()
{
	lapsText = gameObject->GetScene()->GetObjectByName("lapsText")->GetComponent<LocoMotor::UITextLM>();
	positionText = gameObject->GetScene()->GetObjectByName("positionText")->GetComponent<LocoMotor::UITextLM>();
	countdownText = gameObject->GetScene()->GetObjectByName("countdownText")->GetComponent<LocoMotor::UITextLM>();
	countdownNormalSize = countdownText->GetSizeX();

	ranking.clear();
	RegisterPlayerCar("Player");


	//int numberOfEnemies = 3;

	//std::string s = "Enemy";
	RegisterNPCCar("Enemy0");
	RegisterNPCCar("Enemy1");


	GameObject* enemy = gameObject->GetScene()->GetObjectByName("Enemy0");
	//std::cout << " enemy= " << enemy->GetTransform()->GetPosition().GetY() << std::endl;
	enemies.push_back(enemy);

	enemy = gameObject->GetScene()->GetObjectByName("Enemy1");
	//std::cout << " enemy= " << enemy->GetTransform()->GetPosition().GetY() << std::endl;
	enemies.push_back(enemy);

	//enemy = gameObject->GetScene()->GetObjectByName("Enemy1");;
	//std::cout << " enemy1= " << enemy->GetTransform()->GetPosition().GetY() << std::endl;
	//enemies.push_back(enemy);


	carinfo.at(_playerId).rounds = 0;
	////carinfo.at(s).rounds = 0;

	//std::cout << " carinfo = " << carinfo.begin()->first << std::endl;

	//std::cout << " carinfo_currentCheckpoint = " << carinfo.begin()->second.position.GetY() << std::endl;
}

void RaceManager::Update(float dt)
{

	// Actualizar la posicion de todos los coches enemigos
	//UpdateCarPosition("Enemy", enemies[1]->GetTransform()->GetPosition());

	GameObject* enemy = enemies[0];
	UpdateCarPosition("Enemy0", enemy->GetTransform()->GetPosition());
	//enemy = enemies[1];
	//UpdateCarPosition("Enemy1", enemy->GetTransform()->GetPosition());

	//std::cout << "RACEMANAGER INFO : " << "\n" << "\n" << "\n" << "\n" << "\n";

	// Comprobar si algun coche ha llegado a algun checkpoint
	// En caso afirmativo, notificarlo


	if (HasCarReachedCheckpoint(_playerId))
		CheckpointReached(_playerId);

	if (HasCarReachedCheckpoint("Enemy0"))
		CheckpointReached("Enemy0");

	if (HasCarReachedCheckpoint("Enemy1"))
		CheckpointReached("Enemy1");


	//for (size_t i = 0; i < enemies.size(); i++)
	//{
	//	std::string enemyId = "Enemy" + std::to_string(i);

	//	//if (HasCarReachedCheckpoint(enemyId)){}
	//		//CheckpointReached(enemyId);
	//}


	UpdateRanking();

	std::string s = std::to_string(carinfo.at(_playerId).rounds) + " / 3";
	lapsText->ChangeText(s);

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

	gameObject->GetComponent<UITextLM>()->ChangeText(std::to_string(1000 / (int)dt) + " fps");
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

void RaceManager::UpdateRanking()
{
	// Saber cuantos coches tiene por delante el player
	int carsAhead = 0;

	// Que coches estan justo en la misma ronda que el jugador y cuantos estan por delante
	std::vector<std::string> carsInSameRound;

	int playerRounds = carinfo.at(_playerId).rounds;

	for (size_t i = 0; i < ranking.size(); i++)
	{
		std::string enemyName = ranking[i];

		int enemyRound = carinfo.at(enemyName).rounds;

		// Si va por delante, añadirlo a coches que van por delante directamente
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

		// Si va por delante, añadirlo a coches que van por delante directamente
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

		// Si va por delante, añadirlo a coches que van por delante directamente
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