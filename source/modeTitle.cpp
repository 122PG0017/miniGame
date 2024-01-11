#include "modeTitle.h"
using namespace AppFrame;
using namespace model;

modeTitle::modeTitle() :_cg{ 0 }, _select{ 0 }, _color{ 0 }
{
}

bool	modeTitle::Initialize()
{
	_cg = RS.loadGraphR("resource/tmp/sky.png");
	_color = DxLib::GetColor(0, 0, 0);

	return true;
}

bool modeTitle::Process(InputManager& input)
{
	if (input.GetXboxUp(InputState::Pressed) || input.GetKeyUp(InputState::Pressed)) {
		--_select;
	}

	if (input.GetXboxDown(InputState::Pressed) || input.GetKeyDown(InputState::Pressed)) {
		++_select;
	}

	_select = std::clamp(_select, 0, 1);

	switch (_select)
	{
	case 0:
		_x1 = 630; _x2 = 720; _y1 = 480; _y2 = 500;
		if ((input.GetKeyEnter(InputState::Pressed) || input.GetXboxA(InputState::Pressed) == true))
		{
			StartGame();
			return false;
		}
		break;
	case 1:
		_x1 = 630; _x2 = 720; _y1 = 500; _y2 = 520;
		if ((input.GetKeyEnter(InputState::Pressed) || input.GetXboxA(InputState::Pressed) == true))
		{
			StopMusic();
			Exit();
			return false;
		}
		break;
	}


	return true;
}

bool	modeTitle::Render()
{
	DxLib::DrawGraph(0, 0, _cg, true);
	DxLib::DrawFormatString(630, 480, _color, "GameStart");
	DxLib::DrawFormatString(630, 500, _color, "Exit");
	DrawBox(_x1, _y1, _x2, _y2, _color, FALSE);
	return true;
}

bool modeTitle::Debug()
{
	return true;
}

bool	modeTitle::Terminate()
{
	StopMusic();
	return true;
}

void modeTitle::StartGame()
{
	ModeServer::GetInstance()->Add(std::make_unique<modeGame>(), 1, "game");
}

void modeTitle::Exit()
{
	ApplicationBase::GetInstance()->SetAppEnd(true);
}
