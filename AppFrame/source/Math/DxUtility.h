#pragma once
#include <DxLib.h>
/**
 * \brief �A�v���P�[�V�����t���[��
 */
namespace AppFrame {
	/**
	 * \brief �Z�p�֌W
	 */
	namespace Math {
		struct tagVECTOR;
		struct tagMATRIX;
		class Vector4;
		class Matrix44;
		/**
		 * \brief ����Vector4�N���X����DxLib::VECTOR�\���̂ւ̕ϊ�
		 * \param vector ����Vector4�N���X
		 */
		VECTOR ToDX(const Vector4& vector);
		/**
		 * \brief DxLib::VECTOR�\���̂��玩��Vector4�N���X�ւ̕ϊ�
		 * \param vector DxLib::VECTOR�\����
		 */
		Math::Vector4 ToMath(const VECTOR& vector);
		/**
		 * \brief ����Matrix44�N���X����DxLib::MATRIX�\���̂ւ̕ϊ�
		 * \param matrix ����Matrix44�N���X
		 */
		MATRIX ToDX(const Matrix44& matrix);
		/**
		 * \brief DxLib::MATRIX�\���̂��玩��Matirix44�N���X�ւ̕ϊ�
		 * \param matrix DxLib::MATRIX�\����
		 */
		Math::Matrix44 ToMath(const MATRIX& matrix);
	};
};