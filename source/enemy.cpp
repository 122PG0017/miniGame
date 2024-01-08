#include "enemy.h"
using namespace AppFrame;
bool sift;

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

	_position = { 0.0f, 50.0f, 0.0f };
	_scale = { 0.2f,0.2f,0.2f };
    sift = true;

	auto handle = MV1LoadModel("resource/tmp/DefaultCude.mv1");
	auto mv1Component = std::make_unique<MV1Component>(handle);
	AddComponent(std::move(mv1Component));

	auto col = std::make_unique<SphereCollisionComponent>();
	AddComponent(std::move(col));
}

void Enemy::Terminate()
{
	ObjectBase::Terminate();
}

void Enemy::Process(InputManager& input)
{
	if (sift)
	{
		_position.y += 1.0f;
		if (_position.y == 100) { sift = false; }
	}
	if(!sift)
	{
		_position.y -= 1.0f;
		if (_position.y == 20) { sift = true; }
	}
	_rotation.y += 0.1f;
	ObjectBase::Process(input);
}

void Enemy::Render()
{
	ObjectBase::Render();
}
