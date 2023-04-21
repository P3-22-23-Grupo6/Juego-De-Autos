#include "RaceManager.h"
#include "GameObject.h"
#include "Checkpoint.h"
#include "LMVector.h"
const std::string name = "RaceManager";

RaceManager* RaceManager::_instance = nullptr;
RaceManager::RaceManager()
{
	raceCompleted = false;

	if (_instance == nullptr)
		_instance = this;
	else delete this;

	carinfo = std::map<std::string, CarInfo>();
}

RaceManager::~RaceManager()
{
	for (auto& cInfo : carinfo) {
		delete cInfo.second.position;
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
	std::cout << "RaceManager START" << "\n" << "\n" << "\n" << "\n" << "\n";

	RegisterPlayerCar("player");
}

void RaceManager::Update(float dt)
{
	std::cout << "RACEMANAGER INFO : " << "\n" << "\n" << "\n" << "\n" << "\n";

	// Comprobar si algun coche ha llegado a algun checkpoint
	// En caso afirmativo, notificarlo

	// Comprobar jugador
	int checkpointIndex = carinfo.at(_playerId).currentCheckpoint;
	LMVector3 targetCheckpoint_Pos = _checkpoints[checkpointIndex];
	LMVector3* player_Pos = carinfo.at(_playerId).position;

	double x = targetCheckpoint_Pos.GetX() - player_Pos->GetX();
	double y = targetCheckpoint_Pos.GetY() - player_Pos->GetY();
	double z = targetCheckpoint_Pos.GetZ() - player_Pos->GetZ();
	LMVector3 directorVector = LMVector3(x, y, z);
	float distance = directorVector.Magnitude();
	std::cout << "DISTANCE TO NEXT CHECKPOINT " << distance << "\n";
	std::cout << "GO TO CHECKPOINT NUMBER " << carinfo.at(_playerId).currentCheckpoint << "\n";
	if (distance < 20)
		CheckpointReached(_playerId);

	UpdateRanking();
	if (raceCompleted) {
		// Pasar a escena donde se muestran los resultados
	}
}

void RaceManager::RegisterCheckpointPosition(LMVector3 checkpointPos)
{
	_checkpoints.push_back(checkpointPos);
}

void RaceManager::RegisterPlayerCar(std::string carId)
{
	CarInfo carInfo = { 0,0, new LMVector3() };
	carinfo.insert(std::pair<std::string, CarInfo>(carId, carInfo));
	ranking.push_back(carId);
	_playerId = carId;
}

void RaceManager::RegisterNPCCar(std::string carId)
{
	CarInfo carInfo = { 0,0, new LMVector3() };

	carinfo.insert(std::pair<std::string, CarInfo>(carId, carInfo));
	ranking.push_back(carId);
}

void RaceManager::UpdateCarPosition(std::string carId, double x, double y, double z)
{
	std::cout << "carId = " << carId;

	carinfo.at(carId).position->SetX(x);
	carinfo.at(carId).position->SetY(y);
	carinfo.at(carId).position->SetZ(z);
}

void RaceManager::CheckpointReached(std::string carId)
{
	std::cout << "CheckpointReached ";

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
				(carinfo.at(ranking[i]).rounds == carinfo.at(ranking[i - 1]).rounds && carinfo.at(ranking[i]).currentCheckpoint > carinfo.at(ranking[i - 1]).currentCheckpoint)) {
				std::string aux = ranking[i - 1];
				ranking[i - 1] = ranking[i];
				ranking[i] = aux;
			}
		}

	}
}