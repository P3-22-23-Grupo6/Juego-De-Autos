#include "Scene.h"
#include "GameObject.h"
#include "Transform.h"
#include "RaceManager.h"

#include "RigidBodyComponent.h"
#include "Boost.h"
#include "Boost.h"

using namespace JuegoDeAutos;
using namespace LocoMotor;

const std::string Boost::name = "Boost";

Boost::Boost() {
	
}

void Boost::InitComponent() {

}

void Boost::Update(float dt) {

}

void Boost::OnCollisionEnter(GameObject* other)
{
 other->GetComponent<RigidBodyComponent>()->addForce(LMVector3(other->GetTransform()->GetRotation().Forward() * 20000));
}
