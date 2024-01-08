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
	//�J�����`�拗���̐ݒ�
	DxLib::SetCameraNearFar(CAMERA::NEAR_CAMERA, CAMERA::FAR_CAMERA);
	return true;
}

void CameraComponent::Process(InputManager& input)
{
	//�J�������x�{��
	float cameraSpd = CAMERA::SPD_DEFAULT_RETURN_TO_PLAYER_PARAMETER;
	float deltaTime = _parent->GetMode()->GetStepTm() * 0.001f;

    // �r���[�s��̐ݒ�
    auto cameraMatrix = GetCameraViewMatrix();
    SetCameraViewMatrix(cameraMatrix);


    //fov�Z�b�g
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

	// 3D�T�E���h�̃��X�i�[�ݒ�(�J�����Ɠ���)
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
    VECTOR Direction = CAMERA::DISTANCE_TPS;//TPS���[�h�̃J�������W

    // �����_�̍��W�̓v���C���[���W
   _target = playerPosition;
   _target.y += 100;

    // �w����]�s��
    MATRIX MatrixX = MGetRotX(_upDownAngle);
    // �x����]�s��
    MATRIX MatrixY = MGetRotY(_sideAngle);
    // �s��̍���
    _cameraMatrix = MMult(MatrixX, MatrixY);
    // ��x�N�g�����s��ŕϊ�
    Direction = VTransform(Direction, _cameraMatrix);

   // �J�������W�̓v���C���[���W����ϊ��������W�𑫂����Ƃ���
    _position = VAdd(_parent->GetPosition(), Direction);

    /*VECTOR positionTps = VAdd(playerPosition, VTransform(distanceTps, playerRotationMatrix));
    VECTOR targetFPS = VAdd(playerPosition, VTransform(CAMERA::TARGET_FPS_CAMERA, playerRotationMatrix));

    VECTOR positionNotFpsCamera = positionTps;
    VECTOR targetNotFps = targetFPS;

    //�J�����^�C�v�ɂ�苗�������ϓ�
    float cameraDistanceChangeSpd = CAMERA::SPD_DISTANCE_CHANGE * deltaTime;//�J�������������̏C�����x
    //���O�����Z�q cameraType==Fps�Ȃ�ω����x�̓}�C�i�X�����Afalse�Ȃ�v���X�����̕ω��ɂȂ�
    cameraDistanceChangeSpd = cameraDistanceChangeSpd;
    float max = 1.0f;

    _cameraDistanceParameter += cameraDistanceChangeSpd;
    _cameraDistanceParameter = Math::Clamp(_cameraDistanceParameter, 0.0f, max);

    //���������̌��ʂ�������
    _up = VTransform(Math::VUp(), playerRotationMatrix);//������̃x�N�g��
    _position = Math::Lerp(playerPosition, positionNotFpsCamera, _cameraDistanceParameter);
    _target = Math::Lerp(targetFPS, targetNotFps, _cameraDistanceParameter);*/

}


void CameraComponent::KeyBoardInput(InputManager& input,float cameraspd)
{
    // ���E�L�[�Ō����̕ύX
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

   

    // �����_�̍��W�̓v���C���[���W
    //_target = _parent->GetPosition();
    //_target.y += 100;

    // ��̃x�N�g��
    //VECTOR Direction = VGet(0.0f, 500.0f, 1000.0f);

    // �w����]�s��
    //MATRIX MatrixX = MGetRotX(_upDownAngle);
    // �x����]�s��
    //MATRIX MatrixY = MGetRotY(_sideAngle);
    // �s��̍���
    //_cameraMatrix = MMult(MatrixX, MatrixY);
    // ��x�N�g�����s��ŕϊ�
    //Direction = VTransform(Direction, Matrix);

    // �J�������W�̓v���C���[���W����ϊ��������W�𑫂����Ƃ���
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
    // �w����]�s��
    //MATRIX MatrixX = MGetRotX(_upDownAngle);
    // �x����]�s��
    //MATRIX MatrixY = MGetRotY(_sideAngle);
    // �s��̍���
    //_cameraMatrix = MMult(MatrixX, MatrixY);
    //_parent->SetRotationMatrix(_rotMatrix);
}
