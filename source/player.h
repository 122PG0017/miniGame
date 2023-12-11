#pragma once

class player : public gameObjectBase
{
public:
	using ObjectBase::AddComponent;
	player() {};
	~player() {};
	void Initialize()override;
	void Terminate()override;
	void Process(InputManager& input)override;
	void Render()override;
protected:
	int Handle;
	bool isAnimEnd;
	modelInf _modelInf;
	Rserver RS;
};