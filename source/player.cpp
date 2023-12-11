using namespace AppFrame;
using namespace model;

void player::Initialize()
{
	ObjectBase::Initialize();
	modelImport("resource/Knight/MV1/enemy_1_.mv1", 1.0f, &_modelInf, &RS);
	_modelInf.pos = VECTOR(0, 0, 0);
	RS.duplicateModelListImportR();
	animChange(2, &_modelInf, false, false, false);
}

void player::Terminate()
{
	model::modelDelete(&_modelInf);
	ObjectBase::Terminate();
}

void player::Process(InputManager& input)
{
	ObjectBase::Process(input);
}

void player::Render()
{
	isAnimEnd = modelRender(&_modelInf, 1, 1);
	ObjectBase::Render();
}
