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
	DxLib::SetCameraPositionAndTargetAndUpVec(_position,_target, _up);
}

void CameraComponent::Input(InputManager& input)
{
    float DefoltDeadZone = 0.0f;
    // ゲーム内感度の取得
    auto [cameraSens, aimSens, deadZone] = _gm.sensitivity();
    // デッドゾーンの範囲を設定するためにデフォルトのデットゾーンに掛ける値の設定
    auto deadZoneMulti = DefoltDeadZone / deadZone;
    // 右スティックが上に傾いていたらカメラの上下の回転の角度を増やす
    // デッドゾーン以上でパッドのスティックの入力範囲を分割した範囲の最初の範囲内だった場合
    if (input.GetXboxStickR().y >= deadZone && input.GetXboxStickL().y < deadZone * deadZoneMulti) {
        // カメラ感度を0.2倍したものを足す
        _upDownAngle += cameraSens * 0.2;
        // 10度以上傾いていたら10度にする
        if (_upDownAngle >= 10.0) {
            _upDownAngle = 10.0;
        }
    }
    // パッドのスティックの入力範囲を分割した範囲の二つ目の範囲内だった場合
    else if (input.GetXboxStickL().y >= deadZone * deadZoneMulti && input.GetXboxStickL().y < deadZone * deadZoneMulti * 2) {
        // カメラ感度を0.4倍したものを足す
        _upDownAngle += cameraSens * 0.4;
        // 10度以上傾いていたら10度にする
        if (_upDownAngle >= 10.0) {
            _upDownAngle = 10.0;
        }
    }
    // パッドのスティックの入力範囲を分割した範囲の三つ目の範囲内だった場合
    else if (input.GetXboxStickL().y >= deadZone * deadZoneMulti * 2 && input.GetXboxStickL().y < deadZone * deadZoneMulti * 3) {
        // カメラ感度を0.6倍したものを足す
        _upDownAngle += cameraSens * 0.6;
        // 10度以上傾いていたら10度にする
        if (_upDownAngle >= 10.0) {
            _upDownAngle = 10.0;
        }
    }
    // パッドのスティックの入力範囲を分割した範囲の四つ目の範囲内だった場合
    else if (input.GetXboxStickL().y >= deadZone * deadZoneMulti * 3 && input.GetXboxStickL().y < deadZone * deadZoneMulti * 4) {
        // カメラ感度を0.8倍したものを足す
        _upDownAngle += cameraSens * 0.8;
        // 10度以上傾いていたら10度にする
        if (_upDownAngle >= 10.0) {
            _upDownAngle = 10.0;
        }
    }
    // パッドのスティックの入力範囲を分割した範囲の四つ目の範囲より大きかった場合
    else if (input.GetXboxStickL().y >= deadZone * deadZoneMulti * 4) {
        // カメラ感度を足す
        _upDownAngle += cameraSens;
        // 10度以上傾いていたら10度にする
        if (_upDownAngle >= 10.0) {
            _upDownAngle = 10.0;
        }
    }
    // 右スティックが下に傾いていたらカメラの上下の回転の角度を減らす
    // デッドゾーン以下でパッドのスティックの入力範囲を分割した範囲の最初の範囲内だった場合
    if (input.GetXboxStickL().y <= -deadZone && input.GetXboxStickL().y > -deadZone * deadZoneMulti) {
        // カメラ感度を0.2倍したものを引く
        _upDownAngle -= cameraSens * 0.2;
        // -20度以上傾いていたら-20度にする
        if (_upDownAngle <= -20.0) {
            _upDownAngle = -20.0;
        }
    }
    // パッドのスティックの入力範囲を分割した範囲の二つ目の範囲内だった場合
    else if (input.GetXboxStickL().y <= -deadZone * deadZoneMulti && input.GetXboxStickL().y > -deadZone * deadZoneMulti * 2) {
        // カメラ感度を0.4倍したものを引く
        _upDownAngle -= cameraSens * 0.4;
        // -20度以上傾いていたら-20度にする
        if (_upDownAngle <= -20.0) {
            _upDownAngle = -20.0;
        }
    }
    // パッドのスティックの入力範囲を分割した範囲の三つ目の範囲内だった場合
    else if (input.GetXboxStickL().y <= -deadZone * deadZoneMulti * 2 && input.GetXboxStickL().y > -deadZone * deadZoneMulti * 3) {
        // カメラ感度を0.6倍したものを引く
        _upDownAngle -= cameraSens * 0.6;
        // -20度以上傾いていたら-20度にする
        if (_upDownAngle <= -20.0) {
            _upDownAngle = -20.0;
        }
    }
    // パッドのスティックの入力範囲を分割した範囲の四つ目の範囲内だった場合
    else if (input.GetXboxStickL().y <= -deadZone * deadZoneMulti * 3 && input.GetXboxStickL().y > -deadZone * deadZoneMulti * 4) {
        // カメラ感度を0.8倍したものを引く
        _upDownAngle -= cameraSens * 0.8;
        // -20度以上傾いていたら-20度にする
        if (_upDownAngle <= -20.0) {
            _upDownAngle = -20.0;
        }
    }
    // パッドのスティックの入力範囲を分割した範囲の四つ目の範囲より小さかった場合
    else if (input.GetXboxStickL().y <= -deadZone * deadZoneMulti * 4) {
        // カメラ感度を引く
        _upDownAngle -= cameraSens;
        // -20度以上傾いていたら-20度にする
        if (_upDownAngle <= -20.0) {
            _upDownAngle = -20.0;
        }
    }
    // 右スティックが右に傾いていたらカメラの左右の回転の角度を減らす
    // デッドゾーン以上でパッドのスティックの入力範囲を分割した範囲の最初の範囲内だった場合
    if (input.GetXboxStickL().x >= deadZone && input.GetXboxStickL().x < deadZone * deadZoneMulti) {
        // カメラ感度を0.2倍したものを引く
        _sideAngle -= cameraSens * 0.2;
        // -360度以下になったら0度にする
        if (_sideAngle <= -360.0) {
            _sideAngle = 0.0;
        }
    }
    // パッドのスティックの入力範囲を分割した範囲の二つ目の範囲内だった場合
    else if (input.GetXboxStickL().x >= deadZone * deadZoneMulti && input.GetXboxStickL().x < deadZone * deadZoneMulti * 2) {
        // カメラ感度を0.4倍したものを引く
        _sideAngle -= cameraSens * 0.4;
        //-360度以下になったら0度にする
        if (_sideAngle <= -360.0) {
            _sideAngle = 0.0;
        }
    }
    // パッドのスティックの入力範囲を分割した範囲の三つ目の範囲内だった場合
    else if (input.GetXboxStickL().x >= deadZone * deadZoneMulti * 2 && input.GetXboxStickL().x < deadZone * deadZoneMulti * 3) {
        // カメラ感度を0.6倍したものを引く
        _sideAngle -= cameraSens * 0.6;
        // -360度以下になったら0度にする
        if (_sideAngle <= -360.0) {
            _sideAngle = 0.0;
        }
    }
    // パッドのスティックの入力範囲を分割した範囲の四つ目の範囲内だった場合
    else if (input.GetXboxStickL().x >= deadZone * deadZoneMulti * 3 && input.GetXboxStickL().x < deadZone * deadZoneMulti * 4) {
        // カメラ感度を0.8倍したものを引く
        _sideAngle -= cameraSens * 0.8;
        // -360度以下になったら0度にする
        if (_sideAngle <= -360.0) {
            _sideAngle = 0.0;
        }
    }
    // パッドのスティックの入力範囲を分割した範囲の四つ目の範囲より大きかった場合
    else if (input.GetXboxStickL().x >= deadZone * deadZoneMulti * 4) {
        // カメラ感度を引く
        _sideAngle -= cameraSens;
        // -360度以下になったら0度にする
        if (_sideAngle <= -360.0) {
            _sideAngle = 0.0;
        }
    }
    // 右スティックが左に傾いていたらカメラの左右の回転の角度を増やす
    // デッドゾーン以下でパッドのスティックの入力範囲を分割した範囲の最初の範囲内だった場合
    if (input.GetXboxStickL().x <= -deadZone && input.GetXboxStickL().x > -deadZone * deadZoneMulti) {
        // カメラ感度を0.2倍したものを足す
        _sideAngle += cameraSens * 0.2;
        // 360度以上になったら0度にする
        if (_sideAngle >= 360.0) {
            _sideAngle = 0.0;
        }
    }
    // パッドのスティックの入力範囲を分割した範囲の二つ目の範囲内だった場合
    else if (input.GetXboxStickL().x <= -deadZone * deadZoneMulti && input.GetXboxStickL().x > -deadZone * deadZoneMulti * 2) {
        // カメラ感度を0.4倍したものを足す
        _sideAngle += cameraSens * 0.4;
        // 360度以上になったら0度にする
        if (_sideAngle >= 360.0) {
            _sideAngle = 0.0;
        }
    }
    // パッドのスティックの入力範囲を分割した範囲の三つ目の範囲内だった場合
    else if (input.GetXboxStickL().x <= -deadZone * deadZoneMulti * 2 && input.GetXboxStickL().x > -deadZone * deadZoneMulti * 3) {
        // カメラ感度を0.6倍したものを足す
        _sideAngle += cameraSens * 0.6;
        // 360度以上になったら0度にする
        if (_sideAngle >= 360.0) {
            _sideAngle = 0.0;
        }
    }
    // パッドのスティックの入力範囲を分割した範囲の四つ目の範囲内だった場合
    else if (input.GetXboxStickL().x <= -deadZone * deadZoneMulti * 3 && input.GetXboxStickL().x > -deadZone * deadZoneMulti * 4) {
        // カメラ感度を0.8倍したものを足す
        _sideAngle += cameraSens * 0.8;
        // 360度以上になったら0度にする
        if (_sideAngle >= 360.0) {
            _sideAngle = 0.0;
        }
    }
    // パッドのスティックの入力範囲を分割した範囲の四つ目の範囲より小さかった場合
    else if (input.GetXboxStickL().x <= -deadZone * deadZoneMulti * 4) {
        // カメラ感度を足す
        _sideAngle += cameraSens;
        // 360度以上になったら0度にする
        if (_sideAngle >= 360.0) {
            _sideAngle = 0.0;
        }
    }
    // カメラの位置から注視点へのベクトル作成
    auto posToTarget = _target - _position;
    // カメラの位置から注視点へのベクトルを90度回転させる
    auto anyAxisVec = posToTarget * _anyAxisMatrix;
    // 上下の回転のマトリクス作成
    Matrix44 rotateUpDown = Matrix44();
    rotateUpDown.RotateAnyVecQuaternion(anyAxisVec, _upDownAngle, true);
    // 左右の回転のマトリクス作成
    Matrix44 rotateSide = Matrix44();
    rotateSide.RotateAnyVecQuaternion(Vector4(0.0, 1.0, 0.0), _sideAngle, true);
    // 上下の回転と左右の回転を合わせたマトリクスを作成
    _rotateMatrix = rotateSide * rotateUpDown;
}

void CameraComponent::Vibration() 
{
	const auto DivideT =0.0;
	// オイラー法の時間の分割数分for文を回す
	for (auto i = 0.0; i < DivideT; ++i) {
		// 時間の分割数で割った速度をYの位置に足していく
		_vibrationValue += _vibrationVelocity / DivideT;
		// 速度に時間の分割数で割ったYの位置から自然長を引いたものにばね定数を掛けたものを足していく
		_vibrationVelocity += (-0.0 * (_vibrationValue - 0.0)) / DivideT;
	}
	// 速度を減衰させる
	_vibrationVelocity *= 0.9;
}

void CameraComponent::ProcessPlayerCamera(InputManager& input, float deltaTime, float camSpd)
{


	//距離成分の結果を代入する//_cameraDistanceParameterが0ならプレイヤー準拠、1ならカメラモード準拠
	_up = VTransform(Math::VUp(), playerRotationMatrix);//上方向のベクトル
	_position = Math::Lerp(playerPosition, positionNotFpsCamera, _cameraDistanceParameter);
	_target = Math::Lerp(targetFPS, targetNotFps, _cameraDistanceParameter);
}
