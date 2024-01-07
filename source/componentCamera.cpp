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
    //VECTOR playerPosition = _parent->GetPosition();
    //// プレイヤーからのカメラの注視点へのベクトルを作成
    //_firstPlyToTarget =VSub(_target ,playerPosition);
    //// プレイヤーからのカメラの位置へのベクトルを作成
    //_firstPlyToPos = VSub(_position , playerPosition);
    //// ベクトルを90度回転させるマトリクスの作成
    //_anyAxisMatrix.RotateY(90.0, true);
    //// カメラの位置から注視点へのベクトルの作成
    //Math::Vector4 posToTarget = Math::ToMath(_target) - Math::ToMath(_position);
    //posToTarget.Normalized();
    //_posToTarget = posToTarget * 300.0;
    //// ベクトルを90度回転させるマトリクスの作成
    //_anyAxisMatrix.RotateY(90.0, true);
    
   

	//カメラ描画距離の設定
	DxLib::SetCameraNearFar(CAMERA::NEAR_CAMERA, CAMERA::FAR_CAMERA);
	return true;
}

void CameraComponent::Process(InputManager& input)
{
    //PadInput(input);
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
		break;
	default:
		break;
	}

	// 3Dサウンドのリスナー設定(カメラと同一)
	DxLib::Set3DSoundListenerPosAndFrontPosAndUpVec(_position,_target,_up);
}

void CameraComponent::Render()
{
    //SetCameraPositionAndTarget_UpVecY({ 0.0f, 500.0f, 50.0f }, { 0.0f, 0.0f, 0.0f });
	DxLib::SetCameraPositionAndTargetAndUpVec(_position,_target, _up);
}


void CameraComponent::ProcessPlayerCamera(InputManager& input, float deltaTime, float camSpd)
{

    MouseInput(input);

    MATRIX playerRotationMatrix = _parent->GetRotationMatrix();
    VECTOR playerPosition = _parent->GetPosition();
    VECTOR distanceTps = CAMERA::DISTANCE_TPS;//TPSモードのカメラ座標

    VECTOR positionTps = VAdd(playerPosition, VTransform(distanceTps, playerRotationMatrix));
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

    //距離成分の結果を代入する//_cameraDistanceParameterが0ならプレイヤー準拠、1ならカメラモード準拠
    _up = VTransform(Math::VUp(), playerRotationMatrix);//上方向のベクトル
    _position = Math::Lerp(playerPosition, positionNotFpsCamera, _cameraDistanceParameter);
    _target = Math::Lerp(targetFPS, targetNotFps, _cameraDistanceParameter);

}

