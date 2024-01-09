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
    int Disp_x, Disp_y;
    GetWindowSize(&Disp_x, &Disp_y);
    SetMousePoint(Disp_x / 2, Disp_y / 2);
    _upDownAngle = 0.0;
    _sideAngle = 0.0;
    _firstflag = true;
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
	//DxLib::SetCameraPositionAndTargetAndUpVec(_position,_target, _up);
}


void CameraComponent::ProcessPlayerCamera(InputManager& input, float deltaTime, float camSpd)
{
    KeyBoardInput(input, camSpd);
    MouseInput(input);

    MATRIX playerRotationMatrix = _parent->GetRotationMatrix();
    VECTOR playerPosition = _parent->GetPosition();
    VECTOR Direction = CAMERA::DISTANCE_TPS;//TPS���[�h�̃J�������W
    double Max = static_cast<float>(Math::ToRadians(70.0));
    double Min = static_cast<float>(Math::ToRadians(-70.0));
    _upDownAngle = Math::Clamp(_upDownAngle, Min, Max);

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

    //���������̌��ʂ�������
    /*_up = VTransform(Math::VUp(), playerRotationMatrix);//������̃x�N�g��
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
}

void CameraComponent::MouseInput(InputManager& input)
{
    int Disp_x;
    int Disp_y;
    int frame =60;
    GetWindowSize(&Disp_x,&Disp_y);
    float GetX = input.GetMouseX() - Disp_x / 2;
    float GetY = input.GetMouseY() - Disp_y / 2;
    //auto MouseX = Math::Clamp(GetX, -1.5f, 1.5f);
    //auto MouseY = Math::Clamp(GetY, -1.5f, 1.5f);
    auto MouseX = GetX;
    auto MouseY = GetY;
    if (!_firstflag)
    {
        _sideAngle -= Math::ToRadians(MouseX);
        _upDownAngle -= Math::ToRadians(MouseY);
    }
    else { _firstflag = false; }
   
    if (MouseX > 0 || MouseX < 0 || MouseY < 0 || MouseY > 0) { SetMousePoint(Disp_x / 2, Disp_y / 2); }
   
}
