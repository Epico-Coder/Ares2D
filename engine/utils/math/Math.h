#pragma once

#include "dependancies/glm/glm.hpp"
#include "dependancies/glm/gtc/matrix_transform.hpp"

#include <cmath>
#include <iostream>

namespace Ares2D
{
	struct Float4
	{
	public:
		Float4();
		Float4(float x, float y, float w, float h);
		Float4(const Float4& other);

		float x;
		float y;
		float w;
		float h;

		float Length() const;
		void Display() const;

		Float4& operator=(const Float4& other);

		Float4 operator+(const Float4& other) const;
		Float4 operator-(const Float4& other) const;
		Float4 operator*(float scalar) const;
		Float4 operator/(float scalar) const;

		bool operator==(const Float4& other) const;
		bool operator!=(const Float4& other) const;

		float& operator[](size_t index);
		const float& operator[](size_t index) const;
	};

	struct Int4
	{
	public:
		Int4();
		Int4(int x, int y, int w, int h);
		Int4(const Int4& other);

		int x;
		int y;
		int w;
		int h;

		double Length() const;
		void Display() const;

		Int4& operator=(const Int4& other);

		Int4 operator+(const Int4& other) const;
		Int4 operator-(const Int4& other) const;
		Int4 operator*(int scalar) const;
		Int4 operator/(int scalar) const;

		bool operator==(const Int4& other) const;
		bool operator!=(const Int4& other) const;

		int& operator[](size_t index);
		const int& operator[](size_t index) const;

		
	};

	struct Float3
	{
	public:
		Float3();
		Float3(float a, float b, float c);
		Float3(const Float3& other);

		float a;
		float b;
		float c;

		float Length() const;
		void Display() const;

		Float3& operator=(const Float3& other);

		Float3 operator+(const Float3& other) const;
		Float3 operator-(const Float3& other) const;
		Float3 operator*(float scalar) const;
		Float3 operator/(float scalar) const;

		bool operator==(const Float3& other) const;
		bool operator!=(const Float3& other) const;

		float& operator[](size_t index);
		const float& operator[](size_t index) const;
	};

	struct Int3
	{
	public:
		Int3();
		Int3(int a, int b, int c);
		Int3(const Int3& other);

		int a;
		int b;
		int c;

		double Length() const;
		void Display() const;

		Int3& operator=(const Int3& other);

		Int3 operator+(const Int3& other) const;
		Int3 operator-(const Int3& other) const;
		Int3 operator*(int scalar) const;
		Int3 operator/(int scalar) const;

		bool operator==(const Int3& other) const;
		bool operator!=(const Int3& other) const;

		int& operator[](size_t index);
		const int& operator[](size_t index) const;
	};

	struct Float2
	{
	public:
		Float2();
		Float2(float x, float y);
		Float2(const Float2& other);

		float x;
		float y;

		float Length() const;
		void Display() const;

		Float2& operator=(const Float2& other);

		Float2 operator+(const Float2& other) const;
		Float2& operator+=(const Float2& other);

		Float2 operator-(const Float2& other) const;
		Float2& operator-=(const Float2& other);

		Float2 operator*(const float scalar) const;
		Float2& operator*=(const float scalar);
		Float2 operator*(const Float2& other) const;
		Float2& operator*=(const Float2& other);

		Float2 operator/(const float scalar) const;
		Float2& operator/=(const float scalar);
		Float2 operator/(const Float2& other) const;
		Float2& operator/=(const Float2& other);

		bool operator==(const Float2& other) const;
		bool operator!=(const Float2& other) const;

		float& operator[](size_t index);
		const float& operator[](size_t index) const;
	};

	struct Int2
	{
	public:
		Int2();
		Int2(int x, int y);
		Int2(const Int2& other);

		int x;
		int y;

		double Length() const;
		void Display() const;

		Int2& operator=(const Int2& other);

		Int2 operator+(const Int2& other) const;
		Int2 operator-(const Int2& other) const;
		Int2 operator*(int scalar) const;
		Int2 operator/(int scalar) const;

		bool operator==(const Int2& other) const;
		bool operator!=(const Int2& other) const;

		int& operator[](size_t index);
		const int& operator[](size_t index) const;

	};

	class Math
	{
	public:
	private:
	};
}