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
	maxDistance = 20;
	backward = true;
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
	counter += 0.02f;
	if (backward)
	{
		if(tr->GetPosition().GetZ() < maxDistance) tr->SetPosition(tr->GetPosition() + LMVector3(0.1f, 0, 1) * dt / 100.0f * panSpeed);
		else backward = false;
	}
	else
	{
		if (tr->GetPosition().GetZ() > 0.0f) tr->SetPosition(tr->GetPosition() - LMVector3(0.1f, 0, 1) * dt / 100.0f * panSpeed);
		else backward = true;
	}
	
	return;
	if (tr == nullptr) return;
	//ES UNA MIERDA PERO BRO STD::LERP SOLO FUNCIONA EN C++ 20 Y TENGO QYE HACER TODO SOLO ESTO Y EL DELTA TIME VA MAL Y TODO FEO PUTA VIDA TETE
	LMVector3 targetPos = LMVector3(CustomLerp(-10, 10, 0.001f * panSpeed) * side, 3, 20);
	tr->SetPosition(targetPos);
	if (LMVector3(targetPos - tr->GetPosition()).Magnitude() < 0.1f && bufferTime <= 0.0f)
	{
		side *= -1;
		bufferTime = 1.0f;
	}
	if (bufferTime > 0.0f) bufferTime -= dt / 1000.0f;
	else bufferTime = 0.0f;
	tr->LookAt(LMVector3(0, 0, 0));
}
double JuegoDeAutos::CameraPanner::CustomLerp(double a, double b, double t) {
	t = std::max(0.0, std::min(1.0, t)); // Ensure t is in the [0, 1] range
	return a + t * (b - a);
}
