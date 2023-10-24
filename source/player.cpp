#include"player.h"
using namespace model;
bool player::Initialize()
{
	modelImport("resource/Knight/MV1/enemy_1_.mv1", 1.0f, &_modelInf, RS);
	return true;
}

bool player::Terminate()
{
	return false;
}

bool player::Process()
{
	return false;
}

bool player::Render(float timeSpeed)
{
	isAnimEnd = modelRender(&_modelInf, 1, timeSpeed);
	return false;
}
