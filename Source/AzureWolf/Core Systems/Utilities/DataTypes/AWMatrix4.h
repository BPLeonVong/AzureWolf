#pragma once

#include "../types.h"

namespace AW
{
	template <typename Real>
	class Matrix4 : public Table<4,4,Real>
	{
		public:
			Matrix4(bool makeZero = true);

			Matrix4(const Matrix4& mat);

			Matrix4(
				Real m00, Real m01, Real m02, Real m03,
				Real m10, Real m11, Real m12, Real m13,
				Real m20, Real m21, Real m22, Real m23,
				Real m30, Real m31, Real m32, Real m33,);

			Matrix4 (const Real entry[16], bool rowMajor);

			Matrix4& operator= (cont Matrix4& mat);

			void MakeZero();
			void MakeIdentity();

			Matrix4 operator+ (const Matrix4& mat) const;
			Matrix4 operator- (const Matrix4& mat) const;
			Matrix4 operator* (Real scalar) const;
			Matrix4 operator/ (Real scalar) const;
			Matrix4 operator- () const;

 
			Matrix4& operator+= (const Matrix4& mat);
			Matrix4& operator-= (const Matrix4& mat);
			Matrix4& operator*= (Real scalar);
			Matrix4& operator/= (Real scalar);

			Vector4<Real> operator* (const Vector4<Real>& vec) const;

			Real QForm (const Vector4<Real>& u, const Vector4<Real>& v) const;

			Matrix4 Transpose () const;

			Matrix4 operator* (const Matrix4& mat) const;

			Matrix4 TransposeTimes (const Matrix4& mat) const;

			Matrix4 TimesTranspose (const Matrix4& mat) const;

		    Matrix4 TransposeTimesTranspose (const Matrix4& mat) const;

			Matrix4 Inverse (const Real epsilon = (Real)0) const;
			Matrix4 Adjoint () const;
		    Real Determinant () const;

			void MakeObliqueProjection (const Vector3<Real>& normal,
			const Vector3<Real>& origin, const Vector3<Real>& direction);

			void MakePerspectiveProjection (const Vector3<Real>& normal,
			const Vector3<Real>& origin, const Vector3<Real>& eye);

		    void MakeReflection (const Vector3<Real>& normal,
			const Vector3<Real>& origin);

			static const Matrix4 ZERO;
			static const Matrix4 IDENTITY;

		protected:
			using Table<4,4,Real>::mEntry;
	};

	template <typename Real>
	inline Matrix4<Real> operator* (Real scalar, const Matrix4<Real>& mat);

	template <typename Real>
	inline Vector4<Real> operator* (const Vector4<Real>& vec,
    const Matrix4<Real>& mat);

	#include "AWMatrix4.inl"

	typedef Matrix4<float> Matrix4f;
	typedef Matrix4<double> Matrix4d;
}