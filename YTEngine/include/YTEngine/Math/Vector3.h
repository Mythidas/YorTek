#pragma once

#include "YTEngine/Reflection/Object.h"

#include <glm/glm.hpp>

namespace Yor
{
	template <typename T>
	struct TVector3;

	using Vector3 = TVector3<float>;
	using IVector3 = TVector3<int>;
	using UVector3 = TVector3<unsigned int>;

	template <typename T>
  struct TVector3 : public Object
  {
  public:
		TVector3() = default;
		TVector3(T value)
		{
			x = value;
			y = value;
			z = value;
		}
		TVector3(T _x, T _y, T _z)
		{
			x = _x;
			y = _y;
			z = _z;
		}
		TVector3(const glm::vec3& gvec3)
		{
			x = static_cast<T>(gvec3.x);
			y = static_cast<T>(gvec3.y);
			z = static_cast<T>(gvec3.z);
		}
		TVector3(const glm::ivec3& gvec3)
		{
			x = static_cast<T>(gvec3.x);
			y = static_cast<T>(gvec3.y);
			z = static_cast<T>(gvec3.z);
		}
		TVector3(const glm::uvec3& gvec3)
		{
			x = static_cast<T>(gvec3.x);
			y = static_cast<T>(gvec3.y);
			z = static_cast<T>(gvec3.z);
		}

		union { T x, r; };
		union { T y, g; };
		union { T z, b; };

		virtual void _registerData() override
		{
			_registerProperty<T>("X", offsetof(TVector3<T>, x));
			_registerProperty<T>("Y", offsetof(TVector3<T>, y));
			_registerProperty<T>("Z", offsetof(TVector3<T>, z));
		}

	public:
		inline static const glm::vec3 one{ 1.0f, 1.0f, 1.0f };
		inline static const glm::vec3 zero{ 0.0f, 0.0f, 0.0f };
		inline static const glm::vec3 up{ 0.0f, 1.0f, 0.0f };
		inline static const glm::vec3 right{ 1.0f, 0.0f, 0.0f };
		inline static const glm::vec3 left{ -1.0f, 0.0f, 0.0f };
		inline static const glm::vec3 down{ 0.0f, -1.0f, 0.0 };
		inline static const glm::vec3 back{ 0.0f, 0.0f, -1.0f };
		inline static const glm::vec3 forward{ 0.0f, 0.0f, 1.0f };

	public:
		// Scalar Ops
		TVector3<T> operator+(const T& rhs) const;
		TVector3<T> operator-(const T& rhs) const;
		TVector3<T> operator*(const T& rhs) const;
		TVector3<T> operator/(const T& rhs) const;

		TVector3<T>& operator+=(const T& rhs);
		TVector3<T>& operator-=(const T& rhs);
		TVector3<T>& operator*=(const T& rhs);
		TVector3<T>& operator/=(const T& rhs);

		// TVector3<T> Ops
		TVector3<T> operator+(const TVector3<T>& rhs) const;
		TVector3<T> operator-(const TVector3<T>& rhs) const;
		TVector3<T> operator*(const TVector3<T>& rhs) const;
		TVector3<T> operator/(const TVector3<T>& rhs) const;

		TVector3<T>& operator+=(const TVector3<T>& rhs);
		TVector3<T>& operator-=(const TVector3<T>& rhs);
		TVector3<T>& operator*=(const TVector3<T>& rhs);
		TVector3<T>& operator/=(const TVector3<T>& rhs);

		T operator[](int index) const
		{
			if (index == 0)
				return x;
			if (index == 1)
				return y;
			if (index == 2)
				return z;
		}

		operator glm::vec3() const
		{
			return glm::vec3(x, y, z);
		}
		operator glm::ivec3() const
		{
			return glm::ivec3(x, y, z);
		}
		operator glm::uvec3() const
		{
			return glm::uvec3(x, y, z);
		}
  };
	OBJ_CLASS(Vector3)
	OBJ_CLASS(IVector3)
	OBJ_CLASS(UVector3)

	// Scalar Ops

	template <typename T>
	inline TVector3<T> TVector3<T>::operator+(const T& rhs) const
	{
		return TVector3<T>(x + rhs, y + rhs, z + rhs);
	}
	template <typename T>
	inline TVector3<T> TVector3<T>::operator-(const T& rhs) const
	{
		return TVector3<T>(x - rhs, y - rhs, z - rhs);
	}
	template <typename T>
	inline TVector3<T> TVector3<T>::operator*(const T& rhs) const
	{
		return TVector3<T>(x * rhs, y * rhs, z * rhs);
	}
	template <typename T>
	inline TVector3<T> TVector3<T>::operator/(const T& rhs) const
	{
		return TVector3<T>(x / rhs, y / rhs, z / rhs);
	}
	template <typename T>
	inline TVector3<T>& TVector3<T>::operator+=(const T& rhs)
	{
		x += rhs; y += rhs; z += rhs;
		return *this;
	}
	template <typename T>
	inline TVector3<T>& TVector3<T>::operator-=(const T& rhs)
	{
		x -= rhs; y -= rhs; z -= rhs;
		return *this;
	}
	template <typename T>
	inline TVector3<T>& TVector3<T>::operator*=(const T& rhs)
	{
		x *= rhs; y *= rhs; z *= rhs;
		return *this;
	}
	template <typename T>
	inline TVector3<T>& TVector3<T>::operator/=(const T& rhs)
	{
		x /= rhs; y /= rhs; z /= rhs;
		return *this;
	}

	// TVector3<T> Ops

	template <typename T>
	inline TVector3<T> TVector3<T>::operator+(const TVector3<T>& rhs) const
	{
		return TVector3<T>(x + rhs.x, y + rhs.y, z + rhs.z);
	}
	template <typename T>
	inline TVector3<T> TVector3<T>::operator-(const TVector3<T>& rhs) const
	{
		return TVector3<T>(x - rhs.x, y - rhs.y, z - rhs.z);
	}
	template <typename T>
	inline TVector3<T> TVector3<T>::operator*(const TVector3<T>& rhs) const
	{
		return TVector3<T>(x * rhs.x, y * rhs.y, z * rhs.z);
	}
	template <typename T>
	inline TVector3<T> TVector3<T>::operator/(const TVector3<T>& rhs) const
	{
		return TVector3<T>(x / rhs.x, y / rhs.y, z / rhs.z);
	}
	template <typename T>
	inline TVector3<T>& TVector3<T>::operator+=(const TVector3<T>& rhs)
	{
		x += rhs.x; y += rhs.y; z += rhs.z;
		return *this;
	}
	template <typename T>
	inline TVector3<T>& TVector3<T>::operator-=(const TVector3<T>& rhs)
	{
		x -= rhs.x; y -= rhs.y; z -= rhs.z;
		return *this;
	}
	template <typename T>
	inline TVector3<T>& TVector3<T>::operator*=(const TVector3<T>& rhs)
	{
		x *= rhs.x; y *= rhs.y; z *= rhs.z;
		return *this;
	}
	template <typename T>
	inline TVector3<T>& TVector3<T>::operator/=(const TVector3<T>& rhs)
	{
		x /= rhs.x; y /= rhs.y; z /= rhs.z;
		return *this;
	}
}