#include "CoreHeaders.h"
#include "Vec2.h"

namespace fw {
    Vec2::Vec2()
    {

    }

    Vec2::Vec2(float x, float y) :
        x(x),
        y(y)
    {

    }

    float Vec2::Length() const
    {
        return sqrtf(x * x + y * y);
    }

    float Vec2::DistanceTo(const Vec2& o) const
    {
        return (*this - o).Length();;
    }

    Vec2 Vec2::GetNormalized() const
    {
        return (*this) / Length();
    }

    Vec2& Vec2::Normalize()
    {
        (*this) /= Length();
        return (*this);
    }

    void Vec2::Test()
    {
        Vec2 a;
        assert(a.x == 0 && a.y == 0);

        Vec2 b(1, 3);
        assert(b.x == 1 && b.y == 3);

        Vec2 c(20, 30);
        c += b;
        assert(c.x == 21 && c.y == 33);


        
    }
}