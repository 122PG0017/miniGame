
namespace 
{
	constexpr auto skyhandle = "resource/tmp/sky.mv1";
	constexpr auto skyhandle2 = "resource/skyDoom/incskies_029_16k.x";
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
	float sc = 20.0f;
	_scale = DxLib::VScale(_scale, sc);
	auto handle = MV1LoadModel(skyhandle2);
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
	float deltaTime = _mode->GetStepTm() * 0.001f;
	float spd = 0.1f;
	_rotation.y += deltaTime * spd;
	//_position = _player != nullptr ? _player->GetPosition() : Math::VZero();
	ObjectBase::Process(input);
}

void SkySphere::Render()
{
	ObjectBase::Render();
}

void SkySphere::Debug()
{
	ObjectBase::Debug();
}
