#include "pch.h"
#include "RaceManager.h"
#include "../../Motor/src/LocoMotor_Utils/lmVector.h"
const std::string name = "RaceManager";

RaceManager::RaceManager()
{
	raceCompleted = false;
}

RaceManager::~RaceManager()
{
}

RaceManager* RaceManager::GetInstance()
{
	if (_instance == nullptr) {
		_instance = this;
	}
	return _instance;
}

void RaceManager::Init(std::vector<std::pair<std::string, std::string>>& params)
{
	//if (_instance == nullptr)_instance = this;
	//else delete this;
}

void RaceManager::Start()
{
}

void RaceManager::Update(float dt)
{
	UpdateRanking();
	if (raceCompleted) {
		// Pasar a escena donde se muestran los resultados
	}
}

void RaceManager::RegisterCheckpoint(CheckPoint* cp)
{
	_checkpoints.push_back(cp);
}

void RaceManager::RegisterPlayerCar(std::string carId)
{
	carinfo.insert(std::pair<std::string, CarInfo>(carId, { 0,0,new LMVector3() }));
	ranking.push_back(carId);
	_playerId = carId;
}

void RaceManager::RegisterNPCCar(std::string carId)
{
	carinfo.insert(std::pair<std::string, CarInfo>(carId, { 0,0,new LMVector3() }));
	ranking.push_back(carId);
}

void RaceManager::UpdateCarPosition(std::string carId, double x, double y, double z)
{
	carinfo.at(carId).position->SetX(x);
	carinfo.at(carId).position->SetY(y);
	carinfo.at(carId).position->SetZ(z);
}

void RaceManager::CheckpointReached(std::string carId)
{
	carinfo.at(carId).checkpoints++;
	if (carinfo.at(carId).checkpoints >= _totalCheckpointsPerRound) {
		carinfo.at(carId).checkpoints = 0;
		carinfo.at(carId).rounds++;
		if (carId == _playerId && carinfo.at(carId).rounds >= _totalRounds) {
			raceCompleted = true;
		}
	}
}

void RaceManager::UpdateRanking()
{
	if (ranking.size() < 2)return;
	for (int i = 1; i < ranking.size(); i++) {
		if (carinfo.at(ranking[i]).rounds < _totalRounds) { // Check if the car has completed the race
			if (carinfo.at(ranking[i]).rounds > carinfo.at(ranking[i - 1]).rounds ||
				(carinfo.at(ranking[i]).rounds == carinfo.at(ranking[i - 1]).rounds && carinfo.at(ranking[i]).checkpoints > carinfo.at(ranking[i - 1]).checkpoints)) {
				std::string aux = ranking[i - 1];
				ranking[i - 1] = ranking[i];
				ranking[i] = aux;
			}
		}
		
	}
}