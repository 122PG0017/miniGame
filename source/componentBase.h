#pragma once
#include"appframe.h"
#include"inputManager.h"

class ObjectBase;

class ComponentBase {
public:
    ComponentBase();
    ~ComponentBase();
    virtual bool Init();
    virtual void Update(InputManager& input);
    virtual void Render();
    virtual void Debug();

    virtual void SetParent(ObjectBase* parent) { _parent = parent; }
protected:
    ObjectBase* _parent;
};