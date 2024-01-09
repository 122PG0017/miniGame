/*****************************************************************//**
 * \file   ApplicationBase.cpp
 * \brief  �A�v���P�[�V�����̃X�[�p�[�N���X�̒�`
 *
 * \author �R�{介v
 * \date   March 2023
 *********************************************************************/
#include "ApplicationBase.h"
#include "../AppFrame/source/Mode/ModeServer.h"
#include "../AppFrame/source/object/inputManager.h"
#include "../AppFrame/source/ResourceServer/SoundServer.h"

namespace AppFrame {

	ApplicationBase* ApplicationBase::_lpInstance = NULL;

	ApplicationBase::ApplicationBase()
	{
		_lpInstance = this;
		_modeServer = nullptr;
		_inputManager = nullptr;
	}

	ApplicationBase::~ApplicationBase() {}

	bool ApplicationBase::Initialize(HINSTANCE hInstance)
	{
#ifdef _DEBUG
		ChangeWindowMode(true);
#else
		ChangeWindowMode(false);
#endif //DEBUG��:�E�B���h�E���[�h / RELEASE���F�t���X�N���[�����[�h
		SetMainWindowText("minigame");
		SetGraphMode(DispSizeW(), DispSizeH(), 32);

		// DirectX11���g�p����悤�ɂ���B(DirectX9���A�ꕔ�@�\�s��)
		// Effekseer���g�p����ɂ͕K���ݒ肷��B
		SetUseDirect3DVersion(DX_DIRECT3D_11);

		//SetEnableXAudioFlag(TRUE);

		// 3D�T�E���h�ɂ�����1���[�g���̋������w�肷��
		// DxLib_Init �̑O�� Set3DSoundOneMetre ���Ă�
		Set3DSoundOneMetre(500.0f);

		if (DxLib_Init() == -1)
		{	// �G���[���N�����璼���ɏI��
			return false;
		}
		SetDrawScreen(DX_SCREEN_BACK);// �`����ʂ𗠉�ʂɃZ�b�g
		// Effekseer������������B
		// �����ɂ͉�ʂɕ\������ő�p�[�e�B�N������ݒ肷��B
		/*if (Effekseer_Init(8000) == -1)
		{
			DxLib_End();
			return -1;
		}*/

		// �t���X�N���[���E�C���h�E�̐؂�ւ��Ń��\�[�X��������̂�h���B
		// Effekseer���g�p����ꍇ�͕K���ݒ肷��B
		SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

		// DX���C�u�����̃f�o�C�X���X�g�������̃R�[���o�b�N��ݒ肷��B
		// �E�C���h�E�ƃt���X�N���[���̐؂�ւ�����������ꍇ�͕K�����s����B
		// �������ADirectX11���g�p����ꍇ�͎��s����K�v�͂Ȃ��B
		//Effekseer_SetGraphicsDeviceLostCallbackFunctions();
		// ����������
		srand((unsigned int)time(NULL));

		// ���[�h�T�[�o�̏�����
		_modeServer.reset(new ModeServer);
		//�C���v�b�g�}�l�[�W���[�̏�����
		_inputManager.reset(new InputManager);

		return true;
	}

	bool ApplicationBase::Terminate()
	{
		// Effekseer���I������B
		//Effkseer_End();
		// DX���C�u�����J��
		DxLib_End();

		return true;
	}

	int volumeGate4000(int num)
	{
		if (std::abs(num) > 4000) { return num; }
		return 0;
	}

	bool ApplicationBase::Input()
	{
		_inputManager->Input();
		return true;
	}

	bool ApplicationBase::Process()
	{
		SoundServer::CheckLoad();
		if (_modeServer->_valData.hitstopF > 0) { _modeServer->_valData.hitstopF--; }
		else
		{
			_modeServer->ProcessInit();
			_modeServer->Process(*_inputManager);
			_modeServer->ProcessFinish();
		}
		return true;
	}

	bool ApplicationBase::Render()
	{
		if (_modeServer->_valData.hitstopF > 0);
		else
		{
			ClearDrawScreen();		// ��ʂ�����������
			_modeServer->RenderInit();
			_modeServer->Render();
			_modeServer->RenderFinish();
			ScreenFlip();			// ����ʂ̓��e��\��ʂɔ��f������
		}
		return true;
	}
}