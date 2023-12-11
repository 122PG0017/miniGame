#include<vector>
#include<memory>

using namespace DxLib;
using namespace AppFrame;
using namespace model;


// À‘Ì
gameMain appFrame;

bool gameMain::Initialize(HINSTANCE hInstance)
{
	if (!base::Initialize(hInstance)) { return false; }
	ModeServer::GetInstance()->Add(std::make_unique<modeTitle>(), 5, "ModeTitle");
	return true;
}

bool gameMain::Terminate()
{
	base::Terminate();
	return true;
}

bool gameMain::Input()
{
	base::Input();
	return true;
}

bool gameMain::Process()
{
	base::Process();

	if (CheckHitKey(KEY_INPUT_ESCAPE)) { return false; }
	return true;
}

bool gameMain::Render()
{
	base::Render();

	return true;
}
