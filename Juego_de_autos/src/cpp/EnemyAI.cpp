#include "Scene.h"
#include "GameObject.h"
#include "Transform.h"
#include "LMSpline.h"

#include "EnemyAI.h"

using namespace JuegoDeAutos;
using namespace LocoMotor;

const std::string EnemyAI::name = "EnemyAI";

EnemyAI::EnemyAI() {
}

void EnemyAI::Init(std::vector<std::pair<std::string, std::string>>& params) {
	for (int i = 0; i < params.size(); i++) {
		if (params[i].first == "enemySpeed") {
			enemySpeed = std::stof(params[i].second);
		}
	}
	//_body = nullptr;
}

void EnemyAI::InitComponent() {

}

void EnemyAI::Update(float dt) {

}
