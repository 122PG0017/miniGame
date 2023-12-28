#pragma once
class GameObjectBase;

class GameComponentBase : public AppFrame::ComponentBase
{
public:
    void SetParent(GameObjectBase* parent) { _parent = parent; }
protected:
    GameObjectBase* _parent;
};