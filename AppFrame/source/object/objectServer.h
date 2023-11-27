/*****************************************************************//**
 * \file   ObjectServer.h
 * \brief  ゲーム内のオブジェクト配列を管理する
 * \brief  配列への追加削除、更新描画の呼び出し、検索、メッセージ送信の機能を持つ
 *
 * \author 土居将太郎
 * \date   December 2022
 *********************************************************************/
#pragma once
#include <DxLib.h>
#include <memory>
#include <vector>
#include <algorithm>
#include <string>

class ObjectBase;
class InputManager;
class ModeBase;

class ObjectServer {

public:
	ObjectServer(ModeBase& parent);
	~ObjectServer();

	std::vector<std::unique_ptr<ObjectBase>>& GetObjects() { return _objects; }

	void Clear();

	/** Actorをペンディングに追加する */
	void Add(std::unique_ptr<ObjectBase> actor);
	//特定のオブジェクトを削除する
	void Delete(ObjectBase& actor);
	void Update(InputManager& input);
	void Render(int renderScreen = DX_SCREEN_BACK);
	void Debug();

	ObjectBase* Get(const int id);
	ObjectBase* Get(std::string_view name);

	
private:
	std::vector<std::unique_ptr<ObjectBase>> _objects;
	std::vector<std::unique_ptr<ObjectBase>> _pendingObjects;

	bool _updating;

	//ペンディングのActorをゲーム内に追加
	void AddPendingObject();
	//deadフラグが立っているオブジェクトを全て削除
	void DeleteObject();

	int _uidCount;
	ModeBase& _mode;
};

