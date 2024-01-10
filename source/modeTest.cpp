#include "modeTest.h"
/*****************************************************************//**
 * \file   ModeTest.cpp
 * \brief  モードの実装例です。ゲーム中では使用しない。
 *
 * \author 
 * \date   December 2022
 *********************************************************************/

using namespace AppFrame;
using namespace model;
 //最初に一度だけ自動的に呼ばれる
bool ModeTest::Initialize() {
    if (!ModeBase::Initialize()) { return false; }

    ////テストオブジェクトの追加
    //_objectServer->Add(std::make_unique<TestObject>());
   
    
    SetUseZBuffer3D(true);
    SetWriteZBuffer3D(true);
    SetUseLighting(false);
    //カメラのセット
    SetCameraPositionAndTarget_UpVecY({ 0.0f, 500.0f, 50.0f }, { 0.0f, 0.0f, 0.0f });
    //ライトの設定
    //ChangeLightTypeDir({ 0.1f,1.0f,0.5f });
    SetLightDifColor({ 2.0f, 2.0f, 2.0f, 0.0f });

    return true;
}

//削除する時に一度だけ自動的に呼ばれる
bool ModeTest::Terminate() {
    ModeBase::Terminate();
    return true;

}

bool ModeTest::Process(InputManager& input) {
    ModeBase::Process(input);
    _objectServer->Process(input);

    return true;
}

bool ModeTest::Render() {
    ModeBase::Render();
    _objectServer->Render();
    return true;
}

bool ModeTest::Debug()
{
    return false;
}

