#pragma once

#include <cmath>

namespace cuda
{
#ifdef RT_DLL
	//Vector with 3 dimensions
	struct Vector3
	{
		float x, y, z;

		__device__ __host__ explicit Vector3()
			: x(0.0f), y(0.0f), z(0.0f) {}
		__device__ __host__ explicit Vector3(const float _x, const float _y, const float _z)
			: x(_x), y(_y), z(_z) {}

		__device__ __host__ Vector3 operator + (const Vector3& vector) const
		{
			Vector3 res;
			res.x = x + vector.x;
			res.y = y + vector.y;
			res.z = z + vector.z;

			return res;
		}

		__device__ __host__ Vector3 operator - (const Vector3& vector) const
		{
			Vector3 res;
			res.x = x - vector.x;
			res.y = y - vector.y;
			res.z = z - vector.z;

			return res;
		}

		__device__ __host__ Vector3 operator * (const float scalar) const
		{
			Vector3 res;
			res.x = x * scalar;
			res.y = y * scalar;
			res.z = z * scalar;

			return res;
		}

		__device__ __host__ Vector3 operator / (const float scalar) const
		{
			Vector3 res;
			res.x = x / scalar;
			res.y = y / scalar;
			res.z = z / scalar;

			return res;
		}

		__device__ __host__ void operator += (const Vector3& vector)
		{
			*this = *this + vector;
		}

		__device__ __host__ void operator -= (const Vector3& vector)
		{
			*this = *this + vector;
		}

		__device__ __host__ void operator *= (const float scalar)
		{
			*this = *this * scalar;
		}

		__device__ __host__ void operator /= (const float scalar)
		{
			*this = *this / scalar;
		}
	};

	inline __device__ float Length(const Vector3& vec) { return sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2)); }
	inline __device__ float Dot(const Vector3& vec1, const Vector3& vec2) { return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z; }
	inline __device__ Vector3 Normalize(const Vector3& vec) { return vec / Length(vec); }

	//Ray
	struct Ray
	{
		Vector3 Origin;
		Vector3 Direction;
	};

	inline __device__ Vector3 PointAt(const Ray& ray, const float distance) { return ray.Origin + ray.Direction * distance; }


	//Convert degree to radians
	#define PI 3.1415926f
	inline __device__ float Radians(const float degree) { return degree * PI / 180.0f; }
#else
	//Vector with 3 dimensions
	struct Vector3
	{
		float x, y, z;

		    explicit Vector3()
			: x(0.0f), y(0.0f), z(0.0f) {}
		    explicit Vector3(const float _x, const float _y, const float _z)
			: x(_x), y(_y), z(_z) {}

		    Vector3 operator + (const Vector3& vector) const
		{
			Vector3 res;
			res.x = x + vector.x;
			res.y = y + vector.y;
			res.z = z + vector.z;

			return res;
		}

		    Vector3 operator - (const Vector3& vector) const
		{
			Vector3 res;
			res.x = x - vector.x;
			res.y = y - vector.y;
			res.z = z - vector.z;

			return res;
		}

		    Vector3 operator * (const float scalar) const
		{
			Vector3 res;
			res.x = x * scalar;
			res.y = y * scalar;
			res.z = z * scalar;

			return res;
		}

		    Vector3 operator / (const float scalar) const
		{
			Vector3 res;
			res.x = x / scalar;
			res.y = y / scalar;
			res.z = z / scalar;

			return res;
		}

		    void operator += (const Vector3& vector)
		{
			*this = *this + vector;
		}

		    void operator -= (const Vector3& vector)
		{
			*this = *this + vector;
		}

		    void operator *= (const float scalar)
		{
			*this = *this * scalar;
		}

		    void operator /= (const float scalar)
		{
			*this = *this / scalar;
		}
	};

	inline   float Length(const Vector3& vec) { return sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2)); }
	inline   float Dot(const Vector3& vec1, const Vector3& vec2) { return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z; }
	inline   Vector3 Normalize(const Vector3& vec) { return vec / Length(vec); }

	//Ray
	struct Ray
	{
		Vector3 Origin;
		Vector3 Direction;
	};

	inline   Vector3 PointAt(const Ray& ray, const float distance) { return ray.Origin + ray.Direction * distance; }


	//Convert degree to radians
#define PI 3.1415926f
	inline   float Radians(const float degree) { return degree * PI / 180.0f; }
#endif
}