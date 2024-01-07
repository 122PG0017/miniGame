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
    //// �v���C���[����̃J�����̒����_�ւ̃x�N�g�����쐬
    //_firstPlyToTarget =VSub(_target ,playerPosition);
    //// �v���C���[����̃J�����̈ʒu�ւ̃x�N�g�����쐬
    //_firstPlyToPos = VSub(_position , playerPosition);
    //// �x�N�g����90�x��]������}�g���N�X�̍쐬
    //_anyAxisMatrix.RotateY(90.0, true);
    //// �J�����̈ʒu���璍���_�ւ̃x�N�g���̍쐬
    //Math::Vector4 posToTarget = Math::ToMath(_target) - Math::ToMath(_position);
    //posToTarget.Normalized();
    //_posToTarget = posToTarget * 300.0;
    //// �x�N�g����90�x��]������}�g���N�X�̍쐬
    //_anyAxisMatrix.RotateY(90.0, true);
    
   

	//�J�����`�拗���̐ݒ�
	DxLib::SetCameraNearFar(CAMERA::NEAR_CAMERA, CAMERA::FAR_CAMERA);
	return true;
}

void CameraComponent::Process(InputManager& input)
{
    //PadInput(input);
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
    //SetCameraPositionAndTarget_UpVecY({ 0.0f, 500.0f, 50.0f }, { 0.0f, 0.0f, 0.0f });
	DxLib::SetCameraPositionAndTargetAndUpVec(_position,_target, _up);
}


void CameraComponent::ProcessPlayerCamera(InputManager& input, float deltaTime, float camSpd)
{

    MouseInput(input);

    MATRIX playerRotationMatrix = _parent->GetRotationMatrix();
    VECTOR playerPosition = _parent->GetPosition();
    VECTOR distanceTps = CAMERA::DISTANCE_TPS;//TPS���[�h�̃J�������W

    VECTOR positionTps = VAdd(playerPosition, VTransform(distanceTps, playerRotationMatrix));
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

    //���������̌��ʂ�������//_cameraDistanceParameter��0�Ȃ�v���C���[�����A1�Ȃ�J�������[�h����
    _up = VTransform(Math::VUp(), playerRotationMatrix);//������̃x�N�g��
    _position = Math::Lerp(playerPosition, positionNotFpsCamera, _cameraDistanceParameter);
    _target = Math::Lerp(targetFPS, targetNotFps, _cameraDistanceParameter);

}

