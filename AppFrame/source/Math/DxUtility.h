#pragma once
#include <DxLib.h>
/**
 * \brief アプリケーションフレーム
 */
namespace AppFrame {
	/**
	 * \brief 算術関係
	 */
	namespace Math {
		struct tagVECTOR;
		struct tagMATRIX;
		class Vector4;
		class Matrix44;
		/**
		 * \brief 自作Vector4クラスからDxLib::VECTOR構造体への変換
		 * \param vector 自作Vector4クラス
		 */
		VECTOR ToDX(const Vector4& vector);
		/**
		 * \brief DxLib::VECTOR構造体から自作Vector4クラスへの変換
		 * \param vector DxLib::VECTOR構造体
		 */
		Math::Vector4 ToMath(const VECTOR& vector);
		/**
		 * \brief 自作Matrix44クラスからDxLib::MATRIX構造体への変換
		 * \param matrix 自作Matrix44クラス
		 */
		MATRIX ToDX(const Matrix44& matrix);
		/**
		 * \brief DxLib::MATRIX構造体から自作Matirix44クラスへの変換
		 * \param matrix DxLib::MATRIX構造体
		 */
		Math::Matrix44 ToMath(const MATRIX& matrix);
	};
};
