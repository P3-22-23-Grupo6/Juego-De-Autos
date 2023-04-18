#include "pch.h"
//#include "PlayerController.h"
//#include "InputManager.h"
//#include "LMVector.h"
//#include "GameObject.h"
//
//#include <iostream>
//
////std::string PlayerController::name = "PlayerController";
//
//PlayerController::PlayerController()
//{
//	_player = GetContext();
//	_transform = _player->GetComponent<LocoMotor::Transform*>();
//}
//
//PlayerController::~PlayerController()
//{
//}
//
//void PlayerController::Init(std::vector<std::pair<std::string, std::string>>& params)
//{
//	std::cout << "PLayer Controller I am \n\n\n\n\n";
//}
//
//void PlayerController::Update(float dt)
//{
//	std::cout << "PLayer Controller I am \n\n\n\n\n";
//
//	InputManager* man = InputManager::Get();
//	if (man->controllerConnected()) {
//
//		float gyroRotate = man->GetGyroscopeAngularSpeed(InputManager::Axis::Horizontal);
//		float joystickValue_1_Hor = man->GetJoystickValue(1, InputManager::Axis::Horizontal);
//		//_node->Rotate(0, joystickValue_1_Hor * 5, -gyroRotate * 200);
//		_player->Rotate(0, gyroRotate * 200 + -joystickValue_1_Hor * 5, 0);
//		
//
//		float joystickValue_0_Hor = man->GetJoystickValue(0, InputManager::Axis::Horizontal);
//		float joystickValue_0_Ver = man->GetJoystickValue(0, InputManager::Axis::Vertical);
//
//		float verticalMov = 0;
//		if (man->GetButton(SDL_CONTROLLER_BUTTON_A)){
//			verticalMov = .1f;
//		}
//		else if (man->GetButton(SDL_CONTROLLER_BUTTON_B))
//			verticalMov = -.1f;
//
//		RigidBodyComponent* rbComp = GetComponent<RigidBodyComponent>();
//		rbComp->addForce(LMVector3(joystickValue_0_Hor, verticalMov, joystickValue_0_Ver));
//		_node->Translate(-joystickValue_0_Hor, verticalMov, -joystickValue_0_Ver);
//
//
//
//		SetPosition(LMVector3(_node->GetPosition_X(), _node->GetPosition_Y(), _node->GetPosition_Z()));
//	}
//	RigidBodyComponent* rbComp = GetComponent<RigidBodyComponent>();
//	//RAYCAST TEMPORAL
//	LMVector3 from = LMVector3(_node->GetPosition_X(), _node->GetPosition_Y(), _node->GetPosition_Z());
//	LMVector3 to = LMVector3(_node->GetPosition_X(), _node->GetPosition_Y() - 5, _node->GetPosition_Z());
//	if (rbComp->GetRaycastHit(from, to)) {
//		std::cout << "Collision! *****************";
//		//_node->Rotate(0, 3, 0);
//	}
//	else std::cout << "NO COLL! *****************";
//
//	bool acelerate = man->GetKey(SDL_SCANCODE_W);
//	if (acelerate) {
//
//		double degToRad = 0.0174533;
//
//		GetComponent<RigidBodyComponent>()->addForce(LMVector3(-20 * std::sin(_tr.rotation.GetY() * degToRad), 0, -20 * std::cos(_tr.rotation.GetY() * degToRad)) * dt);
//		//_rigidBody->AddForce(LMVector3(0, 0, 1));
//		//SetPosition(LMVector3(100, 10, 10));
//		//_node->Translate(0, 0, 1);
//	}
//
//	bool rotateRight = man->GetKey(SDL_SCANCODE_A);
//	if (rotateRight) {
//		GetComponent<RigidBodyComponent>()->setRotation(LMQuaternion(1, 1, 0, 0));
//		//_rigidBody->setRotation(LMQuaternion(1, 1, 0, 0));
//		_node->Rotate(0, 3, 0);
//		_tr.rotation.SetY(_tr.rotation.GetY() + 3.);
//	}
//	bool rotateLeft = man->GetKey(SDL_SCANCODE_D);
//	if (rotateLeft) {
//		GetComponent<RigidBodyComponent>()->setRotation(LMQuaternion(1, -1, 0, 0));
//		//_rigidBody->setRotation(LMQuaternion(1, -1, 0, 0));
//		_node->Rotate(0, -3, 0);
//		_tr.rotation.SetY(_tr.rotation.GetY() - 3.);
//	}
//
//	std::cout << _tr.rotation.GetY() << std::endl;
//}
//
//void PlayerController::InitComponent()
//{
//}
