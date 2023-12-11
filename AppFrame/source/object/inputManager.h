#pragma once
#include <utility>
#include <array>
#include <map>
#include <vector>
#include<../AppFrame/source/appframe.h>
#include"math.h"
//#include "AppFrameMath.h"
namespace AppFrame {
	//キーの入力状態　押しているか、押した瞬間か、離した瞬間か
	enum class InputState {
		Hold,
		Pressed,
		Released
	};

	class InputManager {
	public:
		InputManager();
		virtual ~InputManager();
		virtual void Init();

		//毎フレーム呼び出す入力取得関数
		void Input();

		void Debug();

		/**
		 * \brief 入力取得用の関数
		 * \param state 取得したい入力状態　押しているか、押した瞬間か、離した瞬間か
		 * \return  入力があればtrue
		 */
		virtual bool GetMouseLeft(InputState state) { return GetMouseButton(MOUSE_INPUT_LEFT, state); }
		virtual bool GetMouseMiddle(InputState state) { return GetMouseButton(MOUSE_INPUT_MIDDLE, state); }
		virtual bool GetMouseRight(InputState state) { return GetMouseButton(MOUSE_INPUT_RIGHT, state); }

		virtual bool GetKeyUp(InputState state) { return GetKeyButton(KEY_INPUT_UP, state); }
		virtual bool GetKeyDown(InputState state) { return GetKeyButton(KEY_INPUT_DOWN, state); }
		virtual bool GetKeyLeft(InputState state) { return GetKeyButton(KEY_INPUT_LEFT, state); }
		virtual bool GetKeyRight(InputState state) { return GetKeyButton(KEY_INPUT_RIGHT, state); }
		virtual bool GetKeyZ(InputState state) { return GetKeyButton(KEY_INPUT_Z, state); }
		virtual bool GetKeyX(InputState state) { return GetKeyButton(KEY_INPUT_X, state); }
		virtual bool GetKeyC(InputState state) { return GetKeyButton(KEY_INPUT_C, state); }
		virtual bool GetKeyV(InputState state) { return GetKeyButton(KEY_INPUT_V, state); }
		virtual bool GetKeyA(InputState state) { return GetKeyButton(KEY_INPUT_A, state); }
		virtual bool GetKeyS(InputState state) { return GetKeyButton(KEY_INPUT_S, state); }
		virtual bool GetKeyD(InputState state) { return GetKeyButton(KEY_INPUT_D, state); }
		virtual bool GetKeyQ(InputState state) { return GetKeyButton(KEY_INPUT_Q, state); }
		virtual bool GetKeyW(InputState state) { return GetKeyButton(KEY_INPUT_W, state); }
		virtual bool GetKey1(InputState state) { return GetKeyButton(KEY_INPUT_1, state); }
		virtual bool GetKey2(InputState state) { return GetKeyButton(KEY_INPUT_2, state); }
		virtual bool GetKey0(InputState state) { return GetKeyButton(KEY_INPUT_0, state); }
		virtual bool GetKeyESC(InputState state) { return GetKeyButton(KEY_INPUT_ESCAPE, state); }
		virtual bool GetKeyEnter(InputState state) { return GetKeyButton(KEY_INPUT_RETURN, state); }
		virtual bool GetKeyAt(InputState state) { return GetKeyButton(KEY_INPUT_AT, state); }
		virtual bool GetKeySPACE(InputState state) { return GetKeyButton(KEY_INPUT_SPACE, state); }
		virtual bool GetKeyDelete(InputState state) { return GetKeyButton(KEY_INPUT_DELETE, state); }
		virtual bool GetKeyControlLeft(InputState state) { return GetKeyButton(KEY_INPUT_LCONTROL, state); }
		virtual bool GetKeyShiftLeft(InputState state) { return GetKeyButton(KEY_INPUT_LSHIFT, state); }

