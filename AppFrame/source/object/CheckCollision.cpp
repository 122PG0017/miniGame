/*****************************************************************//**
 * \file   CheckCollision.cpp
 * \brief  コリジョンの交差判定を行う関数を持つクラス
 *
 * \author 土居将太郎
 * \date   April 2023
 *********************************************************************/
#include "CheckCollision.h"
#include "SphereCollisionComponent.h"
#include "AABBCollisionComponent.h"

namespace AppFrame {

    bool CheckCollision::Intersect(SphereCollisionComponent* sphereLeft, SphereCollisionComponent* sphereRight)
    {
        float positionDistance = VSize(VSub(sphereLeft->GetPosition(), sphereRight->GetPosition()));
        return positionDistance <= sphereLeft->GetRadius() + sphereRight->GetRadius();
    }

    bool CheckCollision::Intersect(SphereCollisionComponent* sphere, AABBCollisionComponent* aabb)
    {
        VECTOR aabbMin = VSub(aabb->GetPosition(), VScale(aabb->GetSize(), 0.5f));
        VECTOR aabbMax = VAdd(aabb->GetPosition(), VScale(aabb->GetSize(), 0.5f));
        VECTOR sphereToAABB = VSub(aabb->GetPosition(), sphere->GetPosition());
        float lengthSphereToAABB = VSize(sphereToAABB);

        auto nearestPointOnSphere = VAdd(sphere->GetPosition(), VScale(sphereToAABB, Math::Min(lengthSphereToAABB, sphere->GetRadius())));
        return (nearestPointOnSphere.x >= aabbMin.x && nearestPointOnSphere.x <= aabbMax.x) &&
               (nearestPointOnSphere.y >= aabbMin.y && nearestPointOnSphere.y <= aabbMax.y) &&
               (nearestPointOnSphere.z >= aabbMin.z && nearestPointOnSphere.z <= aabbMax.z);
    }

    bool CheckCollision::Intersect(SphereCollisionComponent* sphere, int modelHandle)
    {
        MV1RefreshCollInfo(modelHandle);
        auto resut = MV1CollCheck_Sphere(modelHandle, -1, sphere->GetPosition(), sphere->GetRadius());

        return resut.HitNum > 0;
    }

    bool CheckCollision::Intersect(AABBCollisionComponent* aabb, SphereCollisionComponent* sphere)
    {
        return Intersect(sphere, aabb);
    }

    bool CheckCollision::Intersect(AABBCollisionComponent* aabbLeft, AABBCollisionComponent* aabbRight)
    {
        VECTOR leftMin = VSub(aabbLeft->GetPosition(), VScale(aabbLeft->GetSize(), 0.5f));
        VECTOR leftMax = VAdd(aabbLeft->GetPosition(), VScale(aabbLeft->GetSize(), 0.5f));
        VECTOR rightMin = VSub(aabbRight->GetPosition(), VScale(aabbRight->GetSize(), 0.5f));
        VECTOR rightMax = VAdd(aabbRight->GetPosition(), VScale(aabbRight->GetSize(), 0.5f));
        return (leftMin.x <= rightMax.x && leftMax.x >= rightMin.x) &&
               (leftMin.y <= rightMax.y && leftMax.y >= rightMin.y) &&
               (leftMin.z <= rightMax.z && leftMax.z >= rightMin.z);
    }

    bool CheckCollision::Intersect(int modelHandle, SphereCollisionComponent* right)
    {
        return Intersect(right, modelHandle);
    }

}