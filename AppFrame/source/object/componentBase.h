#pragma once
#include"../appframe.h"
#include"inputManager.h"
namespace AppFrame {
    class ObjectBase;

    class ComponentBase {
    public:
        ComponentBase();
        ~ComponentBase();
        virtual bool Init();
        virtual void Process(InputManager& input);
        virtual void Render();
        virtual void Debug();

        virtual void SetParent(ObjectBase* parent) { _parent = parent; }
    protected:
        ObjectBase* _parent;
    };
}
