#include "Math.h"

namespace Ares2D
{
    /*-------------------------- Float4 --------------------------*/

    Float4::Float4() : x(0.0f), y(0.0f), w(0.0f), h(0.0f)
    {
    }

    Float4::Float4(float x, float y, float w, float h) : x(x), y(y), w(w), h(h)
    {
    }

    Float4::Float4(const Float4& other) : x(other.x), y(other.y), w(other.w), h(other.h)
    {
    }

    Float4& Float4::operator=(const Float4& other)
    {
        if (this != &other)
        {
            x = other.x;
            y = other.y;
            w = other.w;
            h = other.h;
        }
        return *this;
    }

    Float4 Float4::operator+(const Float4& other) const
    {
        return Float4(x + other.x, y + other.y, w + other.w, h + other.h);
    }

    Float4 Float4::operator-(const Float4& other) const
    {
        return Float4(x - other.x, y - other.y, w - other.w, h - other.h);
    }

    Float4 Float4::operator*(float scalar) const
    {
        return Float4(x * scalar, y * scalar, w * scalar, h * scalar);
    }

    Float4 Float4::operator/(float scalar) const
    {
        return Float4(x / scalar, y / scalar, w / scalar, h / scalar);
    }

    bool Float4::operator==(const Float4& other) const
    {
        return (x == other.x) && (y == other.y) && (w == other.w) && (h == other.h);
    }

    bool Float4::operator!=(const Float4& other) const
    {
        return !(*this == other);
    }

    float& Float4::operator[](size_t index)
    {
        if (index == 0)
            return x;
        else if (index == 1)
            return y;
        else if (index == 2)
            return w;
        else if (index == 3)
            return h;
        else
            throw std::out_of_range("Index out of range for Float4");
    }

    const float& Float4::operator[](size_t index) const
    {
        return const_cast<Float4*>(this)->operator[](index);
    }

    float Float4::Length() const
    {
        return std::sqrt(x * x + y * y);
    }

    void Float4::Display() const
    {
        std::cout << "(" << x << ", " << y << ", " << w << ", " << h << ")" << std::endl;
    }

    /*-------------------------- Int4 Functions --------------------------*/

    Int4::Int4() : x(0), y(0), w(0), h(0)
    {
    }

    Int4::Int4(int x, int y, int w, int h) : x(x), y(y), w(w), h(h)
    {
    }

    Int4::Int4(const Int4& other) : x(other.x), y(other.y), w(other.w), h(other.h)
    {
    }

    Int4& Int4::operator=(const Int4& other)
    {
        if (this != &other)
        {
            x = other.x;
            y = other.y;
            w = other.w;
            h = other.h;
        }
        return *this;
    }

    Int4 Int4::operator+(const Int4& other) const
    {
        return Int4(x + other.x, y + other.y, w + other.w, h + other.h);
    }

    Int4 Int4::operator-(const Int4& other) const
    {
        return Int4(x - other.x, y - other.y, w - other.w, h - other.h);
    }

    Int4 Int4::operator*(int scalar) const
    {
        return Int4(x * scalar, y * scalar, w * scalar, h * scalar);
    }

    Int4 Int4::operator/(int scalar) const
    {
        if (scalar == 0)
            throw std::runtime_error("Divide by zero exception");
        return Int4(x / scalar, y / scalar, w / scalar, h / scalar);
    }

    bool Int4::operator==(const Int4& other) const
    {
        return (x == other.x) && (y == other.y) && (w == other.w) && (h == other.h);
    }

    bool Int4::operator!=(const Int4& other) const
    {
        return !(*this == other);
    }

    int& Int4::operator[](size_t index)
    {
        if (index == 0)
            return x;
        else if (index == 1)
            return y;
        else if (index == 2)
            return w;
        else if (index == 3)
            return h;
        else
            throw std::out_of_range("Index out of range for Int4");
    }

    const int& Int4::operator[](size_t index) const
    {
        return const_cast<Int4*>(this)->operator[](index);
    }

    double Int4::Length() const
    {
        return std::sqrt(x * x + y * y + w * w + h * h);
    }

    void Int4::Display() const
    {
        std::cout << "(" << x << ", " << y << ", " << w << ", " << h << ")" << std::endl;
    }

