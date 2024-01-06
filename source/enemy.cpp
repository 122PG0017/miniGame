#include "enemy.h"
using namespace AppFrame;

Enemy::Enemy():Handle{0}
{
	_name = "cube";
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
	ObjectBase::Initialize();

	_position = { 0.0f, 300.0f, 0.0f };
	_scale = { 0.1f,0.1,0.1f };

	auto handle = MV1LoadModel("resource/tmp/DefaultCude.mv1");
	auto mv1Component = std::make_unique<MV1Component>(handle);
	AddComponent(std::move(mv1Component));
}

void Enemy::Terminate()
{
	ObjectBase::Terminate();
}

void Enemy::Process(InputManager& input)
{
	ObjectBase::Process(input);
}

void Enemy::Render()
{
	ObjectBase::Render();
}
