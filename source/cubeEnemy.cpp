using namespace AppFrame;

CubeEnemy::CubeEnemy():Handle{0}
{
	_name = "cube";
}

CubeEnemy::~CubeEnemy()
{
}

void CubeEnemy::Initialize()
{
	ObjectBase::Initialize();

	_position = { 0.0f, 60.0f, -200.0f };
	_scale = { 0.2f,0.2f,0.2f };
    _sift = true;

	auto handle = MV1LoadModel("resource/tmp/DefaultCude.mv1");
	auto mv1Component = std::make_unique<MV1Component>(handle);
	AddComponent(std::move(mv1Component));

	auto col = std::make_unique<SphereCollisionComponent>();
	AddComponent(std::move(col));

	GetComponent <SphereCollisionComponent>()->SetAttachFrame(1);
}

void CubeEnemy::Terminate()
{
	ObjectBase::Terminate();
}

void CubeEnemy::Process(InputManager& input)
{
	auto _player = GetPlayer();
	if (_sift)
	{
		_position.y += 1.0f;
		if (_position.y == 100) { _sift = false; }
	}
	if(!_sift)
	{
		_position.y -= 1.0f;
		if (_position.y == 20) { _sift = true; }
	}
	_rotation.y += 0.1f;
	/*if (CheckCollision::Intersect(GetComponent<MV1Component>()->GetModelHandle(), _player->GetComponent<SphereCollisionComponent>()))
	{
		ModeServer::GetInstance()->Add(std::make_unique<modeEnd>(), 1, "end");
		ModeServer::GetInstance()->Del("game");
		return;
	};*/
	ObjectBase::Process(input);
}

void CubeEnemy::Render()
{
	ObjectBase::Render();
}

void CubeEnemy::Debug()
{
	ObjectBase::Debug();
}
