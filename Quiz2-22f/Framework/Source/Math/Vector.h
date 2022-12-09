#pragma once

namespace fw {

class vec2
{
public:
    vec2() {}
    vec2(float nx, float ny) { x = nx; y = ny; }

    void Set(float nx, float ny) { x = nx; y = ny; }

    vec2& operator+=(const vec2& o) { x += o.x; y += o.y; return *this; }
    vec2& operator-=(const vec2& o) { x -= o.x; y -= o.y; return *this; }
    vec2& operator*=(const vec2& o) { x *= o.x; y *= o.y; return *this; }
    vec2& operator/=(const vec2& o) { x /= o.x; y /= o.y; return *this; }

    vec2& operator*=(float o) { x *= o; y *= o; return *this; }
    vec2& operator/=(float o) { x /= o; y /= o; return *this; }

    vec2 operator+(const vec2& o) const { return vec2(x+o.x, y+o.y); }
    vec2 operator-(const vec2& o) const { return vec2(x-o.x, y-o.y); }
    vec2 operator*(const vec2& o) const { return vec2(x*o.x, y*o.y); }
    vec2 operator/(const vec2& o) const { return vec2(x/o.x, y/o.y); }

    vec2 operator*(float o) const { return vec2(x*o, y*o); }
    vec2 operator/(float o) const { return vec2(x/o, y/o); }

    float Length() const
    {
        return sqrtf( x*x + y*y );
    }

    float DistanceTo(const vec2& o) const
    {
        return (*this - o).Length();
    }

    vec2 GetNormalized() const
    {
        return (*this) / Length();
    }

    vec2& Normalize()
    {
        (*this) /= Length();
        return *this;
    }

    static void Test();

public:
    float x = 0;
    float y = 0;
};

class ivec2
{
public:
    ivec2() {}
    ivec2(int nx, int ny) { x = nx; y = ny; }

    void Set(int nx, int ny) { x = nx; y = ny; }

    ivec2& operator+=(const ivec2& o) { x += o.x; y += o.y; return *this; }
    ivec2& operator-=(const ivec2& o) { x -= o.x; y -= o.y; return *this; }
    ivec2& operator*=(const ivec2& o) { x *= o.x; y *= o.y; return *this; }
    ivec2& operator/=(const ivec2& o) { x /= o.x; y /= o.y; return *this; }

    ivec2& operator*=(int o) { x *= o; y *= o; return *this; }
    ivec2& operator/=(int o) { x /= o; y /= o; return *this; }

    ivec2 operator+(const ivec2& o) const { return ivec2(x + o.x, y + o.y); }
    ivec2 operator-(const ivec2& o) const { return ivec2(x - o.x, y - o.y); }
    ivec2 operator*(const ivec2& o) const { return ivec2(x * o.x, y * o.y); }
    ivec2 operator/(const ivec2& o) const { return ivec2(x / o.x, y / o.y); }

    ivec2 operator*(int o) const { return ivec2(x * o, y * o); }
    ivec2 operator/(int o) const { return ivec2(x / o, y / o); }
    
public:
    int x = 0;
    int y = 0;
};

} // namespace fw
