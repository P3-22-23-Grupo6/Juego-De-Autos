// Motor
#include "LMVector.h"
#include "Scene.h"
#include "GameObject.h"
#include "Transform.h"
#include "UITextLM.h"

// Componentes juego
#include "RaceManager.h"
#include "Checkpoint.h"

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
//
void RaceManager::InitComponent()
{
	//std::cout << "RaceManager START" << "\n" << "\n" << "\n" << "\n" << "\n";

}

void RaceManager::Start()
{
	lapsText = gameObject->GetScene()->GetObjectByName("lapsText")->GetComponent<LocoMotor::UITextLM>();


	RegisterPlayerCar("Player");


	//int numberOfEnemies = 3;

	//std::string s = "Enemy";
	RegisterNPCCar("Enemy0");

	GameObject* enemy = gameObject->GetScene()->GetObjectByName("Enemy0");

	std::cout << " enemy= " << enemy->GetTransform()->GetPosition().GetY() << std::endl;
	enemies.push_back(enemy);

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
	std::cout << " enemy= " << enemy->GetTransform()->GetPosition().GetY() << std::endl;
	UpdateCarPosition("Enemy0", enemy->GetTransform()->GetPosition());

	//std::cout << "RACEMANAGER INFO : " << "\n" << "\n" << "\n" << "\n" << "\n";

	// Comprobar si algun coche ha llegado a algun checkpoint
	// En caso afirmativo, notificarlo


	if (HasCarReachedCheckpoint(_playerId))
		CheckpointReached(_playerId);

	if (HasCarReachedCheckpoint("Enemy0"))
		CheckpointReached("Enemy0");


	//for (size_t i = 0; i < enemies.size(); i++)
	//{
	//	std::string enemyId = "Enemy" + std::to_string(i);

	//	//if (HasCarReachedCheckpoint(enemyId)){}
	//		//CheckpointReached(enemyId);
	//}

	//// Comprobar jugador
	//int checkpointIndex = carinfo.at(_playerId).currentCheckpoint;
	//LMVector3 targetCheckpoint_Pos = _checkpoints[checkpointIndex];
	//LMVector3 player_Pos = carinfo.at(_playerId).position;

	//double x = targetCheckpoint_Pos.GetX() - player_Pos.GetX();
	//double y = targetCheckpoint_Pos.GetY() - player_Pos.GetY();
	//double z = targetCheckpoint_Pos.GetZ() - player_Pos.GetZ();
	//LMVector3 directorVector = LMVector3(x, y, z);
	//float distance = directorVector.Magnitude();
	////std::cout << "DISTANCE TO NEXT CHECKPOINT " << distance << "\n";
	////std::cout << "GO TO CHECKPOINT NUMBER " << carinfo.at(_playerId).currentCheckpoint << "\n";
	//if (distance < 250)
	//	CheckpointReached(_playerId);



	//UpdateRanking();
	//if (raceCompleted) {
	//	// Pasar a escena donde se muestran los resultados
	//}


	

	std::string s = std::to_string(carinfo.at(_playerId).rounds) + " / 3";

	//std::cout << carinfo.at(_playerId).rounds << std::endl;
	 
	lapsText->ChangeText(s);
}

void RaceManager::RegisterCheckpointPosition(LMVector3 checkpointPos)
{
	_checkpoints.push_back(checkpointPos);
}

void RaceManager::RegisterPlayerCar(std::string carId)
{
	CarInfo carInfo = { 0,0,  LMVector3() };
	carinfo.insert(std::pair<std::string, CarInfo>(carId, carInfo));
	ranking.push_back(carId);
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


	if (carId != "Player") {}
	std::cout << "EnemyCheckpointIndex = " << checkpointIndex << std::endl;

	if (carId != "Player")
		std::cout << "EnemyDistance = " << distance << std::endl;

	if (carId != "Player")
		std::cout << "EnemyRounds = " << carinfo.at(carId).rounds << std::endl;

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

void RaceManager::UpdateRanking()
{
	if (ranking.size() < 2)return;
	for (int i = 1; i < ranking.size(); i++) {
		if (carinfo.at(ranking[i]).rounds < _totalRounds) { // Check if the car has completed the race
			if (carinfo.at(ranking[i]).rounds > carinfo.at(ranking[i - 1]).rounds ||
				(carinfo.at(ranking[i]).rounds == carinfo.at(ranking[i - 1]).rounds 
					&& carinfo.at(ranking[i]).currentCheckpoint > carinfo.at(ranking[i - 1]).currentCheckpoint)) {
				std::string aux = ranking[i - 1];
				ranking[i - 1] = ranking[i];
				ranking[i] = aux;
			}
		}
	}

	// Posicion del jugador respecto al resto de coches en la carrera
	int playerPos;
	for (int i = 0; i < ranking.size(); i++)
		if (ranking[i] == _playerId)
			playerPos = i;
}