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

	if(input.GetMouseLeft(InputState::Pressed))
	{
		GetComponent<SphereCollisionComponent>()->SetAttachFrame(96);
		GetComponent<MV1Component>()->SetAnimation(1,true);
		GetComponent<MV1Component>()->SetLoop(false);
	}
}

void Player::Render()
{
	ObjectBase::Render();
}

void Player::Debug()
{
	VECTOR forward{ VTransform({0.0f, 500.0f, -5.0f}, _rotationMatrix) };
	VECTOR back{ VTransform({0.0f, -500.0f, 5.0f}, _rotationMatrix) };
    float CrashDeg = 100.0f;
	float r = std::tanf(Math::ToRadians(CrashDeg * 0.5)) * VSize(VSub(_position, VAdd(_position, forward)));

	DrawCapsule3D(_position, VAdd(_position, forward), r, 8, GetColor(255, 0, 0), GetColor(0, 0, 0), false);
	ObjectBase::Debug();
}

void Player::PlayerMove(InputManager& input, float speed, float dir)
{
	//設定処理
	//float radian = (_rotation.y+dir) * DX_PI_F / 180.0f;
	float radian = Math::ToRadians(dir);
	_position.x -= sin(radian) * speed;
	_position.z -= cos(radian) * speed;

	GetComponent<MV1Component>()->SetAnimation(23);
	GetComponent<MV1Component>()->SetLoop(true);
	_rotation.y += radian;
}
