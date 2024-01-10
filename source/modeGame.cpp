#include "modeGame.h"
using namespace AppFrame;
using namespace model;

bool modeGame::Initialize()
{
    if (!ModeBase::Initialize()) { return false; }

    _objectServer->Add(std::make_unique<Player>());
    _objectServer->Add(std::make_unique<CubeEnemy>());
    _objectServer->Add(std::make_unique<SkySphere>());

    Handle = RS.loadGraphR("resource/tmp/Dora.png");

    DxLib::SetUseZBuffer3D(true);
    DxLib::SetWriteZBuffer3D(true);
    DxLib::SetUseLighting(false);
    //ƒ‰ƒCƒg‚ÌÝ’è
    DxLib::ChangeLightTypeDir({ 0.1f,1.0f,0.5f });
    DxLib::SetLightDifColor({ 2.0f, 2.0f, 2.0f, 0.0f });

    return true;
}

bool modeGame::Terminate()
{
    ModeBase::Terminate();
    return true;
}

bool modeGame::Process(InputManager& input)
{
    ModeBase::Process(input);
    _objectServer->Process(input);

    return true;
}

bool modeGame::Render()
{
    ModeBase::Render();
    _objectServer->Render();

    return true;
}

bool modeGame::Debug()
{
    return false;
}
