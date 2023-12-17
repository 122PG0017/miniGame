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
	//�J�����`�拗���̐ݒ�
	DxLib::SetCameraNearFar(CAMERA::NEAR_CAMERA, CAMERA::FAR_CAMERA);
}

void camera::Process(InputManager& input)
{
	//�J�������x�{�� ���O�����Z�q�ɂ��R1(Hold)����==true�Ȃ獶�Ӓl�̔{�����x���Afalse�Ȃ�E�Ӓl�̃f�t�H���g���x��������
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
	//�W�����v����fov����
	float decFov = CAMERA::FOV_DEFAULT + ((CAMERA::FOV_MIN - CAMERA::FOV_DEFAULT) * (1.0f - _p.GetSpdParam()));
	_fov += (decFov - _fov) * deltaTime * CAMERA::SPD_RETURN_FOV_CHANGE;

	//fov�Z�b�g
	float accelerationFov = (CAMERA::FOV_MAX - CAMERA::FOV_DEFAULT) * _fov_parameter;
	float decelerationFov = _fov;
	float fov = accelerationFov + decelerationFov;
	SetupCamera_Perspective(Math::ToRadians(fov));
}

void camera::UpdatePlayerCamera(InputManager& input, float deltaTime, float camSpd)
{
	MATRIX playerRotationMatrix = _p.GetRotationMatrix();
	VECTOR playerPosition = _p.GetPosition();
	VECTOR positionFreeLook = VTransform(CAMERA::DISTANCE_FREE_LOOK, playerRotationMatrix);//�t���[���b�N���[�h�̃J�������W
	VECTOR distanceTps = CAMERA::DISTANCE_TPS;//TPS���[�h�̃J�������W
	
	VECTOR positionTps = VAdd(playerPosition, VTransform(distanceTps, playerRotationMatrix));
	VECTOR targetFPS = VAdd(playerPosition, VTransform(CAMERA::TARGET_FPS_CAMERA, playerRotationMatrix));
	VECTOR targetFreeLook = CAMERA::TARGET_FREE_LOOK;

	//���O�����Z�qcameraTyep��Tps�Ȃ�Tps�p�̍��W(���Ӓl)��������Afalse�Ȃ�E�Ӓl�t���[���b�N�p���W��������
	CameraType cameraType = _p.GetCameraStatus();
	bool isTps = cameraType == CameraType::Tps;
	VECTOR positionNotFpsCamera = isTps ? positionTps : positionFreeLook;
	VECTOR targetNotFps = isTps ? targetFPS : targetFreeLook;

	//�J�����^�C�v�ɂ�苗�������ϓ�
	float cameraDistanceChangeSpd = CAMERA::SPD_DISTANCE_CHANGE * deltaTime;//�J�������������̏C�����x
	//���O�����Z�q cameraType==Fps�Ȃ�ω����x�̓}�C�i�X�����Afalse�Ȃ�v���X�����̕ω��ɂȂ�
	cameraDistanceChangeSpd = cameraType == CameraType::Fps ? -1 * cameraDistanceChangeSpd : cameraDistanceChangeSpd;
	//landing�A�j���[�V�������̓J�������������͓�{
	float max = _p.GetStatus() == Status::Landing ? 2.0f : 1.0f;

	_cameraDistanceParameter += cameraDistanceChangeSpd;
	_cameraDistanceParameter = Math::Clamp(_cameraDistanceParameter, 0.0f, max);

	//���������̌��ʂ�������//_cameraDistanceParameter��0�Ȃ�v���C���[�����A1�Ȃ�J�������[�h����
	_up = VTransform(Math::VUp(), playerRotationMatrix);//������̃x�N�g��
	_position = Math::Lerp(playerPosition, positionNotFpsCamera, _cameraDistanceParameter);
	_target = Math::Lerp(targetFPS, targetNotFps, _cameraDistanceParameter);
}

