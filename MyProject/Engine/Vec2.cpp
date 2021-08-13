#include "Vec2.h"

Vec2 Vec2::ZERO{0, 0};

Vec2::Vec2() {
    x = 0;
    y = 0;
}

Vec2::Vec2(const Vec2 &other) {
    x = other.x;
    y = other.y;
}

Vec2::Vec2(float x, float y) {
    this->x = x;
    this->y = y;
}

const Vec2 Vec2::operator+(const Vec2 &other) const {
    return Vec2{x + other.x, y + other.y};
}

const Vec2 Vec2::operator-(const Vec2 &other) const {
    return Vec2{x - other.x, y - other.y};
}

const Vec2 Vec2::operator*(float f) const { return Vec2{x * f, y * f}; }

const Vec2 Vec2::operator/(float f) const { return Vec2{x / f, y / f}; }

const Vec2 Vec2::operator-() const { return Vec2{-x, -y}; }

Vec2 &Vec2::operator+=(const Vec2 &other) {
    x += other.x;
    y += other.y;
    return *this;
}

Vec2 &Vec2::operator-=(const Vec2 &other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

Vec2 &Vec2::operator*=(float f) {
    x *= f;
    y *= f;
    return *this;
}

Vec2 &Vec2::operator/=(float f) {
    x /= f;
    y /= f;
    return *this;
}