#include "player.h"
using namespace AppFrame;
using namespace model;

Player::Player()
{
	_name = "Player";
}

Player::~Player()
{
}

void Player::Initialize()
{
	ObjectBase::Initialize();

	_position = { 0.0f, 0.0f, 0.0f }; //プレイヤー座標

	auto handle = MV1LoadModel("resource/Knight/MV1/enemy_1_.mv1");
	auto mv1Component = std::make_unique<MV1Component>(handle);
	mv1Component->SetAnimation(0);
	AddComponent(std::move(mv1Component));

	auto camera = std::make_unique<CameraComponent>();
	camera->SetCameraMode(CameraMode::Player);
	AddGameComponent(std::move(camera));

	auto col = std::make_unique<SphereCollisionComponent>();
	AddComponent(std::move(col));

	GetComponent <SphereCollisionComponent>()->SetAttachFrame(40);
}

void Player::Terminate()
{
	model::modelDelete(&_modelInf);
	ObjectBase::Terminate();
}

void Player::Process(InputManager& input)
{
	ObjectBase::Process(input);

	//キーボードでの自機移動処理
	float spd = 10.0;
	auto dir = GetComponent<CameraComponent>()->GetDegree();
	if (input.GetKeyW(InputState::Hold)) { PlayerMove(input, spd, dir); }
	if (input.GetKeyS(InputState::Hold)) { PlayerMove(input, spd, dir + 180.f); }
	if (input.GetKeyD(InputState::Hold)) { PlayerMove(input, spd, dir + 90.f); }
	if (input.GetKeyA(InputState::Hold)) { PlayerMove(input, spd, dir + 270.f); }

	
}

void Player::Render()
{
	ObjectBase::Render();
}

void Player::Debug()
{
	ObjectBase::Debug();
}

void Player::PlayerMove(InputManager& input, float speed, float dir)
{
	//設定処理
	float radian = (_rotation.y+dir) * DX_PI_F / 180.0f;
	_position.x -= sin(radian) * speed;
	_position.z -= cos(radian) * speed;


	GetComponent<MV1Component>()->SetAnimation(23);
	GetComponent<MV1Component>()->SetLoop(true);
	_rotation.y = dir + 180.0f;
}
