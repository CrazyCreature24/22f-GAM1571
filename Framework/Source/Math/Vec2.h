#pragma once

namespace fw {

	class Vec2
	{
	public:
		Vec2();
		Vec2(float x, float y);

		Vec2& operator+=(const Vec2& o) { x += o.x; y += o.y; return *this; }
		Vec2& operator-=(const Vec2& o) { x -= o.x; y -= o.y; return *this; }
		Vec2& operator*=(const Vec2& o) { x *= o.x; y *= o.y; return *this; }
		Vec2& operator/=(const Vec2& o) { x /= o.x; y /= o.y; return *this; }

		Vec2& operator*=(const float o) { x *= o; y *= o; return *this; }
		Vec2& operator/=(const float o) { x /= o; y /= o; return *this; }

		Vec2 operator+(const Vec2& o) const { return Vec2( x + o.x, y + o.y ); }
		Vec2 operator-(const Vec2& o) const { return Vec2(x - o.x, y - o.y); }
		Vec2 operator*(const Vec2& o) const { return Vec2(x * o.x, y * o.y); }
		Vec2 operator/(const Vec2& o) const { return Vec2(x / o.x, y / o.y); }

		Vec2 operator*(const float o) const { return Vec2(x * o, y * o); }
		Vec2 operator/(const float o) const { return Vec2(x / o, y / o); }

		float Length() const;

		float DistanceTo(const Vec2& o) const;

		Vec2 GetNormalized() const;

		Vec2& Normalize();


		void Set(float nx, float ny) { x = nx; y = ny; }


		static void Test(); //Unit Testing

		


		float x = 0;
		float y = 0;
	};

}