		virtual bool GetPadDown(InputState state, int controllerNumber = 0) { return GetPadButton(PAD_INPUT_DOWN, state, controllerNumber); }
		virtual bool GetPadLeft(InputState state, int controllerNumber = 0) { return GetPadButton(PAD_INPUT_LEFT, state, controllerNumber); }
		virtual bool GetPadRight(InputState state, int controllerNumber = 0) { return GetPadButton(PAD_INPUT_RIGHT, state, controllerNumber); }
		virtual bool GetPadUp(InputState state, int controllerNumber = 0) { return GetPadButton(PAD_INPUT_UP, state, controllerNumber); }
		virtual bool GetPadX(InputState state, int controllerNumber = 0) { return GetPadButton(PAD_INPUT_1, state, controllerNumber); }
		virtual bool GetPadY(InputState state, int controllerNumber = 0) { return GetPadButton(PAD_INPUT_2, state, controllerNumber); }
		virtual bool GetPadA(InputState state, int controllerNumber = 0) { return GetPadButton(PAD_INPUT_3, state, controllerNumber); }
		virtual bool GetPadB(InputState state, int controllerNumber = 0) { return GetPadButton(PAD_INPUT_4, state, controllerNumber); }
		virtual bool GetPadL1(InputState state, int controllerNumber = 0) { return GetPadButton(PAD_INPUT_5, state, controllerNumber); }
		virtual bool GetPadR1(InputState state, int controllerNumber = 0) { return GetPadButton(PAD_INPUT_6, state, controllerNumber); }
		virtual bool GetPadL2(InputState state, int controllerNumber = 0) { return GetPadButton(PAD_INPUT_8, state, controllerNumber); }
		virtual bool GetPadR2(InputState state, int controllerNumber = 0) { return GetPadButton(PAD_INPUT_8, state, controllerNumber); }
		//Lスティック押し込み
		virtual bool GetPadL3(InputState state, int controllerNumber = 0) { return GetPadButton(PAD_INPUT_9, state, controllerNumber); }
		//Rスティック押し込み
		virtual bool GetPadR3(InputState state, int controllerNumber = 0) { return GetPadButton(PAD_INPUT_10, state, controllerNumber); }
		virtual bool GetPadBack(InputState state, int controllerNumber = 0) { return GetPadButton(PAD_INPUT_11, state, controllerNumber); }
		virtual bool GetPadStart(InputState state, int controllerNumber = 0) { return GetPadButton(PAD_INPUT_12, state, controllerNumber); }

