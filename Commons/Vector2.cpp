//
// Created by hw21a105 on 2023/12/20.
//

#include "Vector2.hpp"
#include <cmath>

Vector2::Vector2() : x(0), y(0) {}

Vector2::Vector2(float x, float y) : x(x), y(y) {}

Vector2::Vector2(int x, int y) : x((float) x), y((float) y) {}

Vector2 operator+(const Vector2 &a, const Vector2 &b) {
    return Vector2(a.x + b.x, a.y + b.y);
}

Vector2 operator-(const Vector2 &a, const Vector2 &b) {
    return Vector2(a.x - b.x, a.y - b.y);
}

Vector2 operator*(const Vector2 &a, const Vector2 &b) {
    return Vector2(a.x * b.x, a.y * b.y);
}

Vector2 operator*(const Vector2 &vec, float scalar) {
    return Vector2(vec.x * scalar, vec.y * scalar);
}

Vector2 &Vector2::operator+=(const Vector2 &vec) {
    x += vec.x;
    y += vec.y;
    return *this;
}

Vector2 &Vector2::operator-=(const Vector2 &vec) {
    x -= vec.x;
    y -= vec.y;
    return *this;
}

Vector2 &Vector2::operator*=(float scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
}

float Vector2::Length() const {
    return sqrtf(x * x + y * y);
}

float Vector2::LengthSq() const {
    return x * x + y * y;
}

float Vector2::Max() const {
    return fmax(x, y);
}

Vector2 Vector2::Normalize() const {
    float len = Length();
    if (len > 0.0f) {
        return *this * (1.0f / len);
    }
    return *this;
}

const Vector2 Vector2::Zero = Vector2(0, 0);
const Vector2 Vector2::One = Vector2(1, 1);