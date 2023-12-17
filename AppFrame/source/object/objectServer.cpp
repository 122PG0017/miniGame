/*****************************************************************//**
 * \file   ObjectServer.cpp
 * \brief  ゲーム内のオブジェクト配列を管理する
 * \brief  配列への追加削除、更新描画の呼び出し、検索、メッセージ送信の機能を持つ
 *
 * \author 
 * \date   December 2022
 *********************************************************************/
#include "ObjectServer.h"
#include "ObjectBase.h"
#include "../AppFrame/source/Mode/ModeBase.h"
#include "../AppFrame/source/Application/ApplicationBase.h"
//#include "BlurRenderer.h"
//#include "ChangeScreen.h"

namespace AppFrame {
	ObjectServer::ObjectServer(ModeBase& parent)
		:_uidCount{ 0 }, _mode{ parent }
	{
		Clear();
	}

	ObjectServer::~ObjectServer()
	{
		_objects.clear();
	}

	void ObjectServer::Clear()
	{
	}

	void ObjectServer::Add(std::unique_ptr<ObjectBase> object)
	{
		object->SetMode(&_mode);
		++_uidCount;
		object->SetID(_uidCount);
		object->Initialize();

		if (_updating) {
			_pendingObjects.push_back(std::move(object));
		}
		else {
			_objects.push_back(std::move(object));
		}
	}

	void ObjectServer::Delete(ObjectBase& object)
	{
		object.Dead();
	}

	namespace {
		static bool objectSort(std::unique_ptr<ObjectBase>& x, std::unique_ptr<ObjectBase>& y) {
			VECTOR position = GetCameraPosition();

			if (x->GetLayer() == y->GetLayer()) {
				return VSize(VSub(x->GetPosition(), position)) < VSize(VSub(y->GetPosition(), position));
			}

			return x->GetLayer() < y->GetLayer();
		}
	}

	void ObjectServer::Process(InputManager& input)
	{
		_updating = true;
		DeleteObject();	// 削除予約されたオブジェクトを削除する
		AddPendingObject();
		std::sort(_objects.begin(), _objects.end(), objectSort);

		for (auto&& actor : _objects) {
			actor->Process(input);
		}

		_updating = false;

	}

	void ObjectServer::Render(int renderScreen)
	{
		//layer9以下の描画(ゲーム内3Dモデルは9以下に設定する前提)
		auto renderUnder9Layer = [&] {
			for (auto&& actor : _objects) {
				if (actor->GetLayer() > 9) {
					break;
				}

				actor->Render();
			}
			};
		//不透明部分の描画
		MV1SetSemiTransDrawMode(DX_SEMITRANSDRAWMODE_NOT_SEMITRANS_ONLY);
		renderUnder9Layer();
		//不透明部分の描画
		MV1SetSemiTransDrawMode(DX_SEMITRANSDRAWMODE_SEMITRANS_ONLY);
		renderUnder9Layer();


		/*
		//ブラーを反映
		if (_mode.GetBlurFlag()) {
			_mode.GetPostProcess()->ApplyBlur(renderScreen);
		}
		else {
			_mode.GetPostProcess()->NotApplyBlur(renderScreen);
		}

		ChangeScreen::ChangeScreenAndSaveCamera(renderScreen);
		//layer10以上の描画(UIは10以上にする想定)
		MV1SetSemiTransDrawMode(DX_SEMITRANSDRAWMODE_ALWAYS);
		*/

		for (auto&& actor : _objects) {
			if (actor->GetLayer() < 10) {
				continue;
			}

			actor->Render();
		}
	}

	void ObjectServer::Debug()
	{
		for (auto&& actor : _objects) {
			actor->Debug();
		}
	}

	ObjectBase* ObjectServer::Get(const int id)
	{
		for (auto&& object : _objects) {
			if (object->GetID() == id) {
				return object.get();
			}
		}

		return nullptr;
	}

	ObjectBase* ObjectServer::Get(std::string_view name)
	{
		for (auto&& object : _objects) {
			if (object->GetName() == name) {
				return object.get();
			}
		}

		return nullptr;
	}


	void ObjectServer::AddPendingObject()
	{
		// Add()されたものを有効にし、必要であればソートを行う
		if (_pendingObjects.size() > 0) {
			auto ite = _pendingObjects.begin();

			for (; ite != _pendingObjects.end(); ++ite) {
				_objects.push_back(std::move((*ite)));
			}

			_pendingObjects.clear();
		}
	}

	void ObjectServer::DeleteObject()
	{
		// コンテナをイテレータで回す( eraseがイテレータを要求しているため )
		for (auto ite = _objects.begin(); ite != _objects.end(); ) {
			if ((*ite)->IsDead()) {
				(*ite)->Terminate();
				ite = _objects.erase(ite);		// これでobjectそのものも削除される
			}
			else {
				++ite;
			}
		}
	}
}