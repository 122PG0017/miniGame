#include "skySphere.h"
namespace 
{
	constexpr auto skyhandle = "resource/tmp/sky.mv1";
}

SkySphere::SkySphere()
{
	_name = "sky";
}

SkySphere::~SkySphere()
{
}

void SkySphere::Initialize()
{
	_position = { 0,0,0 };
	float sc = 10.0f;
	_scale = VScale(_scale, sc);
	auto handle = MV1LoadModel(skyhandle);
	auto mv1Component = std::make_unique<MV1Component>(handle);
	AddComponent(std::move(mv1Component));
}

void SkySphere::Terminate()
{
	ObjectBase::Terminate();
}

void SkySphere::Process(InputManager& input)
{
	auto _player = GetPlayer();
	//float deltaTime = _mode->GetStepTm() * 0.001f;
	//float spd = 0.1f;
	//_rotation.y += deltaTime * spd;
	_position = _player != nullptr ? _player->GetPosition() : Math::VZero();
	ObjectBase::Process(input);
}

void SkySphere::Render()
{
	ObjectBase::Render();
}
