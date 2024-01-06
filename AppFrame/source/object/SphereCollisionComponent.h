/*****************************************************************//**
 * \file   CollisionComponent.h
 * \brief  球状コリジョン
 *
 * \author 土居将太郎
 * \date   December 2022
 *********************************************************************/
#pragma once
#include "ComponentBase.h"
namespace AppFrame {
    class  SphereCollisionComponent :public ComponentBase
    {
    public:
        SphereCollisionComponent();
        ~SphereCollisionComponent();
        bool Initialize()override;
        void Process(InputManager& input)override;
        void Render()override;
        void Debug()override;
        VECTOR GetPosition();
        void SetRadius(float value) { _radius = value; }
        float GetRadius() { return _radius; }
        void SetAttachFrame(int value) { _attachFrame = value; }
        int GetAttachFrame() { return _attachFrame; }
        void SetOffset(VECTOR value) { _offset = value; }
        VECTOR GetOffset() { return _offset; }

    private:
        VECTOR _offset;//親オブジェクトのルート、あるいはアタッチボーンからの位置オフセット量
        float _radius;//球状コリジョンサイズ用
        int _attachFrame;//アタッチされているフレーム（ボーンの別称）
    };
}