    /*-------------------------- Float3 Functions --------------------------*/

    Float3::Float3() : a(0.0f), b(0.0f), c(0.0f)
    {
    }

    Float3::Float3(float a, float b, float c) : a(a), b(b), c(c)
    {
    }

    Float3::Float3(const Float3& other) : a(other.a), b(other.b), c(other.c)
    {
    }

    Float3& Float3::operator=(const Float3& other)
    {
        if (this != &other)
        {
            a = other.a;
            b = other.b;
            c = other.c;
        }
        return *this;
    }

    Float3 Float3::operator+(const Float3& other) const
    {
        return Float3(a + other.a, b + other.b, c + other.c);
    }

    Float3 Float3::operator-(const Float3& other) const
    {
        return Float3(a - other.a, b - other.b, c - other.c);
    }

    Float3 Float3::operator*(float scalar) const
    {
        return Float3(a * scalar, b * scalar, c * scalar);
    }

    Float3 Float3::operator/(float scalar) const
    {
        if (scalar == 0.0f)
            throw std::runtime_error("Divide by zero exception");
        return Float3(a / scalar, b / scalar, c / scalar);
    }

    bool Float3::operator==(const Float3& other) const
    {
        return (a == other.a) && (b == other.b) && (c == other.c);
    }

    bool Float3::operator!=(const Float3& other) const
    {
        return !(*this == other);
    }

    float& Float3::operator[](size_t index)
    {
        if (index == 0)
            return a;
        else if (index == 1)
            return b;
        else if (index == 2)
            return c;
        else
            throw std::out_of_range("Index out of range for Float3");
    }

    const float& Float3::operator[](size_t index) const
    {
        return const_cast<Float3*>(this)->operator[](index);
    }

    float Float3::Length() const
    {
        return std::sqrt(a * a + b * b + c * c);
    }

    void Float3::Display() const
    {
        std::cout << "(" << a << ", " << b << ", " << c << ")" << std::endl;
    }

    /*-------------------------- Int3 Functions --------------------------*/

    Int3::Int3() : a(0), b(0), c(0)
    {
    }

    Int3::Int3(int a, int b, int c) : a(a), b(b), c(c)
    {
    }

    Int3::Int3(const Int3& other) : a(other.a), b(other.b), c(other.c)
    {
    }

    Int3& Int3::operator=(const Int3& other)
    {
        if (this != &other)
        {
            a = other.a;
            b = other.b;
            c = other.c;
        }
        return *this;
    }

    Int3 Int3::operator+(const Int3& other) const
    {
        return Int3(a + other.a, b + other.b, c + other.c);
    }

    Int3 Int3::operator-(const Int3& other) const
    {
        return Int3(a - other.a, b - other.b, c - other.c);
    }

    Int3 Int3::operator*(int scalar) const
    {
        return Int3(a * scalar, b * scalar, c * scalar);
    }

    Int3 Int3::operator/(int scalar) const
    {
        if (scalar == 0)
            throw std::runtime_error("Divide by zero exception");
        return Int3(a / scalar, b / scalar, c / scalar);
    }

    bool Int3::operator==(const Int3& other) const
    {
        return (a == other.a) && (b == other.b) && (c == other.c);
    }

    bool Int3::operator!=(const Int3& other) const
    {
        return !(*this == other);
    }

    int& Int3::operator[](size_t index)
    {
        if (index == 0)
            return a;
        else if (index == 1)
            return b;
        else if (index == 2)
            return c;
        else
            throw std::out_of_range("Index out of range for Int3");
    }

    const int& Int3::operator[](size_t index) const
    {
        return const_cast<Int3*>(this)->operator[](index);
    }

    double Int3::Length() const
    {
        return std::sqrt(a * a + b * b + c * c);
    }

    void Int3::Display() const
    {
        std::cout << "(" << a << ", " << b << ", " << c << ")" << std::endl;
    }

    /*-------------------------- Float2 Functions --------------------------*/

    Float2::Float2() : x(0.0f), y(0.0f)
    {
    }

    Float2::Float2(float arr[2]) : x(arr[0]), y(arr[1])
    {
    }

    Float2::Float2(float x, float y) : x(x), y(y)
    {
    }

    Float2::Float2(const Float2& other) : x(other.x), y(other.y)
    {
    }

