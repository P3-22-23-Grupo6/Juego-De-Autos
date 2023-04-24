#pragma once
#include <map>
#include <string>
#include "Component.h"
#include "LMVector.h"
class Checkpoint;
struct CarInfo {
	int rounds;
	int currentCheckpoint;
	LMVector3 position;
};
//bool operator<(CarInfo const& a, CarInfo const& b) {
//	return a.rounds<b.rounds||(a.rounds==b.rounds&&a.checkpoints<b.checkpoints)||(a.rounds == b.rounds && a.checkpoints == b.checkpoints&&())
//}
class RaceManager : public LocoMotor::Component
{
public:
	const static std::string name;
	RaceManager();
	~RaceManager();
	static RaceManager* GetInstance();
	/// @brief Sets the initial position of the listener to the gameobject's
	void InitComponent() override;
	/// @brief Updates the listener's world attributes to be the same as the gameobject's
	/// @param dt DeltaTime used to calculate the velocity
	void Update(float dt) override;
	// 
	void RegisterCheckpointPosition(LMVector3 checkpointPos);
	// 
	void RegisterPlayerCar(std::string carId);
	void RegisterNPCCar(std::string carId);
	/// @brief Updates the carId car position
	void UpdateCarPosition(std::string carId, double x, double y, double z);
	// 
	void CheckpointReached(std::string carId);
private:
	// 
	void UpdateRanking();
	static RaceManager* _instance;
	// The number of rounds to complete the race
	const int _totalRounds = 3;
	// The total number of checkpoint per round
	int _totalCheckpointsPerRound;
	// The checkpoints in the circuit
	std::vector<LMVector3>_checkpoints;
	// 
	//std::vector<CarInfo>carinfo;
	std::map<std::string, CarInfo> carinfo;
	//
	std::vector<std::string>ranking;
	// The player id
	std::string _playerId;
	// True if the player has completed _totalRounds rounds to the circuit
	bool raceCompleted;
};

