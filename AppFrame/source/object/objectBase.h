#pragma once
#include <DxLib.h>
#include <string>
#include <map>
#include <memory>
#include <typeindex>
#include"../AppFrame/source/Math/math.h"

namespace AppFrame {
    class InputManager;
    class ModeBase;
    class ComponentBase;
    class ObjectBase {
    public:
        ObjectBase();
        virtual ~ObjectBase();
        //オブジェクトサーバーに追加した際に呼ばれる
        virtual void Initialize();
        //オブジェクトサーバーから削除された際に呼ばれる
        virtual void Terminate();
        virtual void Process(InputManager& input);
        virtual void Render();
        virtual void Debug();

        VECTOR GetPosition()const { return _position; }
        VECTOR GetRotation()const { return _rotation; }
        VECTOR GetScale()const { return _scale; }
        virtual void SetPosition(VECTOR position) { _position = position; }
        virtual void SetPosition(int positionX, int positionY) { _position = { static_cast<float>(positionX), static_cast<float>(positionY), 0.0f }; }
        virtual void SetRotation(VECTOR rotation) { _rotation = rotation; }
        virtual void SetScale(VECTOR scale) { _scale = scale; }
        MATRIX GetPositionMatrix()const { return _positionMatrix; }
        MATRIX GetRotationMatrix()const { return _rotationMatrix; }
        MATRIX GetScaleMatrix()const { return _scaleMatrix; }
        MATRIX GetTransform()const { return _transrom; }
        virtual void SetPositionMatrix(MATRIX posmatrix) { _positionMatrix = posmatrix; }
        virtual void SetRotationMatrix(MATRIX rotmatrix) { _rotationMatrix = rotmatrix; }

        virtual bool IsDead()const { return _dead; }
        virtual void Dead() { _dead = true; }

        bool GetVisible()const { return _visible; }
        void SetVisible(bool flag) { _visible = flag; }
        int GetLayer()const { return _layer; }
        void SetLayer(int value) { _layer = value; }
        int GetID()const { return _id; }
        void SetID(int value) { _id = value; }
        std::string_view GetName()const { return _name; }
        void SetName(std::string string) { _name = string; }
        ModeBase* GetMode()const { return _mode; }
        void SetMode(ModeBase* mode) { _mode = mode; }

        virtual float GetSpdParam() { return _spdParam; }
        float _spdParam;                         //加速度倍率

        //同型コンポーネントを追加する際は異なるIDを設定する
        virtual void AddComponent(std::unique_ptr<ComponentBase> component, int id = 0);

        /**
         * \brief 指定のコンポーネントを取得する　例：GetComponent<MV1Component>()
         * \return コンポーネントのポインタを返す。所持していなければnullptrを返す。
         */
        template <typename C>
        C* GetComponent(int id = 0) {
            C* result = nullptr;

            if (_components.count({ typeid(C), id }) != 0) {
                result = static_cast<C*>(_components[{typeid(C), id}].get());
            }
            return result;
        }

        /**
         * \brief 指定のクラスか確認する　例：CheckType<Player>()、CheckType<Enemy>()
         * \return 指定のクラスであればtrueを返す
         */
        template <typename T>
        bool CheckType()const {
            if (typeid(T&) == typeid(*this)) {
                return true;
            }

            return false;
        }

    protected:
        bool _visible;//Renderで描画するかの判定に使用

        std::string		_name;//オブジェクトに名前を付けて検索が可能
        int				_id;//インスタンス作成時に固有のIDが割り振られる、検索が可能
        int				_layer;//描画順

        VECTOR _position;
        VECTOR _rotation;
        VECTOR _scale;
        MATRIX _positionMatrix;
        MATRIX _rotationMatrix;
        MATRIX _scaleMatrix;
        MATRIX _transrom;
        bool _dead;

        std::map<std::pair<std::type_index, int>, std::unique_ptr<ComponentBase>> _components;

        ModeBase* _mode;
    };
}