/*****************************************************************//**
 * \file   ApplicationBase.cpp
 * \brief  アプリケーションのスーパークラスの定義
 *
 * \author 山本莉久
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
#endif //DEBUG時:ウィンドウモード / RELEASE時：フルスクリーンモード
		SetMainWindowText("minigame");
		SetGraphMode(DispSizeW(), DispSizeH(), 32);

		// DirectX11を使用するようにする。(DirectX9も可、一部機能不可)
		// Effekseerを使用するには必ず設定する。
		SetUseDirect3DVersion(DX_DIRECT3D_11);

		//SetEnableXAudioFlag(TRUE);

		// 3Dサウンドにおける1メートルの距離を指定する
		// DxLib_Init の前に Set3DSoundOneMetre を呼ぶ
		Set3DSoundOneMetre(500.0f);

		if (DxLib_Init() == -1)
		{	// エラーが起きたら直ちに終了
			return false;
		}
		SetDrawScreen(DX_SCREEN_BACK);// 描画先画面を裏画面にセット
		// Effekseerを初期化する。
		// 引数には画面に表示する最大パーティクル数を設定する。
		/*if (Effekseer_Init(8000) == -1)
		{
			DxLib_End();
			return -1;
		}*/

		// フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ。
		// Effekseerを使用する場合は必ず設定する。
		SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

		// DXライブラリのデバイスロストした時のコールバックを設定する。
		// ウインドウとフルスクリーンの切り替えが発生する場合は必ず実行する。
		// ただし、DirectX11を使用する場合は実行する必要はない。
		//Effekseer_SetGraphicsDeviceLostCallbackFunctions();
		// 乱数初期化
		srand((unsigned int)time(NULL));

		// モードサーバの初期化
		_modeServer.reset(new ModeServer);
		//インプットマネージャーの初期化
		_inputManager.reset(new InputManager);

		return true;
	}

	bool ApplicationBase::Terminate()
	{
		// Effekseerを終了する。
		//Effkseer_End();
		// DXライブラリ開放
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
			ClearDrawScreen();		// 画面を初期化する
			_modeServer->RenderInit();
			_modeServer->Render();
			_modeServer->RenderFinish();
			ScreenFlip();			// 裏画面の内容を表画面に反映させる
		}
		return true;
	}
}