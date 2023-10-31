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
	side = 1;
	bufferTime = 0.0f;
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
	//ES UNA MIERDA PERO BRO STD::LERP SOLO FUNCIONA EN C++ 20 Y TENGO QYE HACER TODO SOLO ESTO Y EL DELTA TIME VA MAL Y TODO FEO PUTA VIDA TETE
	LMVector3 newPos;
	LMVector3 targetPos = LMVector3(4 * side, 3, 20);
	newPos = newPos.Lerp(tr->GetPosition(), targetPos, dt/1000.0f * panSpeed);
	tr->SetPosition(newPos);
	if (LMVector3(targetPos - tr->GetPosition()).Magnitude() < 0.1f && bufferTime <= 0.0f)
	{
		side *= -1;
		bufferTime = 1.0f;
	}
	if (bufferTime > 0.0f) bufferTime -= dt / 1000.0f;
	else bufferTime = 0.0f;
	tr->LookAt(LMVector3(0, 0, 0));
}
