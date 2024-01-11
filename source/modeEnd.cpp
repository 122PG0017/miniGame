using namespace AppFrame;
using namespace model;


bool	modeEnd::Terminate()
{
	StopMusic();
	return true;
}

bool	modeEnd::Initialize()
{
	_cg = RS.loadGraphR("resource/tmp/sky2.jpg");
	_color = DxLib::GetColor(0, 0, 0);

	return true;
}

bool modeEnd::Process(InputManager& input)
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
			LoopGame();
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

bool	modeEnd::Render()
{
	DxLib::DrawGraph(0, 0, _cg, true);
	DxLib::DrawFormatString(640, 480, _color, "Staet–ß‚é");
	DxLib::DrawFormatString(640, 500, _color, "Exit");
	DrawBox(_x1, _y1, _x2, _y2, _color, FALSE);
	return true;
}

bool modeEnd::Debug()
{
	ModeBase::Debug();
	_objectServer->Debug();
	return true;
}

void modeEnd::LoopGame()
{
	ModeServer::GetInstance()->Add(std::make_unique<modeTitle>(), 1, "title");
}

void modeEnd::Exit()
{
	ApplicationBase::GetInstance()->SetAppEnd(true);
}