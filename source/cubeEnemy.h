#pragma once
class CubeEnemy :public GameObjectBase
{
public:
	using ObjectBase::AddComponent;
	CubeEnemy();
	~CubeEnemy();
	void Initialize()override;
	void Terminate()override;
	void Process(InputManager& input)override;
	void Render()override;
protected:
	int Handle;
};
