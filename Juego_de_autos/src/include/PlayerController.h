#pragma once
#include "Component.h"
#include "LMVector.h"
#include "InputManager.h"

 class PlayerController : public LocoMotor::Component
{
public:
	PlayerController();
	virtual ~PlayerController();
	void Init(std::vector<std::pair<std::string, std::string>>& params) override;
	void Update(float dt)override;
	void InitComponent() override;
};

