#pragma once
#include <map>
#include <string>
#include "Component.h"
#include "LMVector.h"

namespace LocoMotor {
	class UITextLM;
	class Spline;
}

namespace JuegoDeAutos {
	class Checkpoint;
	struct CarInfo {
		int rounds = 0;
		int currentCheckpoint = 0;
		LocoMotor::LMVector3 position;
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

		void Init(std::vector<std::pair<std::string, std::string>>& params) override;

		void Start() override;
		/// @brief Updates the listener's world attributes to be the same as the gameobject's
		/// @param dt DeltaTime used to calculate the velocity
		void Update(float dt) override;

		void CreateCheckpoints(std::vector<std::pair<std::string, std::string>>& params);
		bool Compare(const std::pair<std::string, std::string>& p1, const std::pair<std::string, std::string>& p2);
		// 
		void RegisterCheckpointPosition(LocoMotor::LMVector3 checkpointPos);
		// 
		void RegisterPlayerCar(std::string carId);
		void RegisterNPCCar(std::string carId);
		/// @brief Updates the carId car position
		void UpdateCarPosition(std::string carId, LocoMotor::LMVector3 newPosition);

		bool HasCarReachedCheckpoint(std::string carId);
		// 
		void CheckpointReached(std::string carId);

		// Accede a la posicion del siguiente Checkpoint del Jugador
		LocoMotor::LMVector3 GetPlayerLastCheckpointPosition();

		bool HasCountDownFinished();


		LocoMotor::Spline* GetSpline();


		enum SpeedMode { low, middle, high };
		static SpeedMode speedMode;

	private:
		// 
		void UpdateRanking();

		void CountdownUIChanged();

		static RaceManager* _instance;
		// The number of rounds to complete the race
		const int _totalRounds = 3;
		// The total number of checkpoint per round
		int _totalCheckpointsPerRound;
		// The checkpoints in the circuit
		std::vector<LocoMotor::LMVector3>_checkpoints;
		// 
		//std::vector<CarInfo>carinfo;
		std::map<std::string, CarInfo> carinfo;
		//
		std::vector<std::string>ranking;
		// The player id
		std::string _playerId;
		// True if the player has completed _totalRounds rounds to the circuit
		bool raceCompleted;

		// Countdown
		float countdownTimer = 8;
		bool countdownFinished = false;
		int countDownSeconds;
		int countDownSecondsLastFrame;
		// Countdown Animation
		float countdownCurrentSize = 0;
		float countdownNormalSize;
		bool countdownAnimating;
		const float timeConstant = .0009;
		// FPS counter timer
		const float fpsCounterRefreshRate = 0.5;
		float fpsCounterUpdated;

		// UI
		LocoMotor::UITextLM* lapsText;
		LocoMotor::UITextLM* positionText;
		LocoMotor::UITextLM* countdownText;

		std::vector<LocoMotor::GameObject*> enemies;

		LocoMotor::Spline* mainSpline;

		LocoMotor::UITextLM* pruebaaa;
	};
}

