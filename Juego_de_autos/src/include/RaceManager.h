#pragma once
#include <map>
#include <string>
#include "Component.h"
#include "LMVector.h"

namespace LocoMotor {
	class UITextLM;
	class Spline;
	class InputManager;
	class SceneManager;
}

namespace JuegoDeAutos {
	class Checkpoint;
	struct CarInfo {
		int rounds = 0;
		int currentCheckpoint = 0;
		LocoMotor::LMVector3 position;
	};
	class RaceManager : public LocoMotor::Component
	{
	public:
		const static std::string name;
		RaceManager();
		~RaceManager();
		static RaceManager* GetInstance();
		/// @brief Sets the initial position of the listener to the gameobject's

		void Init(std::vector<std::pair<std::string, std::string>>& params) override;

		void Start() override;
		/// @brief Updates the listener's world attributes to be the same as the gameobject's
		/// @param dt DeltaTime used to calculate the velocity
		void Update(float dt) override;
		/// @brief Creates checkpoints
		/// @param params given by LUA
		void CreateCheckpoints(std::vector<std::pair<std::string, std::string>>& params);
		/// @brief Checks if the string can be an int type
		bool IsInt(const std::string& str);

		/// @brief Registers the position of the checkpoint
		/// @param checkpointPos The position of the checkpiont being registereds
		void RegisterCheckpointPosition(LocoMotor::LMVector3 checkpointPos);
		/// @brief Register player car
		void RegisterPlayerCar(std::string carId);
		/// @brief Register enemy car
		void RegisterNPCCar(std::string carId);
		/// @brief Updates the carId car position
		void UpdateCarPosition(std::string carId, LocoMotor::LMVector3 newPosition);
		/// @brief Checks if the ship has reached the checkpoint
		/// @return True if the ship is near the checkpoint
		bool HasCarReachedCheckpoint(std::string carId);
		/// @brief Checks and register the last checkpoint reached 
		void CheckpointReached(std::string carId);
		/// @brief Speeds the bgm when entering the last lap
		void OnLastLap();
		/// @brief What happens when the race finished
		void OnRaceFinished();

		// Accede a la posicion del siguiente Checkpoint del Jugador
		/// @brief Gets the position of the next checkpoint the player has to reach
		/// @return The next checkpoint position
		LocoMotor::LMVector3 GetPlayerLastCheckpointPosition(bool next = false); //arreglo de ultima hora a las 12

		/// @brief Returs true when the starting countdown finishes
		bool HasCountDownFinished();

		/// @brief Get the spline of the map
		LocoMotor::Spline* GetSpline();
		
		float GetSpeed();

		enum SpeedMode { middle, high };
		enum CarModel { Falcon, Eagle, Pelican, Flamingo };
		static SpeedMode speedMode;
		static CarModel carModelPlayerOne, carModelPlayerTwo;
		
		//void SetNumberOfPlayers(int value);
		//int GetNumberOfPlayers();
		static int numberOfPlayer;

	private:
		 
		void UpdateRanking();

		void CountdownUIChanged();

		void UpdateTimer(float dt);

		void SecondsToTimer(float _sec, int& min, int& sec, int& mil);

		std::string NumToString(int num, int numZeros);

		void ShowFPS();

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

		// Timer
		float currentTime;

		// LapTimer
		float bestlapTime = FLT_MAX;
		// The time when you completed the last lap
		float lastlapTime = 0;

		/// End Timer
		float endTimerStart = -1;
		float endTimerCurrent;
		bool ended = false;

		// UI
		LocoMotor::UITextLM* lapsText;
		LocoMotor::UITextLM* positionText;
		LocoMotor::UITextLM* countdownText;
		LocoMotor::UITextLM* timerText;
		LocoMotor::UITextLM* laptimerText;

		std::vector<LocoMotor::GameObject*> enemies;

		LocoMotor::Spline* mainSpline;

		// SpeedModes
		int speeds[3] = { 150, 220 };

		//Player reference
		LocoMotor::GameObject* player;
		LocoMotor::GameObject* playerTwo;

		int playerRacePos = 0;

		bool showFPS = true;
		LocoMotor::InputManager* inputMng;
		LocoMotor::SceneManager* sceneMng;
	};
}

