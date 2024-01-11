#pragma once

class Stage :public GameObjectBase
{
public:
	Stage();
	~Stage();
	void Initialize()override;
	void Terminate()override;
	void Process(InputManager& input)override;
	void Render()override;
	void Debug() override;
};
