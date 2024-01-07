#pragma once

class SkySphere:public GameObjectBase
{
public:
	SkySphere();
	~SkySphere();
	void Initialize()override;
	void Terminate()override;
	void Process(InputManager& input)override;
	void Render()override;
};
