/*****************************************************************//**
 * \file   ApplicationBase.h
 * \brief  アプリケーションのスーパークラス
 *
 * \author 山本莉久
 * \date   March 2023
 *********************************************************************/
#pragma once
#include "DxLib.h"
//#include "EffekseerForDXLib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <memory>
#include <string>

namespace AppFrame {

	class ModeServer;
	class InputManager;

	class ApplicationBase
	{
	public:
		ApplicationBase();
		virtual ~ApplicationBase();

		virtual bool Initialize(HINSTANCE hInstance);
		virtual bool Terminate();
		virtual bool Input();
		virtual bool Process();
		virtual bool Render();
		virtual bool Debug();

		virtual bool AppWindowed() { return true; }
		virtual int DispSizeW() { return 640; }
		virtual int DispSizeH() { return 480; }

		static ApplicationBase* GetInstance() { return _lpInstance; }
		virtual void GetLstick(int* xbuf, int* ybuf) { GetJoypadAnalogInput(xbuf, ybuf, DX_INPUT_PAD1); }
		virtual void GetRstick(int* xbuf, int* ybuf) { GetJoypadAnalogInputRight(xbuf, ybuf, DX_INPUT_PAD1); }
		//virtual int GetWard() { return KeyInputString(10, 700, 141, _imputInf.wardBox, true); }//戻り値1.正常 2.キャンセル 3.失敗
	private:
		std::unique_ptr<ModeServer> _modeServer;//モード管理クラス
	protected:
		static	ApplicationBase* _lpInstance;
		std::vector<std::string> debugWardBox;
		//XINPUT_STATE imputInfX;
		std::unique_ptr<InputManager> _inputManager;//入力を取得
	};
}
