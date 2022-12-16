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

	class iVec2
	{
	public:
		iVec2();
		iVec2(int x, int y);
		
		iVec2& operator+=(const iVec2& o) { x += o.x; y += o.y; return *this; }
		iVec2& operator-=(const iVec2& o) { x -= o.x; y -= o.y; return *this; }
		iVec2& operator*=(const iVec2& o) { x *= o.x; y *= o.y; return *this; }
		iVec2& operator/=(const iVec2& o) { x /= o.x; y /= o.y; return *this; }
		
		iVec2& operator*=(const int o) { x *= o; y *= o; return *this; }
		iVec2& operator/=(const int o) { x /= o; y /= o; return *this; }
		
		bool operator==(const iVec2& o) const { return (x == o.x && y == o.y);  }

		iVec2 operator+(const iVec2& o) const { return iVec2(x + o.x, y + o.y); }
		iVec2 operator-(const iVec2& o) const { return iVec2(x - o.x, y - o.y); }
		iVec2 operator*(const iVec2& o) const { return iVec2(x * o.x, y * o.y); }
		iVec2 operator/(const iVec2& o) const { return iVec2(x / o.x, y / o.y); }
													  
		iVec2 operator*(const int o) const { return iVec2(x * o, y * o); }
		iVec2 operator/(const int o) const { return iVec2(x / o, y / o); }

		float Length() const;

		float DistanceTo(const iVec2& o) const;

		void Set(int nx, int ny) { x = nx; y = ny; }


		static void Test(); //Unit Testing

		int x = 0;
		int y = 0;
	};

}