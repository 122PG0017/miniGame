/*****************************************************************//**
 * \file   ModeBase.h
 * \brief  モードのサーバークラス
 *
 * \author 山本莉久
 * \date   March 2023
 *********************************************************************/
#pragma once
#include <map>
#include <string>
#include<vector>
#include <memory>
#include "ModeBase.h"

namespace AppFrame {
	struct valData
	{
		float plAtkSpd1 = 24.f, plAtkSpd2 = 24.f, plAtkSpd3 = 24.f, plAtkSpd4 = 24.f, counterSpd = 4.f, plAtkNum[9] = { 0 };
		int _counterTime = 20, plCTimeN = 0, efcHandle = -1, bgmSwitchNum = 1, popBossNum = 0, soundMasterValume = 30, mainMenuPicNum = 0, points = 0
			, hitstopF = 0;
		bool isAtkEfcArufa = true, isLogoRender = true, isDebug = false;
		std::string plChangeAttackX = "charge", plChangeAttackY = "kirinuke", boss1Inf, boss2Inf, lastBossInf;
		std::vector<std::string> news, changeAttackList, playerVoiceList, playerSeList, bossVoiceList, bossSeList, deadBoss, credits, Tips;
		std::vector<int> activateWepon, disableWepon, menuSoundHandle;
	};

	class InputManager;
	class	ModeServer
	{
		typedef	std::map<std::string, std::shared_ptr<ModeBase> >		lstModeBase;

	public:
		ModeServer();
		virtual	~ModeServer();
		static ModeServer* _lpInstance;
		static ModeServer* GetInstance() { return (ModeServer*)_lpInstance; }

		int Add(std::shared_ptr<ModeBase> mode, int layer, const char* name);		// 登録はするが、一度メインを回さないといけない
		int Del(const char* name);		// 削除予約
		int activate(const char* name);
		int disable(const char* name);
		void Clear();
		int LayerTop() { return INT32_MAX; }

		static bool modeSort(const std::shared_ptr<ModeBase> x, const std::shared_ptr<ModeBase> y) { return x->_layer < y->_layer; }

		int ProcessInit();	// プロセスを回すための初期化
		int Process(InputManager& input);		// レイヤーの上の方から処理
		int ProcessFinish();		// プロセスを回した後の後始末

		int RenderInit();		// 描画を回すための初期化
		int Render();		// レイヤーの下の方から処理
		int RenderFinish();		// 描画を回した後の後始末

		int DebugInit();		// デバッグを回すための初期化
		int Debug();		// レイヤーの下の方から処理
		int DebugFinish();		// デバッグを回した後の後始末

		int SkipUpdateUnderLayer();		// 現Processで、今処理しているレイヤーより下のレイヤーは、処理を呼ばない
		int SkipRenderUnderLayer();			// 現Processで、今処理しているレイヤーより下のレイヤーは、描画を呼ばない
		int PauseProcessUnderLayer();		// 現Processで、今処理しているレイヤーより下のレイヤーは、時間経過を止める

		float GetSlowRate() { return _slowRate; }
		void SetSlow(float rate, float duration);

	private:
		int Release(const char* name, bool isDel);		// 削除＆delete
		bool IsDelRegist(const char* name);	// 削除予約されているか？

	public:
		valData _valData;
		Rserver RS;
		lstModeBase _vMode; // モードリスト

	private:
		int _uid_count;		// uidカウンタ
		lstModeBase _vModeAdd;		// 追加予約
		std::vector<std::string> _vModeDel;		// 削除予約
		std::vector<std::string> _nowMode;		// 現在呼び出し中のモード
		std::vector<std::string> _skipUpdateMode;	// このモードより下はProcessを呼ばない
		std::vector<std::string> _skipRenderMode;	// このモードより下はRenderを呼ばない
		std::vector<std::string> _pauseUpdateMode;	// このモードより下はProcess時に時間経過をさせない
		float _slowRate;
		unsigned int _slowStart;
		float _slowDuration;
	};
}