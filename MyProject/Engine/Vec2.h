#ifndef __VEC2_H__
#define __VEC2_H__

class Vec2 {
public:
    Vec2();
    Vec2(const Vec2& other);
    Vec2(float x, float y);

    const Vec2 operator+(const Vec2& other) const;
    const Vec2 operator-(const Vec2& other) const;
    const Vec2 operator*(float f) const;
    const Vec2 operator/(float f) const;
    const Vec2 operator-() const;

    Vec2& operator+=(const Vec2& other);
    Vec2& operator-=(const Vec2& other);
    Vec2& operator*=(float f);
    Vec2& operator/=(float f);

    float x = 0;
    float y = 0;

    static Vec2 ZERO;
};

class Rect {
public:
    Vec2 leftBottom;
    Vec2 rightTop;
};

#endif
