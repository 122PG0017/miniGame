#pragma once
#include"appframe.h"

class modeTitle : public ModeBase
{
public:
	modeTitle(ModeServer* MS) { _modeServer = MS; };
	~modeTitle() {};

	bool Initialize() override;
	bool Terminate() override;
	bool Imput(imputInf* iInf) override { _imputInf = *iInf; return true; };
	bool Process() override;
	bool Render() override;
	static bool loadData(const char* dir, valData* _val);
	static bool save(const char* dir, valData* _val);

protected:
	int isPut = 0;
	ModeServer* _modeServer;
	imputInf _imputInf;
};