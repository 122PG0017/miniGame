
void GameObjectBase::AddGameComponent(std::unique_ptr<GameComponentBase> component, int id)
{
    component->SetParent(this);

    if (component->Initialize()) {
        _components[{typeid(*component), id}] = (std::move(component));
    }
}

Player* GameObjectBase::GetPlayer()
{
    return static_cast<Player*>(_mode->GetObjectServer()->Get("Player"));
}

CubeEnemy* GameObjectBase::GetCubeEnemy()
{
    return static_cast<CubeEnemy*>(_mode->GetObjectServer()->Get("cube"));
}
