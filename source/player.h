#pragma once
#include"charBase.h"

class player : public CharBase
{
public:
	player();
	~player();
	bool Initialize() override;
	bool Terminate() override;
	bool Process() override;
	bool Render(float timeSpeed) override;
protected:
	bool  isAnimEnd;
	imputInf _imputInf;
	modelInf _modelInf;
	Rserver* RS;
};