		virtual bool GetXboxDown(InputState state, int controllerNumber = 0) { return GetXboxButton(XINPUT_BUTTON_DPAD_DOWN, state, controllerNumber); }
		virtual bool GetXboxLeft(InputState state, int controllerNumber = 0) { return GetXboxButton(XINPUT_BUTTON_DPAD_LEFT, state, controllerNumber); }
		virtual bool GetXboxRight(InputState state, int controllerNumber = 0) { return GetXboxButton(XINPUT_BUTTON_DPAD_RIGHT, state, controllerNumber); }
		virtual bool GetXboxUp(InputState state, int controllerNumber = 0) { return GetXboxButton(XINPUT_BUTTON_DPAD_UP, state, controllerNumber); }
		virtual bool GetXboxX(InputState state, int controllerNumber = 0) { return GetXboxButton(XINPUT_BUTTON_X, state, controllerNumber); }
		virtual bool GetXboxY(InputState state, int controllerNumber = 0) { return GetXboxButton(XINPUT_BUTTON_Y, state, controllerNumber); }
		virtual bool GetXboxA(InputState state, int controllerNumber = 0) { return GetXboxButton(XINPUT_BUTTON_A, state, controllerNumber); }
		virtual bool GetXboxB(InputState state, int controllerNumber = 0) { return GetXboxButton(XINPUT_BUTTON_B, state, controllerNumber); }
		virtual bool GetXboxL1(InputState state, int controllerNumber = 0) { return GetXboxButton(XINPUT_BUTTON_LEFT_SHOULDER, state, controllerNumber); }
		virtual bool GetXboxR1(InputState state, int controllerNumber = 0) { return GetXboxButton(XINPUT_BUTTON_RIGHT_SHOULDER, state, controllerNumber); }
		//L2戻り値0～255
		unsigned char GetXboxL2(int controllerNumber = 0) { return _xInputs[controllerNumber].LeftTrigger; }
		//R2戻り値0～255
		unsigned char GetXboxR2(int controllerNumber = 0) { return _xInputs[controllerNumber].RightTrigger; }
		//Lスティック押し込み
		virtual bool GetXboxL3(InputState state, int controllerNumber = 0) { return GetXboxButton(XINPUT_BUTTON_LEFT_THUMB, state, controllerNumber); }
		//Rスティック押し込み
		virtual bool GetXboxR3(InputState state, int controllerNumber = 0) { return GetXboxButton(XINPUT_BUTTON_RIGHT_THUMB, state, controllerNumber); }
		virtual bool GetXboxStart(InputState state, int controllerNumber = 0) { return GetXboxButton(XINPUT_BUTTON_START, state, controllerNumber); }
		virtual bool GetXboxBack(InputState state, int controllerNumber = 0) { return GetXboxButton(XINPUT_BUTTON_BACK, state, controllerNumber); }
		//Rスティックの判定。戻り値{x軸( -32768 ～ 32767 ),y軸( -32768 ～ 32767 )}
		VECTOR2<short> GetXboxStickR(int controllerNumber = 0) { return { _xInputs[controllerNumber].ThumbRX, _xInputs[controllerNumber].ThumbRY }; }
		//Lスティック。戻り値{x軸( -32768 ～ 32767 ),y軸( -32768 ～ 32767 )}
		VECTOR2<short> GetXboxStickL(int controllerNumber = 0) { return { _xInputs[controllerNumber].ThumbLX, _xInputs[controllerNumber].ThumbLY }; }

		//マウス位置取得
		VECTOR2<int> GetMouseXY() { return { _mouseX, _mouseY }; };
		int GetMouseX() { return _mouseX; }
		int GetMouseY() { return _mouseY; }
		VECTOR2<int> GetMouseDeltaXY() { return { _mouseX - _mouseOldX, _mouseY - _mouseOldY }; };
		int GetMouseDeltaX() { return _mouseX - _mouseOldX; }
		int GetMouseDeltaY() { return _mouseY - _mouseOldY; }
		int GetMouseWheel() { return _mouseWheel; }
		//マウス位置設定
		void SetMouseXY(VECTOR2<int> set) { _mouseX = set.x; _mouseY = set.y; }
		void SetMouseX(int set) { _mouseX = set; }
		void SetMouseY(int set) { _mouseY = set; }

	private:

		char _keyboardKeys[256], _oldKeyboardKeys[256];
		int _mouseX, _mouseY;
		int _mouseOldX, _mouseOldY;
		int _mouse, _oldMouse;
		int _mouseWheel;

		std::vector<int> _padKeys, _oldPadKeys;
		std::vector<int> _padX;
		std::vector<int> _padY;
		std::vector<int> _stickL;
		std::vector<int> _stickR;

		std::vector<XINPUT_STATE> _xInputs, _oldXInputs;

		static constexpr std::array<int, 16> _controllerList = {
			DX_INPUT_KEY_PAD1,
			DX_INPUT_PAD2,
			DX_INPUT_PAD3,
			DX_INPUT_PAD4,
			DX_INPUT_PAD5,
			DX_INPUT_PAD6,
			DX_INPUT_PAD7,
			DX_INPUT_PAD8,
			DX_INPUT_PAD9,
			DX_INPUT_PAD10,
			DX_INPUT_PAD11,
			DX_INPUT_PAD12,
			DX_INPUT_PAD13,
			DX_INPUT_PAD14,
			DX_INPUT_PAD15,
			DX_INPUT_PAD16
		};

		bool GetMouseButton(int key, InputState state);
		bool GetKeyButton(int key, InputState state);
		bool GetPadButton(int key, InputState state, int controllerNumber);
		bool GetXboxButton(int key, InputState state, int controllerNumber);
	};
}
