#pragma once
#include<../AppFrame/source/appframe.h>
#include <cmath>
#include <iostream>
#include <random>

namespace AppFrame {
	// 2Dベクトルクラス
	template<typename T>
	class VECTOR2 {
	public:
		// x成分,y成分
		T x, y;
		// コンストラクタ
		VECTOR2() noexcept = default;
		constexpr VECTOR2(T inX, T inY) noexcept
			: x{ inX }
			, y{ inY } {
		}
		// ベクトルの加算 a + b ※外部関数
		friend bool operator==(const VECTOR2& a, const VECTOR2& b) {
			if (a.x == b.x && a.y == b.y) {
				return true;
			}
			else {
				return false;
			}
		}
		// ベクトルの加算 a + b ※外部関数
		friend VECTOR2 operator+(const VECTOR2& a, const VECTOR2& b) {
			return { a.x + b.x, a.y + b.y };
		}
		// ベクトルの減算 a - b ※外部関数
		friend VECTOR2 operator-(const VECTOR2& a, const VECTOR2& b) {
			return { a.x - b.x, a.y - b.y };
		}
		// ベクトルのスカラー倍 v * scalar ※外部関数
		friend VECTOR2 operator*(const VECTOR2& v, double scalar) {
			return { v.x * scalar, v.y * scalar };
		}
		// ベクトルのスカラー倍 scalar * v ※外部関数
		friend VECTOR2 operator*(double scalar, const VECTOR2& v) {
			return { v.x * scalar, v.y * scalar };
		}

		// ベクトルのスカラー除算 scalar * v ※外部関数
		friend VECTOR2 operator/(const VECTOR2& v, double scalar) {
			return { v.x / scalar, v.y / scalar };
		}
		// ベクトル加算代入
		VECTOR2& operator+=(const VECTOR2& right) {
			x += right.x;
			y += right.y;
			return *this;
		}
		// ベクトル減算代入
		VECTOR2& operator-=(const VECTOR2& right) {
			x -= right.x;
			y -= right.y;
			return *this;
		}
		// ベクトルのスカラ乗算代入
		VECTOR2& operator*=(double scalar) {
			x *= scalar;
			y *= scalar;
			return *this;
		}
	};
	namespace Math {
		// 円周率
		constexpr float Pi = 3.1415926535f;
		constexpr float TwoPi = Pi * 2.0f;
		constexpr float PiOver2 = Pi / 2.0f;

		// 度数から孤度(ラジアン)に変換
		inline float ToRadians(float degrees) {
			return degrees * Pi / 180.0f;
		}
		// 孤度から度数(ディグリー)に変換
		inline float ToDegrees(float radians) {
			return radians * 180.0f / Pi;
		}
		// 二つの値の大きい値を取得
		template <typename T>
		T Max(const T& a, const T& b) {
			return (a < b ? b : a);
		}
		// 二つの値の小さい値を取得
		template <typename T>
		T Min(const T& a, const T& b) {
			return (a < b ? a : b);
		}
		// 二つの値の間でクランプする
		template <typename T>
		T Clamp(const T& value, const T& lower, const T& upper) {
			return Min(upper, Max(lower, value));
		}
		// 二つの値の間でクランプする
		template <typename T>
		bool Clamp2(T& value, const T& lower, const T& upper) {
			T oldValue = value;
			value = Min(upper, Max(lower, value));

			if (oldValue == value)
			{
				return false;
			}

			return true;
		}

		inline VECTOR VECTORClamp(VECTOR v, float min, float max)
		{
			v = { Clamp(v.x, min, max), Clamp(v.y, min, max), Clamp(v.z, min, max) };
			return v;
		}

		inline bool VECTORClamp2(VECTOR v, float min, float max)
		{
			if (Clamp2(v.x, min, max) || Clamp2(v.y, min, max) || Clamp2(v.z, min, max))
			{
				return true;
			}

			return false;
		}

		//自然数を返す剰余算
		template <typename T>
		inline T Modulo(T n, T modulo) {
			if (n < 0) {
				n += modulo;
			}

			return n % modulo;
		}


		inline VECTOR VZero()
		{
			return { 0.0f, 0.0f, 0.0f };
		}

		inline VECTOR VUp()
		{
			return { 0.0f, 1.0f, 0.0f };
		}

		inline VECTOR VForward()
		{
			return { 0.0f, 0.0f, -1.0f };
		}

