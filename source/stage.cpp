namespace
{
	constexpr auto stagehandle = "resource/tmp/Haikei demo2.mv1";
}

Stage::Stage()
{
	_name = "stage";
}

Stage::~Stage()
{
}

void Stage::Initialize()
{
	_position = { 0,-30,0 };
	float sc = 10.0f;
	_scale = VGet(_scale.x * sc, _scale.y, _scale.z * sc);
	auto handle = MV1LoadModel(stagehandle);
	auto mv1Component = std::make_unique<MV1Component>(handle);
	AddComponent(std::move(mv1Component));
}

void Stage::Terminate()
{
	ObjectBase::Terminate();
}

void Stage::Process(InputManager& input)
{
	ObjectBase::Process(input);
}

void Stage::Render()
{
	ObjectBase::Render();
}

void Stage::Debug()
{
	ObjectBase::Debug();
}
