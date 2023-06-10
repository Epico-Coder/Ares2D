#pragma once

#include <iostream>

namespace Ares2D
{
	struct Color4
	{
	public:
		Color4();
		Color4(float r, float g, float b, float a);
		Color4(const Color4& other);

		float r;
		float g;
		float b;
		float a;

		void Display() const;

		Color4& operator=(const Color4& other);

		Color4 operator+(const Color4& other) const;
		Color4 operator-(const Color4& other) const;
		Color4 operator*(float scalar) const;
		Color4 operator/(float scalar) const;

		bool operator==(const Color4& other) const;
		bool operator!=(const Color4& other) const;

		float& operator[](size_t index);
		const float& operator[](size_t index) const;
	};

	struct Color3
	{
		float r;
		float g;
		float b;
	};

	class Color
	{
	public:
	private:
	};

};

