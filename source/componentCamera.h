#pragma once
namespace CAMERA
{
	//cameraStatus
	constexpr float NEAR_CAMERA = 1.0f;          //�J�����`��ŒZ����
	constexpr float FAR_CAMERA = 3000.0f;        //�J�����`��Œ�����
	constexpr float SPD_DISTANCE_CHANGE = 5.0f;//�J���������ϓ����x
	//FPS
	constexpr float LOOK_FORWARD_Z = -30.0f;      //FPS�������_���v���C���[����ǂꂾ������Ă��邩
	constexpr VECTOR TARGET_FPS_CAMERA = { 0.0f, 0.0f, CAMERA::LOOK_FORWARD_Z }; //�������W
	//TPS
	constexpr float DISTANCE_TPS_Z = 100.0f;     //TPS�n�_���̃v���C���[�Ƃ�Z������
	constexpr float DISTANCE_TPS_Y = 50.0f;      //TPS�n�_���̃J�������W���ǂꂾ�������u����
	constexpr VECTOR DISTANCE_TPS = { 0.0f, DISTANCE_TPS_Y, CAMERA::DISTANCE_TPS_Z }; //�������W
	//FREE_LOOK
	constexpr float DISTANCE_FREE_LOOK_Z = 450.0f;         //�t���[���b�N�n�_����Z������
	constexpr VECTOR DISTANCE_FREE_LOOK = { 0.0f, 0.0f, CAMERA::DISTANCE_FREE_LOOK_Z }; //�������W
	constexpr VECTOR TARGET_FREE_LOOK = { 0.0f, 0.0f, 0.0f }; //FREE_LOOK���̒����_

	constexpr float SPD_DEFAULT_RETURN_TO_PLAYER_PARAMETER = 1.0f;//�ʏ펞�̃v���C���[�փJ�����ǐՂ��߂�J�������x

	//fov
	constexpr float FOV_DEFAULT = 60.0f;//�f�t�H���g��fov
	constexpr float FOV_MIN = 20.0f;//���x�ω��ɂ�鎋��ύX���o���̍Œ�fov
	constexpr float FOV_MAX = 150.0f;//���x�ω��ɂ�鎋��ύX���o���̍ō�fov
	constexpr float MAX_COMBO_IN_MAX_FOV = 10.0f;//�ő压��p���B���̍ő�R���{��
	constexpr float SPD_FOV_CHANGE = 10.0f;//���x�����ɂ��fov�̕ω����x
	constexpr float SPD_RETURN_FOV_CHANGE = 5.0f;//���x�����ɂ��fov�̕ω����x
}

enum class CameraMode 
{
	Player,
	Enemy,
	Game,
	Null
};

class CameraComponent : public GameComponentBase
{
public:
	CameraComponent();
	~CameraComponent();
	bool Initialize()override;
	void Process(InputManager& input)override;
	void Render()override;
	void PadInput(InputManager& input);
	

	//�v���C���[�Ǐ]�J�����̍X�V
	void ProcessPlayerCamera(InputManager& input, float deltaTime, float camSpd);

	//�J�����ʒu�ݒ�
	void SetPosition(VECTOR position) { _position = position; };
	//�J�����ʒu�擾
	inline VECTOR GetPosition()const { return _position; };
	/**
    * \brief �J�����̒����_��ݒ肷��
    * \param target �����_�ɂȂ���W
    * \param forward �J�����̌���
    */
	inline void SetTarget(VECTOR target) { _target = target; }
	/**
    * \brief �J�����̒����_�̎擾
    * \return �J�����̒����_
	*/
	inline VECTOR GetTarget() const { return _target; }
	/**
	 * \brief �����_�����̃x�N�g���̎擾
	 * \return �����_�����̒P�ʃx�N�g��
	 */
	Math::Vector4 GetForward() const {
		auto vec = Math::ToMath(_target) - Math::ToMath(_position);
		vec.Normalized();
		return vec;
	}

	void SetCameraMode(CameraMode cam) {
		_cameraMode = cam;
	}
private:
	float _fov_parameter;//fov�p�����[�^�[
	float _fov;          //����p
	float _cameraDistanceParameter;//�J���������p�����[�^�[
	VECTOR _position;
	VECTOR _target;  //�����_
	VECTOR _oldPosition, _oldTarget, _oldUp, _oldRotation;
	VECTOR _up;//�J�����̏�����x�N�g��

	double _upDownAngle{ 0.0 };                                        //!< �J�����̏㉺�̉�]�̊p�x
	double _sideAngle{ 0.0 };                                          //!< �J�����̍��E�̉�]�̊p�x
	Math::Matrix44 _anyAxisMatrix{ Math::Matrix44() };                             //!< �x�N�g����90�x��]�����邽�߂̃}�g���N�X

	CameraMode _cameraMode;//�J�������[�h
	gameMain _gm;
};
