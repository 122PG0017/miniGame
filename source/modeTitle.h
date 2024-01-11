#pragma once

class modeTitle : public AppFrame::ModeBase
{
public:
	modeTitle();
	bool Initialize() override;
	bool Terminate() override;
	bool Process(InputManager& input) override;
	bool Render() override;
	bool Debug() override;

	void StartGame();
	void Exit();
protected:
	int _cg;
	int _select;
	int _color;
	int _x1, _x2, _y1, _y2;
	Rserver RS;
};