void CameraComponent::PadInput(InputManager& input)
{
    float DefoltDeadZone = 0.0f;
    // �Q�[�������x�̎擾
    auto [cameraSens, aimSens, deadZone] = _gm.sensitivity();
    // �f�b�h�]�[���͈̔͂�ݒ肷�邽�߂Ƀf�t�H���g�̃f�b�g�]�[���Ɋ|����l�̐ݒ�
    auto deadZoneMulti = DefoltDeadZone / deadZone;
    // �E�X�e�B�b�N����ɌX���Ă�����J�����̏㉺�̉�]�̊p�x�𑝂₷
    // �f�b�h�]�[���ȏ�Ńp�b�h�̃X�e�B�b�N�̓��͔͈͂𕪊������͈͂̍ŏ��͈͓̔��������ꍇ
    if (input.GetXboxStickR().y >= deadZone && input.GetXboxStickR().y < deadZone * deadZoneMulti) {
        // �J�������x��0.2�{�������̂𑫂�
        _upDownAngle += cameraSens * 0.2;
        // 10�x�ȏ�X���Ă�����10�x�ɂ���
        if (_upDownAngle >= 10.0) {
            _upDownAngle = 10.0;
        }
    }
    // �p�b�h�̃X�e�B�b�N�̓��͔͈͂𕪊������͈͂̓�ڂ͈͓̔��������ꍇ
    else if (input.GetXboxStickR().y >= deadZone * deadZoneMulti && input.GetXboxStickR().y < deadZone * deadZoneMulti * 2) {
        // �J�������x��0.4�{�������̂𑫂�
        _upDownAngle += cameraSens * 0.4;
        // 10�x�ȏ�X���Ă�����10�x�ɂ���
        if (_upDownAngle >= 10.0) {
            _upDownAngle = 10.0;
        }
    }
    // �p�b�h�̃X�e�B�b�N�̓��͔͈͂𕪊������͈͂̎O�ڂ͈͓̔��������ꍇ
    else if (input.GetXboxStickR().y >= deadZone * deadZoneMulti * 2 && input.GetXboxStickR().y < deadZone * deadZoneMulti * 3) {
        // �J�������x��0.6�{�������̂𑫂�
        _upDownAngle += cameraSens * 0.6;
        // 10�x�ȏ�X���Ă�����10�x�ɂ���
        if (_upDownAngle >= 10.0) {
            _upDownAngle = 10.0;
        }
    }
    // �p�b�h�̃X�e�B�b�N�̓��͔͈͂𕪊������͈͂̎l�ڂ͈͓̔��������ꍇ
    else if (input.GetXboxStickR().y >= deadZone * deadZoneMulti * 3 && input.GetXboxStickR().y < deadZone * deadZoneMulti * 4) {
        // �J�������x��0.8�{�������̂𑫂�
        _upDownAngle += cameraSens * 0.8;
        // 10�x�ȏ�X���Ă�����10�x�ɂ���
        if (_upDownAngle >= 10.0) {
            _upDownAngle = 10.0;
        }
    }
    // �p�b�h�̃X�e�B�b�N�̓��͔͈͂𕪊������͈͂̎l�ڂ͈̔͂��傫�������ꍇ
    else if (input.GetXboxStickR().y >= deadZone * deadZoneMulti * 4) {
        // �J�������x�𑫂�
        _upDownAngle += cameraSens;
        // 10�x�ȏ�X���Ă�����10�x�ɂ���
        if (_upDownAngle >= 10.0) {
            _upDownAngle = 10.0;
        }
    }
    // �E�X�e�B�b�N�����ɌX���Ă�����J�����̏㉺�̉�]�̊p�x�����炷
    // �f�b�h�]�[���ȉ��Ńp�b�h�̃X�e�B�b�N�̓��͔͈͂𕪊������͈͂̍ŏ��͈͓̔��������ꍇ
    if (input.GetXboxStickR().y <= -deadZone && input.GetXboxStickR().y > -deadZone * deadZoneMulti) {
        // �J�������x��0.2�{�������̂�����
        _upDownAngle -= cameraSens * 0.2;
        // -20�x�ȏ�X���Ă�����-20�x�ɂ���
        if (_upDownAngle <= -20.0) {
            _upDownAngle = -20.0;
        }
    }
    // �p�b�h�̃X�e�B�b�N�̓��͔͈͂𕪊������͈͂̓�ڂ͈͓̔��������ꍇ
    else if (input.GetXboxStickR().y <= -deadZone * deadZoneMulti && input.GetXboxStickR().y > -deadZone * deadZoneMulti * 2) {
        // �J�������x��0.4�{�������̂�����
        _upDownAngle -= cameraSens * 0.4;
        // -20�x�ȏ�X���Ă�����-20�x�ɂ���
        if (_upDownAngle <= -20.0) {
            _upDownAngle = -20.0;
        }
    }
    // �p�b�h�̃X�e�B�b�N�̓��͔͈͂𕪊������͈͂̎O�ڂ͈͓̔��������ꍇ
    else if (input.GetXboxStickR().y <= -deadZone * deadZoneMulti * 2 && input.GetXboxStickR().y > -deadZone * deadZoneMulti * 3) {
        // �J�������x��0.6�{�������̂�����
        _upDownAngle -= cameraSens * 0.6;
        // -20�x�ȏ�X���Ă�����-20�x�ɂ���
        if (_upDownAngle <= -20.0) {
            _upDownAngle = -20.0;
        }
    }
    // �p�b�h�̃X�e�B�b�N�̓��͔͈͂𕪊������͈͂̎l�ڂ͈͓̔��������ꍇ
    else if (input.GetXboxStickR().y <= -deadZone * deadZoneMulti * 3 && input.GetXboxStickR().y > -deadZone * deadZoneMulti * 4) {
        // �J�������x��0.8�{�������̂�����
        _upDownAngle -= cameraSens * 0.8;
        // -20�x�ȏ�X���Ă�����-20�x�ɂ���
        if (_upDownAngle <= -20.0) {
            _upDownAngle = -20.0;
        }
    }
    // �p�b�h�̃X�e�B�b�N�̓��͔͈͂𕪊������͈͂̎l�ڂ͈̔͂�菬���������ꍇ
    else if (input.GetXboxStickR().y <= -deadZone * deadZoneMulti * 4) {
        // �J�������x������
        _upDownAngle -= cameraSens;
        // -20�x�ȏ�X���Ă�����-20�x�ɂ���
        if (_upDownAngle <= -20.0) {
            _upDownAngle = -20.0;
        }
    }
    // �E�X�e�B�b�N���E�ɌX���Ă�����J�����̍��E�̉�]�̊p�x�����炷
    // �f�b�h�]�[���ȏ�Ńp�b�h�̃X�e�B�b�N�̓��͔͈͂𕪊������͈͂̍ŏ��͈͓̔��������ꍇ
    if (input.GetXboxStickR().x >= deadZone && input.GetXboxStickR().x < deadZone * deadZoneMulti) {
        // �J�������x��0.2�{�������̂�����
        _sideAngle -= cameraSens * 0.2;
        // -360�x�ȉ��ɂȂ�����0�x�ɂ���
        if (_sideAngle <= -360.0) {
            _sideAngle = 0.0;
        }
    }
    // �p�b�h�̃X�e�B�b�N�̓��͔͈͂𕪊������͈͂̓�ڂ͈͓̔��������ꍇ
    else if (input.GetXboxStickR().x >= deadZone * deadZoneMulti && input.GetXboxStickR().x < deadZone * deadZoneMulti * 2) {
        // �J�������x��0.4�{�������̂�����
        _sideAngle -= cameraSens * 0.4;
        //-360�x�ȉ��ɂȂ�����0�x�ɂ���
        if (_sideAngle <= -360.0) {
            _sideAngle = 0.0;
        }
    }
    // �p�b�h�̃X�e�B�b�N�̓��͔͈͂𕪊������͈͂̎O�ڂ͈͓̔��������ꍇ
    else if (input.GetXboxStickR().x >= deadZone * deadZoneMulti * 2 && input.GetXboxStickR().x < deadZone * deadZoneMulti * 3) {
        // �J�������x��0.6�{�������̂�����
        _sideAngle -= cameraSens * 0.6;
        // -360�x�ȉ��ɂȂ�����0�x�ɂ���
        if (_sideAngle <= -360.0) {
            _sideAngle = 0.0;
        }
    }
    // �p�b�h�̃X�e�B�b�N�̓��͔͈͂𕪊������͈͂̎l�ڂ͈͓̔��������ꍇ
    else if (input.GetXboxStickR().x >= deadZone * deadZoneMulti * 3 && input.GetXboxStickR().x < deadZone * deadZoneMulti * 4) {
        // �J�������x��0.8�{�������̂�����
        _sideAngle -= cameraSens * 0.8;
        // -360�x�ȉ��ɂȂ�����0�x�ɂ���
        if (_sideAngle <= -360.0) {
            _sideAngle = 0.0;
        }
    }
    // �p�b�h�̃X�e�B�b�N�̓��͔͈͂𕪊������͈͂̎l�ڂ͈̔͂��傫�������ꍇ
    else if (input.GetXboxStickR().x >= deadZone * deadZoneMulti * 4) {
        // �J�������x������
        _sideAngle -= cameraSens;
        // -360�x�ȉ��ɂȂ�����0�x�ɂ���
        if (_sideAngle <= -360.0) {
            _sideAngle = 0.0;
        }
    }
    // �E�X�e�B�b�N�����ɌX���Ă�����J�����̍��E�̉�]�̊p�x�𑝂₷
    // �f�b�h�]�[���ȉ��Ńp�b�h�̃X�e�B�b�N�̓��͔͈͂𕪊������͈͂̍ŏ��͈͓̔��������ꍇ
    if (input.GetXboxStickR().x <= -deadZone && input.GetXboxStickR().x > -deadZone * deadZoneMulti) {
        // �J�������x��0.2�{�������̂𑫂�
        _sideAngle += cameraSens * 0.2;
        // 360�x�ȏ�ɂȂ�����0�x�ɂ���
        if (_sideAngle >= 360.0) {
            _sideAngle = 0.0;
        }
    }
    // �p�b�h�̃X�e�B�b�N�̓��͔͈͂𕪊������͈͂̓�ڂ͈͓̔��������ꍇ
    else if (input.GetXboxStickR().x <= -deadZone * deadZoneMulti && input.GetXboxStickR().x > -deadZone * deadZoneMulti * 2) {
        // �J�������x��0.4�{�������̂𑫂�
        _sideAngle += cameraSens * 0.4;
        // 360�x�ȏ�ɂȂ�����0�x�ɂ���
        if (_sideAngle >= 360.0) {
            _sideAngle = 0.0;
        }
    }
    // �p�b�h�̃X�e�B�b�N�̓��͔͈͂𕪊������͈͂̎O�ڂ͈͓̔��������ꍇ
    else if (input.GetXboxStickR().x <= -deadZone * deadZoneMulti * 2 && input.GetXboxStickR().x > -deadZone * deadZoneMulti * 3) {
        // �J�������x��0.6�{�������̂𑫂�
        _sideAngle += cameraSens * 0.6;
        // 360�x�ȏ�ɂȂ�����0�x�ɂ���
        if (_sideAngle >= 360.0) {
            _sideAngle = 0.0;
        }
    }
    // �p�b�h�̃X�e�B�b�N�̓��͔͈͂𕪊������͈͂̎l�ڂ͈͓̔��������ꍇ
    else if (input.GetXboxStickR().x <= -deadZone * deadZoneMulti * 3 && input.GetXboxStickR().x > -deadZone * deadZoneMulti * 4) {
        // �J�������x��0.8�{�������̂𑫂�
        _sideAngle += cameraSens * 0.8;
        // 360�x�ȏ�ɂȂ�����0�x�ɂ���
        if (_sideAngle >= 360.0) {
            _sideAngle = 0.0;
        }
    }
    // �p�b�h�̃X�e�B�b�N�̓��͔͈͂𕪊������͈͂̎l�ڂ͈̔͂�菬���������ꍇ
    else if (input.GetXboxStickR().x <= -deadZone * deadZoneMulti * 4) {
        // �J�������x�𑫂�
        _sideAngle += cameraSens;
        // 360�x�ȏ�ɂȂ�����0�x�ɂ���
        if (_sideAngle >= 360.0) {
            _sideAngle = 0.0;
        }
    }
    // �J�����̈ʒu���璍���_�ւ̃x�N�g���쐬
    auto posToTarget = Math::ToMath(_target) - Math::ToMath(_position);
    // �J�����̈ʒu���璍���_�ւ̃x�N�g����90�x��]������
    auto anyAxisVec = posToTarget * _anyAxisMatrix;
    // �㉺�̉�]�̃}�g���N�X�쐬
    Math::Matrix44 rotateUpDown = Math::Matrix44();
    rotateUpDown.RotateAnyVecQuaternion(anyAxisVec, _upDownAngle, true);
    // ���E�̉�]�̃}�g���N�X�쐬
    Math::Matrix44 rotateSide = Math::Matrix44();
    rotateSide.RotateAnyVecQuaternion(Math::Vector4(0.0, 1.0, 0.0), _sideAngle, true);
    // �㉺�̉�]�ƍ��E�̉�]�����킹���}�g���N�X���쐬
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
