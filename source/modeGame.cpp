using namespace AppFrame;
using namespace model;

bool modeGame::Initialize()
{
    if (!ModeBase::Initialize()) { return false; }

    _objectServer->Add(std::make_unique<Player>());
    _objectServer->Add(std::make_unique<Enemy>());

    Handle = RS.loadGraphR("resource/tmp/Dora.png");

   SetUseZBuffer3D(true);
   SetWriteZBuffer3D(true);
   SetUseLighting(false);
    //カメラのセット
    //SetCameraPositionAndTarget_UpVecY({ 0.0f, 500.0f, 50.0f }, { 0.0f, 0.0f, 0.0f });
    //ライトの設定
    ChangeLightTypeDir({ 0.1f,1.0f,0.5f });
    SetLightDifColor({ 2.0f, 2.0f, 2.0f, 0.0f });

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

    //drawBPolygon(VECTOR(600, 0, 400), VECTOR(600, 0, -400), VECTOR(-600, 0, 400), VECTOR(-600, 0, -400), Handle);

    return true;
}
