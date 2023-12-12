#pragma once

class modeTitle : public AppFrame::ModeBase
{
public:
	modeTitle();
	bool Initialize() override;
	bool Terminate() override;
	bool Process(InputManager& input) override;
	bool Render() override;

protected:
	int _cg;
	int _select;
	Rserver RS;
};