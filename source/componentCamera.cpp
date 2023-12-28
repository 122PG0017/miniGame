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
	DxLib::SetCameraPositionAndTargetAndUpVec(_position,_target, _up);
}

void CameraComponent::Input(InputManager& input)
{
    float DefoltDeadZone = 0.0f;
    // �Q�[�������x�̎擾
    auto [cameraSens, aimSens, deadZone] = _gm.sensitivity();
    // �f�b�h�]�[���͈̔͂�ݒ肷�邽�߂Ƀf�t�H���g�̃f�b�g�]�[���Ɋ|����l�̐ݒ�
    auto deadZoneMulti = DefoltDeadZone / deadZone;
    // �E�X�e�B�b�N����ɌX���Ă�����J�����̏㉺�̉�]�̊p�x�𑝂₷
    // �f�b�h�]�[���ȏ�Ńp�b�h�̃X�e�B�b�N�̓��͔͈͂𕪊������͈͂̍ŏ��͈͓̔��������ꍇ
    if (input.GetXboxStickR().y >= deadZone && input.GetXboxStickL().y < deadZone * deadZoneMulti) {
        // �J�������x��0.2�{�������̂𑫂�
        _upDownAngle += cameraSens * 0.2;
        // 10�x�ȏ�X���Ă�����10�x�ɂ���
        if (_upDownAngle >= 10.0) {
            _upDownAngle = 10.0;
        }
    }
    // �p�b�h�̃X�e�B�b�N�̓��͔͈͂𕪊������͈͂̓�ڂ͈͓̔��������ꍇ
    else if (input.GetXboxStickL().y >= deadZone * deadZoneMulti && input.GetXboxStickL().y < deadZone * deadZoneMulti * 2) {
        // �J�������x��0.4�{�������̂𑫂�
        _upDownAngle += cameraSens * 0.4;
        // 10�x�ȏ�X���Ă�����10�x�ɂ���
        if (_upDownAngle >= 10.0) {
            _upDownAngle = 10.0;
        }
    }
    // �p�b�h�̃X�e�B�b�N�̓��͔͈͂𕪊������͈͂̎O�ڂ͈͓̔��������ꍇ
    else if (input.GetXboxStickL().y >= deadZone * deadZoneMulti * 2 && input.GetXboxStickL().y < deadZone * deadZoneMulti * 3) {
        // �J�������x��0.6�{�������̂𑫂�
        _upDownAngle += cameraSens * 0.6;
        // 10�x�ȏ�X���Ă�����10�x�ɂ���
        if (_upDownAngle >= 10.0) {
            _upDownAngle = 10.0;
        }
    }
    // �p�b�h�̃X�e�B�b�N�̓��͔͈͂𕪊������͈͂̎l�ڂ͈͓̔��������ꍇ
    else if (input.GetXboxStickL().y >= deadZone * deadZoneMulti * 3 && input.GetXboxStickL().y < deadZone * deadZoneMulti * 4) {
        // �J�������x��0.8�{�������̂𑫂�
        _upDownAngle += cameraSens * 0.8;
        // 10�x�ȏ�X���Ă�����10�x�ɂ���
        if (_upDownAngle >= 10.0) {
            _upDownAngle = 10.0;
        }
    }
    // �p�b�h�̃X�e�B�b�N�̓��͔͈͂𕪊������͈͂̎l�ڂ͈̔͂��傫�������ꍇ
    else if (input.GetXboxStickL().y >= deadZone * deadZoneMulti * 4) {
        // �J�������x�𑫂�
        _upDownAngle += cameraSens;
        // 10�x�ȏ�X���Ă�����10�x�ɂ���
        if (_upDownAngle >= 10.0) {
            _upDownAngle = 10.0;
        }
    }
    // �E�X�e�B�b�N�����ɌX���Ă�����J�����̏㉺�̉�]�̊p�x�����炷
    // �f�b�h�]�[���ȉ��Ńp�b�h�̃X�e�B�b�N�̓��͔͈͂𕪊������͈͂̍ŏ��͈͓̔��������ꍇ
    if (input.GetXboxStickL().y <= -deadZone && input.GetXboxStickL().y > -deadZone * deadZoneMulti) {
        // �J�������x��0.2�{�������̂�����
        _upDownAngle -= cameraSens * 0.2;
        // -20�x�ȏ�X���Ă�����-20�x�ɂ���
        if (_upDownAngle <= -20.0) {
            _upDownAngle = -20.0;
        }
    }
    // �p�b�h�̃X�e�B�b�N�̓��͔͈͂𕪊������͈͂̓�ڂ͈͓̔��������ꍇ
    else if (input.GetXboxStickL().y <= -deadZone * deadZoneMulti && input.GetXboxStickL().y > -deadZone * deadZoneMulti * 2) {
        // �J�������x��0.4�{�������̂�����
        _upDownAngle -= cameraSens * 0.4;
        // -20�x�ȏ�X���Ă�����-20�x�ɂ���
        if (_upDownAngle <= -20.0) {
            _upDownAngle = -20.0;
        }
    }
    // �p�b�h�̃X�e�B�b�N�̓��͔͈͂𕪊������͈͂̎O�ڂ͈͓̔��������ꍇ
    else if (input.GetXboxStickL().y <= -deadZone * deadZoneMulti * 2 && input.GetXboxStickL().y > -deadZone * deadZoneMulti * 3) {
        // �J�������x��0.6�{�������̂�����
        _upDownAngle -= cameraSens * 0.6;
        // -20�x�ȏ�X���Ă�����-20�x�ɂ���
        if (_upDownAngle <= -20.0) {
            _upDownAngle = -20.0;
        }
    }
    // �p�b�h�̃X�e�B�b�N�̓��͔͈͂𕪊������͈͂̎l�ڂ͈͓̔��������ꍇ
    else if (input.GetXboxStickL().y <= -deadZone * deadZoneMulti * 3 && input.GetXboxStickL().y > -deadZone * deadZoneMulti * 4) {
        // �J�������x��0.8�{�������̂�����
        _upDownAngle -= cameraSens * 0.8;
        // -20�x�ȏ�X���Ă�����-20�x�ɂ���
        if (_upDownAngle <= -20.0) {
            _upDownAngle = -20.0;
        }
    }
    // �p�b�h�̃X�e�B�b�N�̓��͔͈͂𕪊������͈͂̎l�ڂ͈̔͂�菬���������ꍇ
    else if (input.GetXboxStickL().y <= -deadZone * deadZoneMulti * 4) {
        // �J�������x������
        _upDownAngle -= cameraSens;
        // -20�x�ȏ�X���Ă�����-20�x�ɂ���
        if (_upDownAngle <= -20.0) {
            _upDownAngle = -20.0;
        }
    }
    // �E�X�e�B�b�N���E�ɌX���Ă�����J�����̍��E�̉�]�̊p�x�����炷
    // �f�b�h�]�[���ȏ�Ńp�b�h�̃X�e�B�b�N�̓��͔͈͂𕪊������͈͂̍ŏ��͈͓̔��������ꍇ
    if (input.GetXboxStickL().x >= deadZone && input.GetXboxStickL().x < deadZone * deadZoneMulti) {
        // �J�������x��0.2�{�������̂�����
        _sideAngle -= cameraSens * 0.2;
        // -360�x�ȉ��ɂȂ�����0�x�ɂ���
        if (_sideAngle <= -360.0) {
            _sideAngle = 0.0;
        }
    }
    // �p�b�h�̃X�e�B�b�N�̓��͔͈͂𕪊������͈͂̓�ڂ͈͓̔��������ꍇ
    else if (input.GetXboxStickL().x >= deadZone * deadZoneMulti && input.GetXboxStickL().x < deadZone * deadZoneMulti * 2) {
        // �J�������x��0.4�{�������̂�����
        _sideAngle -= cameraSens * 0.4;
        //-360�x�ȉ��ɂȂ�����0�x�ɂ���
        if (_sideAngle <= -360.0) {
            _sideAngle = 0.0;
        }
    }
    // �p�b�h�̃X�e�B�b�N�̓��͔͈͂𕪊������͈͂̎O�ڂ͈͓̔��������ꍇ
    else if (input.GetXboxStickL().x >= deadZone * deadZoneMulti * 2 && input.GetXboxStickL().x < deadZone * deadZoneMulti * 3) {
        // �J�������x��0.6�{�������̂�����
        _sideAngle -= cameraSens * 0.6;
        // -360�x�ȉ��ɂȂ�����0�x�ɂ���
        if (_sideAngle <= -360.0) {
            _sideAngle = 0.0;
        }
    }
    // �p�b�h�̃X�e�B�b�N�̓��͔͈͂𕪊������͈͂̎l�ڂ͈͓̔��������ꍇ
    else if (input.GetXboxStickL().x >= deadZone * deadZoneMulti * 3 && input.GetXboxStickL().x < deadZone * deadZoneMulti * 4) {
        // �J�������x��0.8�{�������̂�����
        _sideAngle -= cameraSens * 0.8;
        // -360�x�ȉ��ɂȂ�����0�x�ɂ���
        if (_sideAngle <= -360.0) {
            _sideAngle = 0.0;
        }
    }
    // �p�b�h�̃X�e�B�b�N�̓��͔͈͂𕪊������͈͂̎l�ڂ͈̔͂��傫�������ꍇ
    else if (input.GetXboxStickL().x >= deadZone * deadZoneMulti * 4) {
        // �J�������x������
        _sideAngle -= cameraSens;
        // -360�x�ȉ��ɂȂ�����0�x�ɂ���
        if (_sideAngle <= -360.0) {
            _sideAngle = 0.0;
        }
    }
    // �E�X�e�B�b�N�����ɌX���Ă�����J�����̍��E�̉�]�̊p�x�𑝂₷
    // �f�b�h�]�[���ȉ��Ńp�b�h�̃X�e�B�b�N�̓��͔͈͂𕪊������͈͂̍ŏ��͈͓̔��������ꍇ
    if (input.GetXboxStickL().x <= -deadZone && input.GetXboxStickL().x > -deadZone * deadZoneMulti) {
        // �J�������x��0.2�{�������̂𑫂�
        _sideAngle += cameraSens * 0.2;
        // 360�x�ȏ�ɂȂ�����0�x�ɂ���
        if (_sideAngle >= 360.0) {
            _sideAngle = 0.0;
        }
    }
    // �p�b�h�̃X�e�B�b�N�̓��͔͈͂𕪊������͈͂̓�ڂ͈͓̔��������ꍇ
    else if (input.GetXboxStickL().x <= -deadZone * deadZoneMulti && input.GetXboxStickL().x > -deadZone * deadZoneMulti * 2) {
        // �J�������x��0.4�{�������̂𑫂�
        _sideAngle += cameraSens * 0.4;
        // 360�x�ȏ�ɂȂ�����0�x�ɂ���
        if (_sideAngle >= 360.0) {
            _sideAngle = 0.0;
        }
    }
    // �p�b�h�̃X�e�B�b�N�̓��͔͈͂𕪊������͈͂̎O�ڂ͈͓̔��������ꍇ
    else if (input.GetXboxStickL().x <= -deadZone * deadZoneMulti * 2 && input.GetXboxStickL().x > -deadZone * deadZoneMulti * 3) {
        // �J�������x��0.6�{�������̂𑫂�
        _sideAngle += cameraSens * 0.6;
        // 360�x�ȏ�ɂȂ�����0�x�ɂ���
        if (_sideAngle >= 360.0) {
            _sideAngle = 0.0;
        }
    }
    // �p�b�h�̃X�e�B�b�N�̓��͔͈͂𕪊������͈͂̎l�ڂ͈͓̔��������ꍇ
    else if (input.GetXboxStickL().x <= -deadZone * deadZoneMulti * 3 && input.GetXboxStickL().x > -deadZone * deadZoneMulti * 4) {
        // �J�������x��0.8�{�������̂𑫂�
        _sideAngle += cameraSens * 0.8;
        // 360�x�ȏ�ɂȂ�����0�x�ɂ���
        if (_sideAngle >= 360.0) {
            _sideAngle = 0.0;
        }
    }
    // �p�b�h�̃X�e�B�b�N�̓��͔͈͂𕪊������͈͂̎l�ڂ͈̔͂�菬���������ꍇ
    else if (input.GetXboxStickL().x <= -deadZone * deadZoneMulti * 4) {
        // �J�������x�𑫂�
        _sideAngle += cameraSens;
        // 360�x�ȏ�ɂȂ�����0�x�ɂ���
        if (_sideAngle >= 360.0) {
            _sideAngle = 0.0;
        }
    }
    // �J�����̈ʒu���璍���_�ւ̃x�N�g���쐬
    auto posToTarget = _target - _position;
    // �J�����̈ʒu���璍���_�ւ̃x�N�g����90�x��]������
    auto anyAxisVec = posToTarget * _anyAxisMatrix;
    // �㉺�̉�]�̃}�g���N�X�쐬
    Matrix44 rotateUpDown = Matrix44();
    rotateUpDown.RotateAnyVecQuaternion(anyAxisVec, _upDownAngle, true);
    // ���E�̉�]�̃}�g���N�X�쐬
    Matrix44 rotateSide = Matrix44();
    rotateSide.RotateAnyVecQuaternion(Vector4(0.0, 1.0, 0.0), _sideAngle, true);
    // �㉺�̉�]�ƍ��E�̉�]�����킹���}�g���N�X���쐬
    _rotateMatrix = rotateSide * rotateUpDown;
}

