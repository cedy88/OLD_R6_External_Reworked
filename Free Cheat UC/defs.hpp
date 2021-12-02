#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <cstddef>
#include <cmath>
#define M_PI 3.14159265
#define RAD_TO_DEG(x) x * (180.f / M_PI)
#define DEG_TO_RAD(x) x * (M_PI / 180.f)

typedef          __int64 ll;
typedef unsigned __int64 ull;

typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned long ulong;

typedef          char   int8;
typedef   signed char   sint8;
typedef unsigned char   uint8;
typedef          short  int16;
typedef   signed short  sint16;
typedef unsigned short  uint16;
typedef          int    int32;
typedef   signed int    sint32;
typedef unsigned int    uint32;
typedef ll              int64;
typedef ll              sint64;
typedef ull             uint64;

struct vec4
{
	float x, y, z, w;
};

struct vec3
{
	float x, y, z;

	vec3 operator-(vec3 ape)
	{
		return { x - ape.x, y - ape.y, z - ape.z };
	}

	vec3 operator+(vec3 ape)
	{
		return { x + ape.x, y + ape.y, z + ape.z };
	}

	vec3 operator*(float ape)
	{
		return { x * ape, y * ape, z * ape };
	}

	vec3 operator/(float ape)
	{
		return { x / ape, y / ape, z / ape };
	}

	vec3 operator/=(float ape)
	{
		x /= ape;
		y /= ape;
		z /= ape;

		return *this;
	}

	vec3 operator+=(vec3 ape)
	{
		return { x += ape.x, y += ape.y, z += ape.z };
	}

	vec3 operator-=(vec3 ape)
	{
		return { x -= ape.x, y -= ape.y, z -= ape.z };
	}

	vec3 TransformVec(vec3 angle, float ape)
	{
		vec3 ret;
		ret.x = x - cosf(DEG_TO_RAD(angle.x)) * ape;
		ret.y = y - sinf(DEG_TO_RAD(angle.x)) * ape;
		ret.z = z + tanf(DEG_TO_RAD(angle.z)) * ape;
		return ret;
	}

	void Normalize()
	{
		while (x > 89.0f)
			x -= 180.f;

		while (x < -89.0f)
			x += 180.f;

		while (y > 180.f)
			y -= 360.f;

		while (y < -180.f)
			y += 360.f;
	}

	float Length()
	{
		return sqrt((x * x) + (y * y) + (z * z));
	}

	float Length2D()
	{
		return sqrt((x * x) + (y * y));
	}

	float DistTo(vec3 ape)
	{
		return (*this - ape).Length();
	}

	float Dist2D(vec3 ape)
	{
		return (*this - ape).Length2D();
	}

	float Dot(vec3 ape)
	{
		return (x * ape.x) + (y * ape.y) + (z * ape.z);
	}
};

struct vec2
{
	float x, y;

	vec2 operator-(vec2 ape)
	{
		return { x - ape.x, y - ape.y };
	}

	vec2 operator+(vec2 ape)
	{
		return { x + ape.x, y + ape.y };
	}

	vec2 operator*(float ape)
	{
		return { x * ape, y * ape };
	}

	vec2 operator/(float ape)
	{
		return { x / ape, y / ape };
	}

	vec2 operator/=(float ape)
	{
		x /= ape;
		y /= ape;

		return *this;
	}

	vec2 operator+=(vec2 ape)
	{
		return { x += ape.x, y += ape.y };
	}

	vec2 operator-=(vec2 ape)
	{
		return { x -= ape.x, y -= ape.y };
	}

	void Normalize()
	{
		if (x > 89.0f)
			x -= 180.f;

		if (x < -89.0f)
			x += 180.f;

		if (y > 180.f)
			y -= 360.f;

		if (y < -180.f)
			y += 360.f;
	}

	float Length2D()
	{
		return sqrt((x * x) + (y * y));
	}

	float Dist2D(vec2 ape)
	{
		return (*this - ape).Length2D();
	}
};

constexpr float r2d = 57.2957795131f;
constexpr float d2r = 0.01745329251f;

// Rotate left
template<class T> T __ROL__(T value, int count)
{
	const uint nbits = sizeof(T) * 8;

	if (count > 0)
	{
		count %= nbits;
		T high = value >> (nbits - count);
		if (T(-1) < 0) // signed value
			high &= ~((T(-1) << count));
		value <<= count;
		value |= high;
	}
	else
	{
		count = -count % nbits;
		T low = value << (nbits - count);
		value >>= count;
		value |= low;
	}
	return value;
}

inline uint8  __ROL1__(uint8  value, int count) { return __ROL__((uint8)value, count); }
inline uint16 __ROL2__(uint16 value, int count) { return __ROL__((uint16)value, count); }
inline uint32 __ROL4__(uint32 value, int count) { return __ROL__((uint32)value, count); }
inline uint64 __ROL8__(uint64 value, int count) { return __ROL__((uint64)value, count); }
inline uint8  __ROR1__(uint8  value, int count) { return __ROL__((uint8)value, -count); }
inline uint16 __ROR2__(uint16 value, int count) { return __ROL__((uint16)value, -count); }
inline uint32 __ROR4__(uint32 value, int count) { return __ROL__((uint32)value, -count); }
inline uint64 __ROR8__(uint64 value, int count) { return __ROL__((uint64)value, -count); }