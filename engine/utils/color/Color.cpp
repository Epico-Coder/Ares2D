#include "Color.h"

namespace Ares2D
{
    /*-------------------------- Color4 --------------------------*/

    Color4::Color4() : r(0.0f), g(0.0f), b(0.0f), a(0.0f)
    {
    }

    Color4::Color4(float r, float g, float b, float a) : r(r), g(g), b(b), a(a)
    {
    }

    Color4::Color4(const Color4& other) : r(other.r), g(other.g), b(other.b), a(other.a)
    {
    }

    Color4& Color4::operator=(const Color4& other)
    {
        if (this != &other)
        {
            r = other.r;
            g = other.g;
            b = other.b;
            a = other.a;
        }
        return *this;
    }

    Color4 Color4::operator+(const Color4& other) const
    {
        return Color4(r + other.r, g + other.g, b + other.b, a + other.a);
    }

    Color4 Color4::operator-(const Color4& other) const
    {
        return Color4(r - other.r, g - other.g, b - other.b, a - other.a);
    }

    Color4 Color4::operator*(float scalar) const
    {
        return Color4(r * scalar, g * scalar, b * scalar, a * scalar);
    }

    Color4 Color4::operator/(float scalar) const
    {
        return Color4(r / scalar, g / scalar, b / scalar, a / scalar);
    }

    bool Color4::operator==(const Color4& other) const
    {
        return (r == other.r) && (g == other.g) && (b == other.b) && (a == other.a);
    }

    bool Color4::operator!=(const Color4& other) const
    {
        return !(*this == other);
    }

    float& Color4::operator[](size_t index)
    {
        if (index == 0)
            return r;
        else if (index == 1)
            return g;
        else if (index == 2)
            return b;
        else if (index == 3)
            return a;
        else
            throw std::out_of_range("Index out of range for Color4");
    }

    const float& Color4::operator[](size_t index) const
    {
        return const_cast<Color4*>(this)->operator[](index);
    }

    void Color4::Display() const
    {
        std::cout << "(" << r << ", " << g << ", " << b << ", " << a << ")" << std::endl;
    }
};