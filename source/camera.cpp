#include "camera.h"
camera::camera(Player& p, CameraMode initCam) :_p(p) {
	const VECTOR zero = Math::VZero();
	_name = "Camera";
	_layer = -3;
	_fov_parameter = 0.0f;
	_fov = CAMERA::FOV_MIN;
	_cameraDistanceParameter = 0.0f;
	_levelIntroDuctionParameter = 0.0f;

	_cameraMode = initCam;

	_target = zero;
	_oldPosition = zero;
	_oldTarget = zero;
	_oldUp = zero;
	_oldRotation = zero;
	_up = zero;

}

camera::~camera()
{
}

void camera::Initialize()
{
	//カメラ描画距離の設定
	DxLib::SetCameraNearFar(CAMERA::NEAR_CAMERA, CAMERA::FAR_CAMERA);
}

void camera::Process(InputManager& input)
{
	//カメラ速度倍率 ※三項演算子によりR1(Hold)入力==trueなら左辺値の倍速速度を、falseなら右辺値のデフォルト速度を代入する
	float cameraSpd =  CAMERA::SPD_DEFAULT_RETURN_TO_PLAYER_PARAMETER;
	float deltaTime = _mode->GetStepTm() * 0.001f;

	UpdateFov();

	switch (_cameraMode) {
	case CameraMode::Player:
		UpdatePlayerCamera(input, deltaTime, cameraSpd);
		break;
	default:
		break;
	}

	ObjectBase::Process(input);
}

void camera::Render()
{
	DxLib::SetCameraPositionAndTargetAndUpVec(_position, _target, _up);
}

void camera::UpdateFov()
{
	float deltaTime = _mode->GetStepTm() * 0.001f;
	//ジャンプ時のfov増減
	float decFov = CAMERA::FOV_DEFAULT + ((CAMERA::FOV_MIN - CAMERA::FOV_DEFAULT) * (1.0f - _p.GetSpdParam()));
	_fov += (decFov - _fov) * deltaTime * CAMERA::SPD_RETURN_FOV_CHANGE;

	//fovセット
	float accelerationFov = (CAMERA::FOV_MAX - CAMERA::FOV_DEFAULT) * _fov_parameter;
	float decelerationFov = _fov;
	float fov = accelerationFov + decelerationFov;
	SetupCamera_Perspective(Math::ToRadians(fov));
}

void camera::UpdatePlayerCamera(InputManager& input, float deltaTime, float camSpd)
{
	MATRIX playerRotationMatrix = _p.GetRotationMatrix();
	VECTOR playerPosition = _p.GetPosition();
	VECTOR positionFreeLook = VTransform(CAMERA::DISTANCE_FREE_LOOK, playerRotationMatrix);//フリールックモードのカメラ座標
	VECTOR distanceTps = CAMERA::DISTANCE_TPS;//TPSモードのカメラ座標
	
	VECTOR positionTps = VAdd(playerPosition, VTransform(distanceTps, playerRotationMatrix));
	VECTOR targetFPS = VAdd(playerPosition, VTransform(CAMERA::TARGET_FPS_CAMERA, playerRotationMatrix));
	VECTOR targetFreeLook = CAMERA::TARGET_FREE_LOOK;

	//※三項演算子cameraTyepがTpsならTps用の座標(左辺値)を代入する、falseなら右辺値フリールック用座標を代入する
	CameraType cameraType = _p.GetCameraStatus();
	bool isTps = cameraType == CameraType::Tps;
	VECTOR positionNotFpsCamera = isTps ? positionTps : positionFreeLook;
	VECTOR targetNotFps = isTps ? targetFPS : targetFreeLook;

	//カメラタイプにより距離成分変動
	float cameraDistanceChangeSpd = CAMERA::SPD_DISTANCE_CHANGE * deltaTime;//カメラ距離成分の修正速度
	//※三項演算子 cameraType==Fpsなら変化速度はマイナス方向、falseならプラス方向の変化になる
	cameraDistanceChangeSpd = cameraType == CameraType::Fps ? -1 * cameraDistanceChangeSpd : cameraDistanceChangeSpd;
	//landingアニメーション中はカメラ距離成分は二倍
	float max = _p.GetStatus() == Status::Landing ? 2.0f : 1.0f;

	_cameraDistanceParameter += cameraDistanceChangeSpd;
	_cameraDistanceParameter = Math::Clamp(_cameraDistanceParameter, 0.0f, max);

	//距離成分の結果を代入する//_cameraDistanceParameterが0ならプレイヤー準拠、1ならカメラモード準拠
	_up = VTransform(Math::VUp(), playerRotationMatrix);//上方向のベクトル
	_position = Math::Lerp(playerPosition, positionNotFpsCamera, _cameraDistanceParameter);
	_target = Math::Lerp(targetFPS, targetNotFps, _cameraDistanceParameter);
}

