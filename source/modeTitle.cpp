#include <fstream>
#include <sstream>
#include"modeTitle.h"

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
	loadData("game/res/save.csv", &_modeServer->_valData);

	//âπê∫ÉfÅ[É^ÇÃì«Ç›çûÇ›
	for (int i = 0; i < 7; i++)
	{

	}

	return true;
}

bool	modeTitle::Process()
{

	if (isPut == 1 && !CheckHitKeyAll() || isPut == 0 && !_modeServer->_valData.isLogoRender) { isPut = 2; }
	if ((_imputInf._gTrgb[KEY_INPUT_RETURN] || _imputInf._gTrgp[XINPUT_BUTTON_A]) && !_modeServer->_valData.isLogoRender && isPut == 2)
	{
		StopMusic();
		//PlaySoundMem(titleCallHaldle[rand() % 7], DX_PLAYTYPE_BACK);
		//_modeServer->Add(std::make_unique<>(_modeServer), 1, );
		return false;
	}
	return true;
}

bool	modeTitle::Render()
{

	if (_modeServer->_valData.isLogoRender)
	{//logoAlphaNum

	}
	else
	{

		//DrawString(1200, 20, "TITLEmode", GetColor(255, 255, 255));
	}
	return true;
}

bool	modeTitle::Terminate()
{
	StopMusic();
	return true;
}