#pragma once
#include "DataTypes.h"

class Camera
{
public:
	Camera(fw::FWCore& rFramework);
	~Camera();

	Vec2 GetPosition() { return m_Position; }
	Vec2 GetProjectionScale() { return m_ProjectionScale; }
	Vec2 GetWindowSize() { return m_WindowSize; }

	void SetPosition(Vec2 position) { m_Position = position; }
	void SetProjectionScale(Vec2 projectionScale) { m_ProjectionScale = projectionScale; }
	void SetWindowSize(Vec2 windowSize) { m_WindowSize = windowSize; }

protected:
	Vec2 m_Position = { 0, 0 };
	Vec2 m_ProjectionScale = { 1, 1 };
	Vec2 m_WindowSize = { 1, 1 };


};