void CameraComponent::Vibration() 
{
	const auto DivideT =0.0;
	// �I�C���[�@�̎��Ԃ̕�������for������
	for (auto i = 0.0; i < DivideT; ++i) {
		// ���Ԃ̕������Ŋ��������x��Y�̈ʒu�ɑ����Ă���
		_vibrationValue += _vibrationVelocity / DivideT;
		// ���x�Ɏ��Ԃ̕������Ŋ�����Y�̈ʒu���玩�R�������������̂ɂ΂˒萔���|�������̂𑫂��Ă���
		_vibrationVelocity += (-0.0 * (_vibrationValue - 0.0)) / DivideT;
	}
	// ���x������������
	_vibrationVelocity *= 0.9;
}

void CameraComponent::ProcessPlayerCamera(InputManager& input, float deltaTime, float camSpd)
{


	//���������̌��ʂ�������//_cameraDistanceParameter��0�Ȃ�v���C���[�����A1�Ȃ�J�������[�h����
	_up = VTransform(Math::VUp(), playerRotationMatrix);//������̃x�N�g��
	_position = Math::Lerp(playerPosition, positionNotFpsCamera, _cameraDistanceParameter);
	_target = Math::Lerp(targetFPS, targetNotFps, _cameraDistanceParameter);
}
