#pragma once

class modeGame:public AppFrame::ModeBase
{
	modeGame() {};
	~modeGame() {};
	bool Initialize() override;
	bool Terminate() override;
	bool Process(InputManager& input) override;
	bool Render() override;
protected:
	int Handle;
	bool isAnimEnd;
	modelInf _modelInf;
	Rserver RS;
	//ModeServer* _modeServer;
};
