#include "player.h"
using namespace AppFrame;
using namespace model;

player::player()
{

	_spdParam = 1.0f;
	_status = Status::Idle;
	_cam = CameraType::Fps;
	_scale = VScale(_scale, PLAYER::SIZE);
	s = _scale;

	VECTOR zero = Math::VZero();

	_jumpVector = zero;
	_jumpTarget = zero;
	_rotationExtend = zero;
	_rotationExtendFREE_LOOK = zero;
	_name = "Player";
	_side = 0;
	_rotationExtendParameter = 0.0f;
	_idleParameter = 1.0f;
	_landingParameter = 0.0f;
	_visualRotationParameter = 0.0f;
	_visualRoation = { Math::ToRadians(90.0f), Math::ToRadians(180.0f), Math::ToRadians(0.0f) };
	_visualRotationInJump = { Math::ToRadians(-75.0f), Math::ToRadians(0.0f), Math::ToRadians(0.0f) };
	_trueVisualRotationInJump = Math::VZero();

	//回転パターンを設定
	VECTOR rotationPattern[] = {
		{0.0f,0.0f,0.0f},
		{0.0f,90.0f,0.0f},
		{0.0f,180.0f,0.0f},
		{0.0f,-90.0f,0.0f},
		{90.0f,0.0f,0.0f},
		{-90.0f,0.0f,0.0f},
	};
	//見た目上の回転パターンを設定
	VECTOR visualRotationPattern[] = {
		{0.0f,0.0f,0.0f},
		{0.0f,90.0f,0.0f},
		{0.0f,180.0f,0.0f},
		{0.0f,-90.0f,0.0f},
		{-90.0f,180.0f,0.0f},
		{90.0f,180.0f,0.0f},
	};

	for (int i = 0; i < PLAYER::SIDE_NUMBER; i++) {
		_rotationPattern.emplace_back(Math::VDeg2Rad(rotationPattern[i]));
		_visualRotationPattern.emplace_back(Math::VDeg2Rad(visualRotationPattern[i]));
	}

}

player::~player()
{
}

void player::Initialize()
{
	ObjectBase::Initialize();
	_position = { 0.0f, 0.0f, 0.0f }; //プレイヤー座標
	modelImport("resource/Knight/MV1/enemy_1_.mv1", 1.0f, &_modelInf, &RS);
	_modelInf.pos = VECTOR(0, 0, 0);
	RS.duplicateModelListImportR();
	animChange(2, &_modelInf, false, false, false);
}

void player::Terminate()
{
	model::modelDelete(&_modelInf);
	ObjectBase::Terminate();
}

void player::Process(InputManager& input)
{
	ObjectBase::Process(input);
}

void player::Render()
{
	isAnimEnd = modelRender(&_modelInf, 1, 1);
	ObjectBase::Render();
}
