#pragma once
#include "Component.h"

namespace JuegoDeAutos {
	class RaceManager;

	class Checkpoint : public  LocoMotor::Component {
	public:
		const static std::string name;
		static std::string GetName() {
			return "CheckPoint";
		};
		Checkpoint();
		void InitComponent() override;

	private:

		RaceManager* raceManager;

		// Va sumandose para saber cuantos checkpoints hay en cada momento
		// Tambien se usa para ir asignando los index de los checkpoints en orden
		static int numCheckpoints;
		int _checkpointIndex;
		bool checked; // Si el jugador ya ha alcanzado este checkpoint en esta vuelta
	};
}