#pragma once
class Enemy :public GameObjectBase
{
public:
	using ObjectBase::AddComponent;
	Enemy();
	~Enemy();
	void Initialize()override;
	void Terminate()override;
	void Process(InputManager& input)override;
	void Render()override;
protected:
	int Handle;
};
