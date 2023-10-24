#include <fstream>
#include <sstream>
#include"modeTitle.h"
#include"modeTest.h"
using namespace model;
bool modeTitle::save(const char* dir, valData* _val)
{
	std::vector<std::string> _data;
	int points = _val->points;
	fileIO::loadCSV(&_data, dir, false);

	for (int i = 0; i < _data.size(); i++)
	{
		if (_data[i].find("//") != std::string::npos)
		{
			continue;
		}

		
	}
	std::string insStr = "";
	for (auto insData : _data) { insStr += insData + "\n"; }
	std::ofstream ofs(dir);
	ofs << insStr;
	ofs.close();

	return true;
}

bool modeTitle::loadData(const char* dir, valData* _val)
{
	std::vector<std::string> _data;
	fileIO::loadCSV(&_data, dir, false);

	return true;
}

bool	modeTitle::Initialize()
{
	_cg = _modeServer->RS.loadGraphR("resource/tmp/sky.png");

	return true;
}

bool	modeTitle::Process()
{

	if (isPut == 1 && !CheckHitKeyAll() || isPut == 0 ) { isPut = 2; }
	if ((_imputInf._gTrgb[KEY_INPUT_RETURN] || _imputInf._gTrgp[XINPUT_BUTTON_A]) && isPut == 2)
	{
		StopMusic();
		//PlaySoundMem(titleCallHaldle[rand() % 7], DX_PLAYTYPE_BACK);
		_modeServer->Add(std::make_unique<ModeTest>(_modeServer), 1,"test");
		return false;
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