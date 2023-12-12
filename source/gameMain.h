#pragma once
#include<memory>

class gameMain : public AppFrame::ApplicationBase
{
	typedef AppFrame::ApplicationBase base;
public:
	gameMain() {};
	~gameMain() {};
	bool Initialize(HINSTANCE hInstance) override;
	bool Terminate() override;
	bool Input() override;
	bool Process() override;
	bool Render() override;

	bool AppWindowed() override { return true; }
	int DispSizeW() override { return 1280; }
	int DispSizeH() override { return 720; }
	//ModeServer& getModeServer() { return *_modeServer; };

protected:

	int _x, _y;
	int LightHandle01, LightHandle02, shadowMapHandle, animIndexOld;
	float spd, cameraDir, cameraHigh;
	VECTOR cameraPos, cameraFor;
	//modelInf plMI, stage;
	std::string NS;

	bool debugMode = true;
public:
};