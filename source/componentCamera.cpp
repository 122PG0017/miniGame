#include "componentCamera.h"

CameraComponent::CameraComponent():_position{0,0,0}
{
	const VECTOR zero = Math::VZero();
	_fov_parameter = 0.0f;
	_fov = CAMERA::FOV_MIN;

	_target = zero;
	_oldPosition = zero;
	_oldTarget = zero;
	_oldUp = zero;
	_oldRotation = zero;
	_up = zero;

	_cameraMode = CameraMode::Null;
}

CameraComponent::~CameraComponent()
{
}

bool CameraComponent::Initialize()
{ 
	//カメラ描画距離の設定
	DxLib::SetCameraNearFar(CAMERA::NEAR_CAMERA, CAMERA::FAR_CAMERA);
	return true;
}

void CameraComponent::Process(InputManager& input)
{
	//カメラ速度倍率
	float cameraSpd = CAMERA::SPD_DEFAULT_RETURN_TO_PLAYER_PARAMETER;
	float deltaTime = _parent->GetMode()->GetStepTm() * 0.001f;

    // ビュー行列の設定
    auto cameraMatrix = GetCameraViewMatrix();
    SetCameraViewMatrix(cameraMatrix);


    //fovセット
    float accelerationFov = (CAMERA::FOV_MAX - CAMERA::FOV_DEFAULT) * _fov_parameter;
    float decelerationFov = _fov;
    float fov = accelerationFov + decelerationFov;
    SetupCamera_Perspective(Math::ToRadians(fov));


	switch (_cameraMode) {
	case CameraMode::Player:
		ProcessPlayerCamera(input, deltaTime, cameraSpd);
        //KeyBoardInput(input,cameraSpd);
		break;
	default:
		break;
	}

	// 3Dサウンドのリスナー設定(カメラと同一)
	DxLib::Set3DSoundListenerPosAndFrontPosAndUpVec(_position,_target,_up);
}

void CameraComponent::Render()
{
    SetCameraPositionAndTarget_UpVecY(_position,_target);
    //VECTOR tmptarget = VGet(0, 100, 0);
	//DxLib::SetCameraPositionAndTargetAndUpVec(_position,VAdd(_target,tmptarget), _up);
}


void CameraComponent::ProcessPlayerCamera(InputManager& input, float deltaTime, float camSpd)
{
    KeyBoardInput(input, camSpd);
    //MouseInput(input);

    MATRIX playerRotationMatrix = _parent->GetRotationMatrix();
    VECTOR playerPosition = _parent->GetPosition();
    VECTOR Direction = CAMERA::DISTANCE_TPS;//TPSモードのカメラ座標

    // 注視点の座標はプレイヤー座標
   _target = playerPosition;
   _target.y += 100;

    // Ｘ軸回転行列
    MATRIX MatrixX = MGetRotX(_upDownAngle);
    // Ｙ軸回転行列
    MATRIX MatrixY = MGetRotY(_sideAngle);
    // 行列の合成
    _cameraMatrix = MMult(MatrixX, MatrixY);
    // 基準ベクトルを行列で変換
    Direction = VTransform(Direction, _cameraMatrix);

   // カメラ座標はプレイヤー座標から変換した座標を足したところ
    _position = VAdd(_parent->GetPosition(), Direction);

    /*VECTOR positionTps = VAdd(playerPosition, VTransform(distanceTps, playerRotationMatrix));
    VECTOR targetFPS = VAdd(playerPosition, VTransform(CAMERA::TARGET_FPS_CAMERA, playerRotationMatrix));

    VECTOR positionNotFpsCamera = positionTps;
    VECTOR targetNotFps = targetFPS;

    //カメラタイプにより距離成分変動
    float cameraDistanceChangeSpd = CAMERA::SPD_DISTANCE_CHANGE * deltaTime;//カメラ距離成分の修正速度
    //※三項演算子 cameraType==Fpsなら変化速度はマイナス方向、falseならプラス方向の変化になる
    cameraDistanceChangeSpd = cameraDistanceChangeSpd;
    float max = 1.0f;

    _cameraDistanceParameter += cameraDistanceChangeSpd;
    _cameraDistanceParameter = Math::Clamp(_cameraDistanceParameter, 0.0f, max);

    //距離成分の結果を代入する
    _up = VTransform(Math::VUp(), playerRotationMatrix);//上方向のベクトル
    _position = Math::Lerp(playerPosition, positionNotFpsCamera, _cameraDistanceParameter);
    _target = Math::Lerp(targetFPS, targetNotFps, _cameraDistanceParameter);*/

}


void CameraComponent::KeyBoardInput(InputManager& input,float cameraspd)
{
    // 左右キーで向きの変更
    if (input.GetKeyUp(InputState::Hold))
    {
        _upDownAngle -= Math::ToRadians(cameraspd);
    }
    else if (input.GetKeyDown(InputState::Hold))
    {
        _upDownAngle += Math::ToRadians(cameraspd);
    }
    if (input.GetKeyRight(InputState::Hold))
    {
        _sideAngle -= Math::ToRadians(cameraspd);
    }
    else if (input.GetKeyLeft(InputState::Hold))
    {
        _sideAngle += Math::ToRadians(cameraspd);
    }
    _upDownAngle = Math::Clamp(_upDownAngle, -120.0, 120.0);

   

    // 注視点の座標はプレイヤー座標
    //_target = _parent->GetPosition();
    //_target.y += 100;

    // 基準のベクトル
    //VECTOR Direction = VGet(0.0f, 500.0f, 1000.0f);

    // Ｘ軸回転行列
    //MATRIX MatrixX = MGetRotX(_upDownAngle);
    // Ｙ軸回転行列
    //MATRIX MatrixY = MGetRotY(_sideAngle);
    // 行列の合成
    //_cameraMatrix = MMult(MatrixX, MatrixY);
    // 基準ベクトルを行列で変換
    //Direction = VTransform(Direction, Matrix);

    // カメラ座標はプレイヤー座標から変換した座標を足したところ
    //_position = VAdd(_parent->GetPosition(), Direction);
}

void CameraComponent::MouseInput(InputManager& input)
{
    int Disp_x;
    int Disp_y;
    int frame =60;
    GetWindowSize(&Disp_x,&Disp_y);
    //auto MouseXY = Math::Clamp(input.GetMouseXY(),0,0);
    //_upDownAngle = Math::Clamp(MouseXY.x - Disp_x / 2, -120, 120) * 1 / frame;
    //_sideAngle = Math::Clamp(MouseXY.y - Disp_y / 2, -120, 120) * 1 / frame;
    input.SetMouseX(Disp_x / 2);
    input.SetMouseX(Disp_y / 2);
    if (input.GetKeyAt(InputState::Hold)) 
    {
        SetMouseDispFlag(TRUE);
    }
    else
    {
        SetMouseDispFlag(FALSE);
    }
    // Ｘ軸回転行列
    //MATRIX MatrixX = MGetRotX(_upDownAngle);
    // Ｙ軸回転行列
    //MATRIX MatrixY = MGetRotY(_sideAngle);
    // 行列の合成
    //_cameraMatrix = MMult(MatrixX, MatrixY);
    //_parent->SetRotationMatrix(_rotMatrix);
}