    Float2& Float2::operator=(const Float2& other)
    {
        if (this != &other)
        {
            x = other.x;
            y = other.y;
        }
        return *this;
    }

    Float2 Float2::operator+(const Float2& other) const
    {
        return Float2(x + other.x, y + other.y);
    }

    Float2& Float2::operator+=(const Float2& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    Float2 Float2::operator-(const Float2& other) const
    {
        return Float2(x - other.x, y - other.y);
    }

    Float2& Float2::operator-=(const Float2& other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Float2 Float2::operator*(float scalar) const
    {
        return Float2(x * scalar, y * scalar);
    }

    Float2& Float2::operator*=(float scalar)
    {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    Float2 Float2::operator*(const Float2& other) const
    {
        return Float2(x * other.x, y * other.y);
    }

    Float2& Float2::operator*=(const Float2& other)
    {
        x *= other.x;
        y *= other.y;
        return *this;
    }

    Float2 Float2::operator/(float scalar) const
    {
        if (scalar == 0.0f)
            throw std::runtime_error("Divide by zero exception");
        return Float2(x / scalar, y / scalar);
    }

    Float2& Float2::operator/=(float scalar)
    {
        if (scalar == 0.0f)
            throw std::runtime_error("Divide by zero exception");
        x /= scalar;
        y /= scalar;
        return *this;
    }

    Float2 Float2::operator/(const Float2& other) const
    {
        if (other.x == 0.0f || other.y == 0.0f)
            throw std::runtime_error("Divide by zero exception");
        return Float2(x / other.x, y / other.y);
    }

    Float2& Float2::operator/=(const Float2& other)
    {
        if (other.x == 0.0f || other.y == 0.0f)
            throw std::runtime_error("Divide by zero exception");
        x /= other.x;
        y /= other.y;
        return *this;
    }

    bool Float2::operator==(const Float2& other) const
    {
        return (x == other.x) && (y == other.y);
    }

    bool Float2::operator!=(const Float2& other) const
    {
        return !(*this == other);
    }

    float& Float2::operator[](size_t index)
    {
        if (index == 0)
            return x;
        else if (index == 1)
            return y;
        else
            throw std::out_of_range("Index out of range for Float2");
    }

    const float& Float2::operator[](size_t index) const
    {
        return const_cast<Float2*>(this)->operator[](index);
    }

    float Float2::Length() const
    {
        return std::sqrt(x * x + y * y);
    }

    void Float2::Display() const
    {
        std::cout << "(" << x << ", " << y << ")" << std::endl;
    }

    /*-------------------------- Int2 Functions --------------------------*/

    Int2::Int2() : x(0), y(0)
    {
    }

    Int2::Int2(int x, int y) : x(x), y(y)
    {
    }

    Int2::Int2(const Int2& other) : x(other.x), y(other.y)
    {
    }

    Int2& Int2::operator=(const Int2& other)
    {
        if (this != &other)
        {
            x = other.x;
            y = other.y;
        }
        return *this;
    }

    Int2 Int2::operator+(const Int2& other) const
    {
        return Int2(x + other.x, y + other.y);
    }

    Int2 Int2::operator-(const Int2& other) const
    {
        return Int2(x - other.x, y - other.y);
    }

    Int2 Int2::operator*(int scalar) const
    {
        return Int2(x * scalar, y * scalar);
    }

    Int2 Int2::operator/(int scalar) const
    {
        if (scalar == 0)
            throw std::runtime_error("Divide by zero exception");
        return Int2(x / scalar, y / scalar);
    }

    bool Int2::operator==(const Int2& other) const
    {
        return (x == other.x) && (y == other.y);
    }

    bool Int2::operator!=(const Int2& other) const
    {
        return !(*this == other);
    }

    int& Int2::operator[](size_t index)
    {
        if (index == 0)
            return x;
        else if (index == 1)
            return y;
        else
            throw std::out_of_range("Index out of range for Int2");
    }

    const int& Int2::operator[](size_t index) const
    {
        return const_cast<Int2*>(this)->operator[](index);
    }

    double Int2::Length() const
    {
        return std::sqrt(x * x + y * y);
    }

    void Int2::Display() const
    {
        std::cout << "(" << x << ", " << y << ")" << std::endl;
    }
};