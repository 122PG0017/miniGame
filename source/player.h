#pragma once
namespace PLAYER {
	constexpr float SIZE = 0.3f;  //スケール倍率
	constexpr int SIDE_NUMBER = 6;//面の数

	constexpr float SPD_MOVE = 350.0f;        //移動速度
	constexpr float SPD_ROTATION = 3.0f;      //回転速度
	constexpr float ADAPT_STICK = 0.00001f;//スティックの値を回転調整にちょうど良い倍率にする

	constexpr float LENGTH_START_LAND_ANIM = 110.0;//着地アニメーション始動距離
	constexpr float LENGTH_LINE = 1000.0f;         //壁との衝突距離測定用線分の大きさ

	constexpr float SPD_IDLE_PARAMETER = 1.0f;//着地直後から待機状態へ遷移する速度
	constexpr float SPD_CHANGE_VALUE_EXTEND_PARAMETER = 10.0f;//視点切り替え時の拡張回転値補間速度

	constexpr float SPD_VISUAL_ROTATION_PARAMETER = 1.0f;//見た目上回転値の修正速度

	constexpr float END_TIME_LANDING_ANIM = 50.0f;//着地アニメーションの終了時間


}

//カメラステータス
enum class CameraType
{
	Fps,//一人称
	Tps,//三人称
	FreeLook,//ステージ中央を注視点にした神視点
	MAX,
};
//プレイヤーの状態
enum class Status
{
	Idle,    //待機
	Jump,    //ジャンプ中
	Landing, //着地中
	MAX,     //ステータスの個数//MAXは配列に登録しない
};

class Player : public GameObjectBase
{
public:
	using ObjectBase::AddComponent;
	Player();
	~Player();
	void Initialize()override;
	void Terminate()override;
	void Process(InputManager& input)override;
	void Render()override;
	void Debug() override;

	void PlayerMove(InputManager& input,float speed);

	//float GetSpdParam() { return _spdParam; }
protected:
	int Handle;
	bool isAnimEnd;
	//float _spdParam;                         //加速度倍率
	VECTOR vec;
	modelInf _modelInf;
	Rserver RS;
};