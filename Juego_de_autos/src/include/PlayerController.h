#pragma once
#include "Component.h"
#include "LMVector.h"

using namespace LocoMotor;
namespace LocoMotor {
	class RigidBodyComponent;
	class InputManager;
	class MeshRenderer;
}

class RaceManager;

class PlayerController : public LocoMotor::Component
{
public:
	PlayerController();
	virtual ~PlayerController();
	void Init(std::vector<std::pair<std::string, std::string>>& params) override;

	void Start()override;
	void Update(float dt)override;
	void InitComponent() override;

private:
	RaceManager* raceManager;

	RigidBodyComponent* rbComp;
	InputManager* inputMng;
};

