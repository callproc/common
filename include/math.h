#pragma once

#include <cmath>

#ifndef COMMON_MATH_H
#define COMMON_MATH_H
namespace math
{
    class vector2
    {
    public:
        float x, y;

        constexpr vector2() noexcept : x(0), y(0) {}
        constexpr vector2(float x, float y) noexcept : x(x), y(y) {}

        [[nodiscard]] constexpr vector2 operator+(const vector2& v) const noexcept { return { x + v.x, y + v.y }; }
        [[nodiscard]] constexpr vector2 operator-(const vector2& v) const noexcept { return { x - v.x, y - v.y }; }
        [[nodiscard]] constexpr vector2 operator*(const vector2& v) const noexcept { return { x * v.x, y * v.y }; }
        [[nodiscard]] constexpr vector2 operator/(const vector2& v) const noexcept { return { x / v.x, y / v.y }; }

        [[nodiscard]] constexpr vector2 operator*(float s) const noexcept { return { x * s, y * s }; }
        [[nodiscard]] constexpr vector2 operator/(float s) const noexcept { return { x / s, y / s }; }

        constexpr vector2& operator+=(const vector2& v) noexcept { x += v.x; y += v.y; return *this; }
        constexpr vector2& operator-=(const vector2& v) noexcept { x -= v.x; y -= v.y; return *this; }
        constexpr vector2& operator*=(float s)          noexcept { x *= s;   y *= s;   return *this; }
        constexpr vector2& operator/=(float s)          noexcept { x /= s;   y /= s;   return *this; }

        [[nodiscard]] constexpr vector2 operator-() const noexcept { return { -x, -y }; }

        [[nodiscard]] constexpr float dot(const vector2& v) const noexcept { return x * v.x + y * v.y; }
        [[nodiscard]] constexpr float cross(const vector2& v) const noexcept { return x * v.y - y * v.x; }
        [[nodiscard]] constexpr vector2 perp() const noexcept { return { -y, x }; }

        [[nodiscard]] constexpr float length_squared() const noexcept { return dot(*this); }
        [[nodiscard]] float length() const noexcept { return std::sqrt(length_squared()); }
        [[nodiscard]] vector2 normalized() const noexcept { return *this / length(); }
        [[nodiscard]] float angle() const noexcept { return std::atan2(y, x); }

        [[nodiscard]] constexpr bool operator==(const vector2&) const noexcept = default;
    };

	class vector3
	{
	public:
		float x, y, z;

		constexpr vector3() noexcept : x(0.0), y(0.0), z(0.0) {};
		constexpr vector3(float x, float y, float z) noexcept : x(x), y(y), z(z) {};

		[[nodiscard]] constexpr vector3 operator+(const vector3& v) const noexcept { return { x + v.x, y + v.y, z + v.z }; }
		[[nodiscard]] constexpr vector3 operator-(const vector3& v) const noexcept { return { x - v.x, y - v.y, z - v.z }; }
		[[nodiscard]] constexpr vector3 operator*(const vector3& v) const noexcept { return { x * v.x, y * v.y, z * v.z }; }
		[[nodiscard]] constexpr vector3 operator/(const vector3& v) const noexcept { return { x / v.x, y / v.y, z / v.z }; }

		[[nodiscard]] constexpr vector3 operator*(float s) const noexcept { return { x * s, y * s, z * s }; }
		[[nodiscard]] constexpr vector3 operator/(float s) const noexcept { return { x / s, y / s, z / s }; }

		constexpr vector3& operator+=(const vector3& v) noexcept { x += v.x; y += v.y; z += v.z; return *this; }
		constexpr vector3& operator-=(const vector3& v) noexcept { x -= v.x; y -= v.y; z -= v.z; return *this; }
		constexpr vector3& operator*=(float s)          noexcept { x *= s;   y *= s;   z *= s;   return *this; }

		[[nodiscard]] constexpr vector3 operator-() const noexcept { return { -x, -y, -z }; }

		[[nodiscard]] constexpr float dot(const vector3& v) const noexcept { return x * v.x + y * v.y + z * v.z; }
		[[nodiscard]] constexpr vector3 cross(const vector3& v) const noexcept { return { y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x }; }

        [[nodiscard]] float length() const noexcept { return std::sqrt(dot(*this)); }
		[[nodiscard]] vector3 normalized() const noexcept { return *this / length(); }

		[[nodiscard]] constexpr bool operator==(const vector3&) const noexcept = default;
	};
} // namespace math
#endif