		inline VECTOR VRight()
		{
			return { 1.0f, 0.0f, 0.0f };
		}

		//内積のなす角をdegで返す
		inline float VDot2Deg(VECTOR v1, VECTOR v2) {
			float vd = VDot(v1, v2);
			float absv = VSize(v1) * VSize(v2);
			return ToDegrees(std::acos(vd / absv));
		}
		//線形補間
		inline VECTOR Lerp(VECTOR start, VECTOR end, float lerpParam) {
			return  VAdd(start, VScale(VSub(end, start), lerpParam));
		}

		//内積のなす角をradで返す
		inline float VDot2Rad(VECTOR v1, VECTOR v2) {
			float vd = VDot(v1, v2);
			float absv = VSize(v1) * VSize(v2);
			return std::acos(vd / absv);
		}

		//球面線形補間//(始点、終点、回転の中心点、現在の位置パラメーター)
		//正規化ベクトル始点終点の平行線と現在の位置、中心点座標から平行四辺形を作成し
		//それを分割した三角形（正規化ベクトルなので一辺の大きさは1)の二辺から補間を取得。
		//それら二辺を加算して現在位置座標を補間する
		//aを最大角、bが始点、cが現在位置それぞれの角に対応した辺とする
		inline VECTOR SLerp(VECTOR start, VECTOR end, VECTOR center, float parameter) {
			VECTOR s = VSub(start, center);
			VECTOR e = VSub(end, center);
			float dot = VDot2Rad(s, e);//内積のなす角rad
			float aTheta = Math::ToRadians(180) - dot;
			//角度とa辺の長さがわかったので正弦定理で始点終点に平行な直線の補間座標を加算し正規化された現在位置座標を取得
			VECTOR c = VScale(VNorm(e), sin(dot * parameter) / sin(aTheta));
			VECTOR b = VScale(VNorm(s), sin(dot * (1 - parameter)) / sin(aTheta));
			VECTOR a = VAdd(b, c);
			//補間された座標を始点終点間の線形補間でそろえる
			float lerp = VSize(s) + ((VSize(e) - VSize(s)) * parameter);
			VECTOR add = VScale(a, lerp);
			VECTOR slerp = VAdd(center, add);
			return slerp;
		}

		//ベクター2点間の距離の大きさを返す
		inline float DistanceV2V(VECTOR one, VECTOR two) {
			return VSize(VSub(one, two));
		}
		//ベクター2点間距離の大きさの絶対値で返す
		inline float AbsDistanceV2V(VECTOR one, VECTOR two) {
			return fabs(DistanceV2V(one, two));
		}
		//反射ベクトルを返す（進行方向ベクトル、面の法線ベクトル)
		inline VECTOR Reflection(VECTOR forward, VECTOR normalLine) {
			float dot = VDot(VScale(forward, -1.0f), normalLine);
			VECTOR reflection = VScale(normalLine, dot * 2.0f);
			return VAdd(forward, reflection);
		}
		/**
		 * 特定の桁の値を取得する
		 *
		 * \param value 取得したい数値
		 * \param digit 取得したい桁
		 * \return 特定の桁の値、エラーの時-1
		 */
		inline int GetDigitNumber(int value, int digit) {
			if (digit == 1) { return value % (static_cast<int>(std::pow(10, digit))); }

			int a = value % (static_cast<int>(std::pow(10, digit)));
			int b = value % static_cast<int>(std::pow(10, digit - 1));
			return static_cast<int>((a - b) / static_cast<int>(std::pow(10, digit - 1)));
		}
		//行列からオイラー角の抽出
		inline VECTOR RotationMatrix2Euler(MATRIX rotationMatrix) {
			float x = atan2(rotationMatrix.m[1][2], rotationMatrix.m[2][2]);
			float y = -asin(-rotationMatrix.m[0][2]);
			float z = atan2(rotationMatrix.m[0][1], rotationMatrix.m[0][0]);
			return{ x, y, z };
		}

		//渡された度数法表記VECTOR型の中身を弧度法に変換
		inline VECTOR VDeg2Rad(VECTOR deg) {
			return { Math::ToRadians(deg.x),Math::ToRadians(deg.y), Math::ToRadians(deg.z) };
		}
		//渡された弧度法表記VECTOR型の中身を度数法に変換
		inline VECTOR VRad2Deg(VECTOR rad) {
			return { Math::ToDegrees(rad.x),Math::ToDegrees(rad.y), Math::ToDegrees(rad.z) };
		}
	};
}