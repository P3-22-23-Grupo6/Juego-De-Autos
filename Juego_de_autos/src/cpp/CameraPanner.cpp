#include "Scene.h"
#include "GameObject.h"
#include "Transform.h"
#include <cmath>


#include "CameraPanner.h"

using namespace JuegoDeAutos;
using namespace LocoMotor;

const std::string CameraPanner::name = "CameraPanner";

CameraPanner::CameraPanner() {
	tr = nullptr;
}

void CameraPanner::Init(std::vector<std::pair<std::string, std::string>>& params) {
	for (int i = 0; i < params.size(); i++) {
		if (params[i].first == "speed") {
			panSpeed = std::stof(params[i].second);
		}
	}
}

void JuegoDeAutos::CameraPanner::Start()
{
	tr = gameObject->GetComponent<LocoMotor::Transform>();
}

void JuegoDeAutos::CameraPanner::Update(float dt)
{
	if (tr == nullptr) return;
	//LMVector3 newPos;
	//newPos = newPos.Lerp(tr->GetPosition(), LMVector3(10 + sin(90), 3, 20), dt * 5.0f);
	tr->SetPosition(tr->GetPosition() + LMVector3(1, 0, 0)* panSpeed * dt/100.0f);
	//std::cout << "LERPING\n";
}
