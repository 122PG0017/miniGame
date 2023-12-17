#pragma once
namespace CAMERA
{
	//cameraStatus
	constexpr float NEAR_CAMERA = 1.0f;          //カメラ描画最短距離
	constexpr float FAR_CAMERA = 3000.0f;        //カメラ描画最長距離
	constexpr float SPD_DISTANCE_CHANGE = 5.0f;//カメラ距離変動速度
	//FPS
	constexpr float LOOK_FORWARD_Z = -30.0f;      //FPS時注視点がプレイヤーからどれだけ離れているか
	constexpr VECTOR TARGET_FPS_CAMERA = { 0.0f, 0.0f, CAMERA::LOOK_FORWARD_Z }; //距離座標
	//TPS
	constexpr float DISTANCE_TPS_Z = 100.0f;     //TPS始点時のプレイヤーとのZ軸距離
	constexpr float DISTANCE_TPS_Y = 50.0f;      //TPS始点時のカメラ座標をどれだけ高く置くか
	constexpr VECTOR DISTANCE_TPS = { 0.0f, DISTANCE_TPS_Y, CAMERA::DISTANCE_TPS_Z }; //距離座標
	//FREE_LOOK
	constexpr float DISTANCE_FREE_LOOK_Z = 450.0f;         //フリールック始点時のZ軸距離
	constexpr VECTOR DISTANCE_FREE_LOOK = { 0.0f, 0.0f, CAMERA::DISTANCE_FREE_LOOK_Z }; //距離座標
	constexpr VECTOR TARGET_FREE_LOOK = { 0.0f, 0.0f, 0.0f }; //FREE_LOOK時の注視点

	constexpr float SPD_DEFAULT_RETURN_TO_PLAYER_PARAMETER = 1.0f;//通常時のプレイヤーへカメラ追跡が戻るカメラ速度

	//fov
	constexpr float FOV_DEFAULT = 60.0f;//デフォルトのfov
	constexpr float FOV_MIN = 20.0f;//速度変化による視野変更演出時の最低fov
	constexpr float FOV_MAX = 150.0f;//速度変化による視野変更演出時の最高fov
	constexpr float MAX_COMBO_IN_MAX_FOV = 10.0f;//最大視野角到達時の最大コンボ量
	constexpr float SPD_FOV_CHANGE = 10.0f;//速度増加によるfovの変化速度
	constexpr float SPD_RETURN_FOV_CHANGE = 5.0f;//速度増減によるfovの変化速度
}

enum class CameraMode 
{
	Player,
	Enemy,
	Game
};

class camera : public gameObjectBase
{
public:
	camera(Player& p, CameraMode initCam);
	~camera();
	void Initialize()override;
	void Process(InputManager& input)override;
	void Render()override;

	//速度増減に合わせたfovの更新
	void UpdateFov();
	//プレイヤー追従カメラの更新
	void UpdatePlayerCamera(InputManager& input, float deltaTime, float camSpd);
	//他カメラモードからプレイヤーカメラへ帰還する時の更新
	//void UpdateReturn2PlayerCamera(InputManager& input, float deltaTime, float camSpd);

	void SetCameraMode(CameraMode cam) {
		_cameraMode = cam; _cameraDistanceParameter = 0;
	}

private:
	float _fov_parameter;//fovパラメーター
	float _fov;          //視野角
	float _cameraDistanceParameter;//カメラ距離パラメーター
	float _levelIntroDuctionParameter;//ステージ紹介カメラの回転パラメーター

	CameraMode _cameraMode;//カメラモード

	VECTOR _target;//注視点
	VECTOR _oldPosition, _oldTarget, _oldUp, _oldRotation;//帰還カメラ用の古いカメラ情報ステータス
	VECTOR _up;//カメラの上方向ベクトル

	Player& _p;//プレイヤー
};
