
using namespace AppFrame;
using namespace model;

bool	modeTitle::Initialize()
{
	_cg = RS.loadGraphR("resource/tmp/sky.png");

	return true;
}

bool modeTitle::Process(InputManager& input)
{
	if (input.GetXboxUp(InputState::Pressed)) {
		--_select;
	}

	if (input.GetXboxDown(InputState::Pressed)) {
		++_select;
	}

	_select = std::clamp(_select, 0, 1);


	if ((input.GetKeyEnter(InputState::Pressed) || input.GetXboxA(InputState::Pressed)==true))
	{
		switch (_select)
		{
		case 0:
			break;
		case 1:
			StopMusic();
			ModeServer::GetInstance()->Add(std::make_unique<modeGame>(), 1, "game");
			return false;
		}
	}

	return true;
}

bool	modeTitle::Render()
{
	DrawGraph(0, 0, _cg, true);
	return true;
}

bool	modeTitle::Terminate()
{
	StopMusic();
	return true;
}