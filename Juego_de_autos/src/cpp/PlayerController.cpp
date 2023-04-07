#include "pch.h"
#include "PlayerController.h"
#include <iostream>

std::string PlayerController::name = "PlayerController";

PlayerController::PlayerController()
{

}

PlayerController::~PlayerController()
{
}

void PlayerController::Init(std::vector<std::pair<std::string, std::string>>& params)
{
	std::cout << "PLayer Controller I am \n\n\n\n\n";
}

void PlayerController::Update(float dt)
{
	std::cout << "PLayer Controller I am \n\n\n\n\n";
}

void PlayerController::InitComponent()
{
}
