#include "CoreHeaders.h"
#include "Vector.h"

namespace fw {

void vec2::Test()
{
    vec2 a;
    assert( a.x == 0 && a.y == 0 );

    vec2 b( 1, 3 );
    assert( b.x == 1 && b.y == 3 );

    vec2 c( 20, 30 );
    c += b;
    assert( c.x == 21 && c.y == 33 );

    const vec2 e( 3, 4 );
    float len = e.Length();
    assert( len == 5 );
}

}
