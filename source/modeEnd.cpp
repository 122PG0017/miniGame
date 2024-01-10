#include "modeEnd.h"
using namespace AppFrame;
using namespace model;

bool	modeEnd::Terminate()
{
	StopMusic();
	return true;
}

bool	modeEnd::Initialize()
{
	_cg = RS.loadGraphR("resource/tmp/sky.png");

	return true;
}

bool modeEnd::Process(InputManager& input)
{

	if ((input.GetKeyEnter(InputState::Pressed) || input.GetXboxA(InputState::Pressed) == true))
	{
		StopMusic();
		
		return false;

	}

	return true;
}

bool	modeEnd::Render()
{
	DxLib::DrawGraph(0, 0, _cg, true);
	return true;
}

bool modeEnd::Debug()
{
	return false;
}
