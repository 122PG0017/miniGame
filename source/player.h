#pragma once
namespace PLAYER {
	constexpr float SIZE = 0.3f;  //�X�P�[���{��
	constexpr int SIDE_NUMBER = 6;//�ʂ̐�

	constexpr float SPD_MOVE = 350.0f;        //�ړ����x
	constexpr float SPD_ROTATION = 3.0f;      //��]���x
	constexpr float ADAPT_STICK = 0.00001f;//�X�e�B�b�N�̒l����]�����ɂ��傤�Ǘǂ��{���ɂ���

	constexpr float LENGTH_START_LAND_ANIM = 110.0;//���n�A�j���[�V�����n������
	constexpr float LENGTH_LINE = 1000.0f;         //�ǂƂ̏Փˋ�������p�����̑傫��

	constexpr float SPD_IDLE_PARAMETER = 1.0f;//���n���ォ��ҋ@��Ԃ֑J�ڂ��鑬�x
	constexpr float SPD_CHANGE_VALUE_EXTEND_PARAMETER = 10.0f;//���_�؂�ւ����̊g����]�l��ԑ��x

	constexpr float SPD_VISUAL_ROTATION_PARAMETER = 1.0f;//�����ڏ��]�l�̏C�����x

	constexpr float END_TIME_LANDING_ANIM = 50.0f;//���n�A�j���[�V�����̏I������


}

//�J�����X�e�[�^�X
enum class CameraType
{
	Fps,//��l��
	Tps,//�O�l��
	FreeLook,//�X�e�[�W�����𒍎��_�ɂ����_���_
	MAX,
};
//�v���C���[�̏��
enum class Status
{
	Idle,    //�ҋ@
	Jump,    //�W�����v��
	Landing, //���n��
	MAX,     //�X�e�[�^�X�̌�//MAX�͔z��ɓo�^���Ȃ�
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
	//float _spdParam;                         //�����x�{��
	VECTOR vec;
	modelInf _modelInf;
	Rserver RS;
};