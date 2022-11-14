#pragma once
#include "DataTypes.h"

class Camera
{
public:
	Camera();
	~Camera();

protected:
	Vec2 m_Position = { 0, 0 };
	Vec2 m_ProjectionScale = { 1, 1 };
	Vec2 m_WindowSize = { 1, 1 };


};