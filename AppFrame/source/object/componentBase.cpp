#include "ComponentBase.h"

namespace AppFrame {
    ComponentBase::ComponentBase()
        :_parent{ nullptr }
    {
    }

    ComponentBase::~ComponentBase()
    {
    }

    bool ComponentBase::Initialize()
    {
        return true;
    }

    void ComponentBase::Process(InputManager& input)
    {
    }

    void ComponentBase::Render()
    {
    }

    void ComponentBase::Debug()
    {
    }
}