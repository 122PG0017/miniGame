/*****************************************************************//**
 * \file   MV1Component.h
 * \brief  MV1のトランスフォーム更新、描画、アニメーションフレームの進行機能
 *
 * \author 土居将太郎
 * \date   November 2022
 *********************************************************************/
#pragma once
#include "../AppFrame/source/object/componentBase.h"
#include <functional>
#include <algorithm>
#include <vector>
namespace AppFrame {
    class AnimationComponent;
    class MV1Component :public ComponentBase
    {
    public:
        MV1Component(int modelHandle);
        ~MV1Component();
        bool Initialize()override;
        void Process(InputManager& input)override;
        void Render()override;
        void Debug()override;
        void SetModelHandle(int modelHandle);
        int GetModelHandle() { return _modelHandle; }
        void SetAnimation(int index);
        void SetAnimSpeed(float value) { _animSpeed = value; };
        void SetValid(bool valid) { _isValid = valid; }
        void SetAttachIndex(int index) { _attahIndex = index; }
        float GetAnimSpeed() { return _animSpeed; }
        /**
         * \brief アニメーションの特定のタイミングで呼び出す関数を追加する
         * \param animIndex　アニメーションの番号
         * \param activateTime　アニメーションの時間
         * \param function 呼び出す関数
         */
        void AddAnimFunction(int animIndex, float activateTime, std::function<void(void)> function);

        void SetOriginalShader(const CHAR* vertexShaderPath, const CHAR* pixelShaderPath);
        void AddShaderBuffer(std::function<FLOAT4()> func, bool usePixelShader);

        void SetBloom(bool flag) { _bloom = flag; }
    private:
        /**
         * \brief タイミングを確認して、アニメーションに紐づく関数を呼び出す
         * \param preTime　前フレームのアニメーション時間
         * \param nowTime　現在フレームのアニメーション時間
         */
        void CheckAnimFunction(float preTime, float nowTime);

        //描画前のシェーダーの設定
        void SetShader();

        bool _isValid;
        int _modelHandle;
        int _animIndex;
        int _attahIndex;
        float _playTime, _totalTime;
        float _animSpeed;
        std::vector<std::vector<std::pair<float, std::function<void(void)>>>> _animFunction;//[アニメーションIndex][時間,呼び出し関数]

        bool _useOriginalShader;
        int _vertexShader;
        int _pixelShader;

        struct shaderBuffer {
            int _bufferHandle{ -1 };
            int _slot{ 1 };
            std::function < FLOAT4() > _getter;
            bool _usePixelShader{ true };//falseならvertexシェーダーで使用
        };
        std::vector<shaderBuffer> _constantBufferArray;

        bool _bloom;
    };
}