void CameraComponent::PadInput(InputManager& input)
{
    float DefoltDeadZone = 0.0f;
    // ゲーム内感度の取得
    auto [cameraSens, aimSens, deadZone] = _gm.sensitivity();
    // デッドゾーンの範囲を設定するためにデフォルトのデットゾーンに掛ける値の設定
    auto deadZoneMulti = DefoltDeadZone / deadZone;
    // 右スティックが上に傾いていたらカメラの上下の回転の角度を増やす
    // デッドゾーン以上でパッドのスティックの入力範囲を分割した範囲の最初の範囲内だった場合
    if (input.GetXboxStickR().y >= deadZone && input.GetXboxStickR().y < deadZone * deadZoneMulti) {
        // カメラ感度を0.2倍したものを足す
        _upDownAngle += cameraSens * 0.2;
        // 10度以上傾いていたら10度にする
        if (_upDownAngle >= 10.0) {
            _upDownAngle = 10.0;
        }
    }
    // パッドのスティックの入力範囲を分割した範囲の二つ目の範囲内だった場合
    else if (input.GetXboxStickR().y >= deadZone * deadZoneMulti && input.GetXboxStickR().y < deadZone * deadZoneMulti * 2) {
        // カメラ感度を0.4倍したものを足す
        _upDownAngle += cameraSens * 0.4;
        // 10度以上傾いていたら10度にする
        if (_upDownAngle >= 10.0) {
            _upDownAngle = 10.0;
        }
    }
    // パッドのスティックの入力範囲を分割した範囲の三つ目の範囲内だった場合
    else if (input.GetXboxStickR().y >= deadZone * deadZoneMulti * 2 && input.GetXboxStickR().y < deadZone * deadZoneMulti * 3) {
        // カメラ感度を0.6倍したものを足す
        _upDownAngle += cameraSens * 0.6;
        // 10度以上傾いていたら10度にする
        if (_upDownAngle >= 10.0) {
            _upDownAngle = 10.0;
        }
    }
    // パッドのスティックの入力範囲を分割した範囲の四つ目の範囲内だった場合
    else if (input.GetXboxStickR().y >= deadZone * deadZoneMulti * 3 && input.GetXboxStickR().y < deadZone * deadZoneMulti * 4) {
        // カメラ感度を0.8倍したものを足す
        _upDownAngle += cameraSens * 0.8;
        // 10度以上傾いていたら10度にする
        if (_upDownAngle >= 10.0) {
            _upDownAngle = 10.0;
        }
    }
    // パッドのスティックの入力範囲を分割した範囲の四つ目の範囲より大きかった場合
    else if (input.GetXboxStickR().y >= deadZone * deadZoneMulti * 4) {
        // カメラ感度を足す
        _upDownAngle += cameraSens;
        // 10度以上傾いていたら10度にする
        if (_upDownAngle >= 10.0) {
            _upDownAngle = 10.0;
        }
    }
    // 右スティックが下に傾いていたらカメラの上下の回転の角度を減らす
    // デッドゾーン以下でパッドのスティックの入力範囲を分割した範囲の最初の範囲内だった場合
    if (input.GetXboxStickR().y <= -deadZone && input.GetXboxStickR().y > -deadZone * deadZoneMulti) {
        // カメラ感度を0.2倍したものを引く
        _upDownAngle -= cameraSens * 0.2;
        // -20度以上傾いていたら-20度にする
        if (_upDownAngle <= -20.0) {
            _upDownAngle = -20.0;
        }
    }
    // パッドのスティックの入力範囲を分割した範囲の二つ目の範囲内だった場合
    else if (input.GetXboxStickR().y <= -deadZone * deadZoneMulti && input.GetXboxStickR().y > -deadZone * deadZoneMulti * 2) {
        // カメラ感度を0.4倍したものを引く
        _upDownAngle -= cameraSens * 0.4;
        // -20度以上傾いていたら-20度にする
        if (_upDownAngle <= -20.0) {
            _upDownAngle = -20.0;
        }
    }
    // パッドのスティックの入力範囲を分割した範囲の三つ目の範囲内だった場合
    else if (input.GetXboxStickR().y <= -deadZone * deadZoneMulti * 2 && input.GetXboxStickR().y > -deadZone * deadZoneMulti * 3) {
        // カメラ感度を0.6倍したものを引く
        _upDownAngle -= cameraSens * 0.6;
        // -20度以上傾いていたら-20度にする
        if (_upDownAngle <= -20.0) {
            _upDownAngle = -20.0;
        }
    }
    // パッドのスティックの入力範囲を分割した範囲の四つ目の範囲内だった場合
    else if (input.GetXboxStickR().y <= -deadZone * deadZoneMulti * 3 && input.GetXboxStickR().y > -deadZone * deadZoneMulti * 4) {
        // カメラ感度を0.8倍したものを引く
        _upDownAngle -= cameraSens * 0.8;
        // -20度以上傾いていたら-20度にする
        if (_upDownAngle <= -20.0) {
            _upDownAngle = -20.0;
        }
    }
    // パッドのスティックの入力範囲を分割した範囲の四つ目の範囲より小さかった場合
    else if (input.GetXboxStickR().y <= -deadZone * deadZoneMulti * 4) {
        // カメラ感度を引く
        _upDownAngle -= cameraSens;
        // -20度以上傾いていたら-20度にする
        if (_upDownAngle <= -20.0) {
            _upDownAngle = -20.0;
        }
    }
    // 右スティックが右に傾いていたらカメラの左右の回転の角度を減らす
    // デッドゾーン以上でパッドのスティックの入力範囲を分割した範囲の最初の範囲内だった場合
    if (input.GetXboxStickR().x >= deadZone && input.GetXboxStickR().x < deadZone * deadZoneMulti) {
        // カメラ感度を0.2倍したものを引く
        _sideAngle -= cameraSens * 0.2;
        // -360度以下になったら0度にする
        if (_sideAngle <= -360.0) {
            _sideAngle = 0.0;
        }
    }
    // パッドのスティックの入力範囲を分割した範囲の二つ目の範囲内だった場合
    else if (input.GetXboxStickR().x >= deadZone * deadZoneMulti && input.GetXboxStickR().x < deadZone * deadZoneMulti * 2) {
        // カメラ感度を0.4倍したものを引く
        _sideAngle -= cameraSens * 0.4;
        //-360度以下になったら0度にする
        if (_sideAngle <= -360.0) {
            _sideAngle = 0.0;
        }
    }
    // パッドのスティックの入力範囲を分割した範囲の三つ目の範囲内だった場合
    else if (input.GetXboxStickR().x >= deadZone * deadZoneMulti * 2 && input.GetXboxStickR().x < deadZone * deadZoneMulti * 3) {
        // カメラ感度を0.6倍したものを引く
        _sideAngle -= cameraSens * 0.6;
        // -360度以下になったら0度にする
        if (_sideAngle <= -360.0) {
            _sideAngle = 0.0;
        }
    }
    // パッドのスティックの入力範囲を分割した範囲の四つ目の範囲内だった場合
    else if (input.GetXboxStickR().x >= deadZone * deadZoneMulti * 3 && input.GetXboxStickR().x < deadZone * deadZoneMulti * 4) {
        // カメラ感度を0.8倍したものを引く
        _sideAngle -= cameraSens * 0.8;
        // -360度以下になったら0度にする
        if (_sideAngle <= -360.0) {
            _sideAngle = 0.0;
        }
    }
    // パッドのスティックの入力範囲を分割した範囲の四つ目の範囲より大きかった場合
    else if (input.GetXboxStickR().x >= deadZone * deadZoneMulti * 4) {
        // カメラ感度を引く
        _sideAngle -= cameraSens;
        // -360度以下になったら0度にする
        if (_sideAngle <= -360.0) {
            _sideAngle = 0.0;
        }
    }
    // 右スティックが左に傾いていたらカメラの左右の回転の角度を増やす
    // デッドゾーン以下でパッドのスティックの入力範囲を分割した範囲の最初の範囲内だった場合
    if (input.GetXboxStickR().x <= -deadZone && input.GetXboxStickR().x > -deadZone * deadZoneMulti) {
        // カメラ感度を0.2倍したものを足す
        _sideAngle += cameraSens * 0.2;
        // 360度以上になったら0度にする
        if (_sideAngle >= 360.0) {
            _sideAngle = 0.0;
        }
    }
    // パッドのスティックの入力範囲を分割した範囲の二つ目の範囲内だった場合
    else if (input.GetXboxStickR().x <= -deadZone * deadZoneMulti && input.GetXboxStickR().x > -deadZone * deadZoneMulti * 2) {
        // カメラ感度を0.4倍したものを足す
        _sideAngle += cameraSens * 0.4;
        // 360度以上になったら0度にする
        if (_sideAngle >= 360.0) {
            _sideAngle = 0.0;
        }
    }
    // パッドのスティックの入力範囲を分割した範囲の三つ目の範囲内だった場合
    else if (input.GetXboxStickR().x <= -deadZone * deadZoneMulti * 2 && input.GetXboxStickR().x > -deadZone * deadZoneMulti * 3) {
        // カメラ感度を0.6倍したものを足す
        _sideAngle += cameraSens * 0.6;
        // 360度以上になったら0度にする
        if (_sideAngle >= 360.0) {
            _sideAngle = 0.0;
        }
    }
    // パッドのスティックの入力範囲を分割した範囲の四つ目の範囲内だった場合
    else if (input.GetXboxStickR().x <= -deadZone * deadZoneMulti * 3 && input.GetXboxStickR().x > -deadZone * deadZoneMulti * 4) {
        // カメラ感度を0.8倍したものを足す
        _sideAngle += cameraSens * 0.8;
        // 360度以上になったら0度にする
        if (_sideAngle >= 360.0) {
            _sideAngle = 0.0;
        }
    }
    // パッドのスティックの入力範囲を分割した範囲の四つ目の範囲より小さかった場合
    else if (input.GetXboxStickR().x <= -deadZone * deadZoneMulti * 4) {
        // カメラ感度を足す
        _sideAngle += cameraSens;
        // 360度以上になったら0度にする
        if (_sideAngle >= 360.0) {
            _sideAngle = 0.0;
        }
    }
    // カメラの位置から注視点へのベクトル作成
    auto posToTarget = Math::ToMath(_target) - Math::ToMath(_position);
    // カメラの位置から注視点へのベクトルを90度回転させる
    auto anyAxisVec = posToTarget * _anyAxisMatrix;
    // 上下の回転のマトリクス作成
    Math::Matrix44 rotateUpDown = Math::Matrix44();
    rotateUpDown.RotateAnyVecQuaternion(anyAxisVec, _upDownAngle, true);
    // 左右の回転のマトリクス作成
    Math::Matrix44 rotateSide = Math::Matrix44();
    rotateSide.RotateAnyVecQuaternion(Math::Vector4(0.0, 1.0, 0.0), _sideAngle, true);
    // 上下の回転と左右の回転を合わせたマトリクスを作成
    auto _rotateMatrix = rotateSide * rotateUpDown;
    _parent->SetRotationMatrix(Math::ToDX(_rotateMatrix));
}

void CameraComponent::KeyBoardInput(InputManager& input)
{
    if (input.GetKeyUp(InputState::Hold))
    {
        //_upDownAngle
    }
    else if (input.GetKeyDown(InputState::Hold))
    {

    }
    if (input.GetKeyRight(InputState::Hold))
    {

    }
    else if (input.GetKeyLeft(InputState::Hold))
    {

    }
}

void CameraComponent::MouseInput(InputManager& input)
{
    int Disp_x;
    int Disp_y;
    int frame =60;
    GetWindowSize(&Disp_x,&Disp_y);
    int mouse_x = Math::Clamp(input.GetMouseX() - Disp_x / 2, -120, 120) * 1 / frame;
    int mouse_y = Math::Clamp(input.GetMouseY() - Disp_y / 2, -120, 120) * 1 / frame;
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
    MATRIX _rotMatrix = (DxLib::MGetRotX(mouse_x), DxLib::MGetRotY(mouse_y));
    _parent->SetRotationMatrix(_rotMatrix);
}
