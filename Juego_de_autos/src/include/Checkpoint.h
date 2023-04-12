#pragma once
#include "Component.h"

class RaceManager;

//class LocoMotor::GameObject;

class Checkpoint : public  LocoMotor::Component {
public:
	const static std::string name;
	static std::string GetName() {
		return "CheckPoint";
	};
	Checkpoint();
	//Checkpoint(GameObject* player = nullptr, int checkpointIndex = 0);

	void Start(LocoMotor::GameObject* player, int checkpointIndex);
	void Update(float dt) override;

private:

	RaceManager* raceManager;

	int _checkpointIndex;
	bool checked; // Si el jugador ya ha alcanzado este checkpoint en esta vuelta

	LocoMotor::GameObject* _player;
};