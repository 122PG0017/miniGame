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
	//auto dir = GetComponent<CameraComponent>()->GetDegree();
	if (input.GetKeyW(InputState::Hold)) { PlayerMove(input, spd); }
	if (input.GetKeyS(InputState::Hold)) { PlayerMove(input, spd); }
	if (input.GetKeyD(InputState::Hold)) { PlayerMove(input, spd); }
	if (input.GetKeyA(InputState::Hold)) { PlayerMove(input, spd); }

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

void Player::PlayerMove(InputManager& input, float speed)
{
	//設定処理
	auto radian = GetComponent<CameraComponent>()->GetRadian();
	auto cameravec = GetComponent<CameraComponent>()->GetForwardVECTOR();
	//float radian = (_rotation.y+dir) * DX_PI_F / 180.0f;
	//float radian = Math::ToRadians(dir);
	cameravec.y -= 180.0f;
	auto dig = GetComponent<CameraComponent>()->GetDegree();
	_rotation.y = GetComponent<CameraComponent>()->GetForwardVECTOR().y;
	//_rotation.y = cameravec.y + 180.0f;
	auto pos = _position;
	//_position.x -= sin(radian) * speed;
	//_position.z -= cos(radian) * speed;
	//pos.x -= sin(radian*100) * speed;
	//pos.z -= cos(radian*100) * speed;
	//auto vec.x -= sin(radian) * speed;
	//auto vec.y -= cos(radian) * speed;
	vec.x += sin(radian) * speed;
	vec.y += cos(radian) * speed;

	//_position = Math::Lerp(_position,pos,1);
	//_position = VAdd(_position, cameravec);
	//_position.x = _position.x + cameravec.x;
	//_position.z = _position.y + cameravec.y;
	_position.x = _position.x + vec.x;
	_position.z = _position.y + vec.y;

	//GetComponent<MV1Component>()->SetAnimation(23);
	//GetComponent<MV1Component>()->SetLoop(true);
	//_rotation.y += radian;
}
