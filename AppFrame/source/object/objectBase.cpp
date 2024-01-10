#include "ObjectBase.h"
#include "ComponentBase.h"

namespace AppFrame {
    ObjectBase::ObjectBase()
        : _position{ 0, 0, 0 }
        , _rotation{ 0, 0, 0 }
        , _scale{ 1, 1, 1 }
        , _dead{ false }
        , _visible{ true }
        , _name{ "null" }
        , _id{ -1 }
        , _layer{ 0 }
        , _mode{ nullptr }
    {

    }

    ObjectBase::~ObjectBase()
    {
        _components.clear();
    }

    void ObjectBase::Initialize()
    {
    }

    void ObjectBase::Terminate()
    {
        _components.clear();
    }

    void ObjectBase::Process(InputManager& input)
    {
        _positionMatrix = MGetTranslate(_position);
        _rotationMatrix = MMult(MMult(MGetRotX(_rotation.x), MGetRotY(_rotation.y)), MGetRotZ(_rotation.z));
        _scaleMatrix = MGetScale(_scale);

        for (auto&& component : _components) {
            component.second->Process(input);
        }
    }

    void ObjectBase::Render()
    {
        if (!_visible) {
            return;
        }

        for (auto&& component : _components) {
            component.second->Render();
        }
    }

    void ObjectBase::Debug()
    {
        for (auto&& component : _components) {
            component.second->Debug();
        }
    }

    void ObjectBase::AddComponent(std::unique_ptr<ComponentBase> component, int id)
    {
        component->SetParent(this);

        if (component->Initialize()) {
            _components[{typeid(*component), id}] = (std::move(component));
        }
    }
}