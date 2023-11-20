#include "ComponentBase.h"


ComponentBase::ComponentBase()
    :_parent{ nullptr }
{
}

ComponentBase::~ComponentBase()
{
}

bool ComponentBase::Init()
{
    return true;
}

void ComponentBase::Update(InputManager& input)
{
}

void ComponentBase::Render()
{
}

void ComponentBase::Debug()
{
}