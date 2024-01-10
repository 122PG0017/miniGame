#pragma once

class modeEnd :public AppFrame::ModeBase
{
	modeEnd() {};
	~modeEnd() {};
	bool Initialize() override;
	bool Terminate() override;
	bool Process(InputManager& input) override;
	bool Render() override;
	bool Debug() override;
protected:
	int _cg;
	modelInf _modelInf;
	Rserver RS;
	//ModeServer* _modeServer;
};