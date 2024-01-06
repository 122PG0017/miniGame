/*****************************************************************//**
 * \file   CheckCollision.h
 * \brief  コリジョンの交差判定を行う関数を持つクラス
 *
 * \author 土居将太郎
 * \date   April 2023
 *********************************************************************/
#pragma once
namespace AppFrame {
    class SphereCollisionComponent;
    class AABBCollisionComponent;
    class CheckCollision
    {
    public:
        /**
         * \brief 交差判定
         * \param sphereLeft 球状コリジョン1個目
         * \param sphereRight 球状コリジョン2個目
         * \return 交差していたらtrue
         */
        static bool Intersect(SphereCollisionComponent* sphereLeft, SphereCollisionComponent* sphereRight);
        /**
         * \brief 交差判定
         * \param sphere 球状コリジョン
         * \param aabb 箱状コリジョン
         * \return 交差していたらtrue
         */
        static bool Intersect(SphereCollisionComponent* sphere, AABBCollisionComponent* aabb);
        /**
         * \brief 交差判定
         * \param sphere 球状コリジョン
         * \param modelHandle 3Dモデルハンドル
         * \return 交差していたらtrue
         */
        static bool Intersect(SphereCollisionComponent* sphere, int modelHandle);
        /**
         * \brief 交差判定
         * \param aabb 箱状コリジョン
         * \param sphere 球状コリジョン
         * \return 交差していたらtrue
         */
        static bool Intersect(AABBCollisionComponent* aabb, SphereCollisionComponent* sphere);
        /**
         * \brief 交差判定
         * \param aabbLeft 箱状コリジョン1個目
         * \param aabbRight 箱状コリジョン2個目
         * \return 交差していたらtrue
         */
        static bool Intersect(AABBCollisionComponent* aabbLeft, AABBCollisionComponent* aabbRight);
        /**
         * \brief 交差判定
         * \param modelHandle 3Dモデルハンドル
         * \param sphere 球状コリジョン
         * \return 交差していたらtrue
         */
        static bool Intersect(int modelHandle, SphereCollisionComponent* right);
    };
}