/*****************************************************************//**
 * \file   AABBCollisionComponent.h
 * \brief  AABB(ワールド座標軸に沿った箱形状)コリジョン
 *
 * \author 土居将太郎
 * \date   April 2023
 *********************************************************************/
#pragma once
#include "ComponentBase.h"
namespace AppFrame {
    class AABBCollisionComponent :public ComponentBase
    {
    public:
        bool Initialize()override;
        void Process(InputManager& input)override;
        void Render()override;
        void Debug()override;
        VECTOR GetPosition();
        void SetSize(VECTOR value) { _size = value; }
        VECTOR GetSize() { return _size; }
        void SetAttachFrame(int value) { _attachFrame = value; }
        int GetAttachFrame() { return _attachFrame; }
        void SetOffset(VECTOR value) { _offset = value; }
        VECTOR GetOffset() { return _offset; }
    private:
        VECTOR _offset;//親オブジェクトのルート、あるいはアタッチボーンからの位置オフセット量
        VECTOR _size;//箱状コリジョンサイズ用
        int _attachFrame;//アタッチされているフレーム（ボーンの別称）
    };
}