/*****************************************************************//**
 * \file   ModeTest.cpp
 * \brief  モードの実装例です。ゲーム中では使用しない。
 *
 * \author 
 * \date   December 2022
 *********************************************************************/
#include"modeTest.h"
using namespace model;
 //最初に一度だけ自動的に呼ばれる
bool ModeTest::Initialize() {
    if (!ModeBase::Initialize()) { return false; }

    ////テストオブジェクトの追加
    //_objectServer->Add(std::make_unique<TestObject>());
    modelImport("resource/Knight/MV1/enemy_1_.mv1", 1.0f, &_modelInf, &RS);

    _modelInf.pos = VECTOR (0, 0, 0);

    Handle=RS.loadGraphR("resource/tmp/Dora.png");
    
    SetUseZBuffer3D(true);
    SetWriteZBuffer3D(true);
    SetUseLighting(false);
    //カメラのセット
    SetCameraPositionAndTarget_UpVecY({ 0.0f, 500.0f, 50.0f }, { 0.0f, 0.0f, 0.0f });
    //ライトの設定
    //ChangeLightTypeDir({ 0.1f,1.0f,0.5f });
    SetLightDifColor({ 2.0f, 2.0f, 2.0f, 0.0f });

    RS.duplicateModelListImportR();
    animChange(2,&_modelInf,false,false,false);
    return true;
}

//削除する時に一度だけ自動的に呼ばれる
bool ModeTest::Terminate() {
    ModeBase::Terminate();
    return true;

}

/*bool ModeTest::Update(InputManager& input) {
    ModeBase::Update(input);
    _objectServer->Update(input);

    return true;
}*/

bool ModeTest::Render() {
    ModeBase::Render();

    //_objectServer->Render();
    isAnimEnd = modelRender(&_modelInf, 1, 1);
    //drawCube(VECTOR(0, 0, 0), VECTOR(100, 100, 100), GetColorU8(0, 0, 0, 0), GetColorU8(0, 0, 0, 0));
   
        drawBPolygon(VECTOR(600,0,400), VECTOR(600 ,0,-400 ), VECTOR(-600,0,400), VECTOR(-600 ,0,-400 ), Handle);
    
    return true;
}

/*bool ModeTest::Debug()
{
    ModeBase::Debug();
    _objectServer->Debug();
    return false;
}*/

