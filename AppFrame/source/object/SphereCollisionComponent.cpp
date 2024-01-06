/*****************************************************************//**
 * \file   SphereCollisionComponent.cpp
 * \brief  球状コリジョン、AABBコリジョン
 *
 * \author 土居将太郎
 * \date   December 2022
 *********************************************************************/
#include "SphereCollisionComponent.h"
#include "ObjectBase.h"
#include "componentMV1.h"

namespace AppFrame {
    SphereCollisionComponent::SphereCollisionComponent()
    {
        _offset = { 0.0f, 0.0f, 0.0f };
        _radius = { 10.0f };
        _attachFrame = -1;
    }

    SphereCollisionComponent::~SphereCollisionComponent()
    {
    }

    bool SphereCollisionComponent::Initialize()
    {
        return true;
    }

    void SphereCollisionComponent::Process(InputManager& input)
    {

    }

    void SphereCollisionComponent::Render()
    {
    }

    void SphereCollisionComponent::Debug()
    {
        DrawSphere3D(GetPosition(), _radius, 12, GetColor(255, 255, 0) , GetColor(0, 0, 0), false);
    }
    VECTOR SphereCollisionComponent::GetPosition()
    {
        VECTOR position = _parent->GetPosition();

        if (_attachFrame > -1) {
            auto handle = _parent->GetComponent<MV1Component>()->GetModelHandle();
            auto matrix = MV1GetFrameLocalWorldMatrix(handle, _attachFrame);
            position = VAdd(VTransform(Math::VZero(), matrix), _offset);
        }

        return VAdd(position, _offset);
    }
}