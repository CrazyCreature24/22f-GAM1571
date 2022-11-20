#pragma once
#include "Math/Vec2.h"

namespace fw
{

	class Camera
	{
	public:
		Camera(FWCore& rFramework);
		~Camera();

		void UpdateAspect();

		Vec2 GetPosition() { return m_Position; }
		Vec2 GetProjectionScale() { return m_ProjectionScale; }
		Vec2 GetWindowSize() { return m_WindowSize; }

		void SetPosition(Vec2 position) { m_Position = position; }
		void SetProjectionScale(Vec2 projectionScale) { m_SetProjectionScale = projectionScale; }
		void SetWindowSize(Vec2 windowSize) { m_WindowSize = windowSize; }

	protected:
		Vec2 m_Position = { 0, 0 };
		Vec2 m_ProjectionScale = { 0.1f, 0.1f };
		Vec2 m_SetProjectionScale = { 0.1f, 0.1f };
		Vec2 m_WindowSize = { 1, 1 };
		float m_Aspect = 0.0f;
		FWCore& m_rFramework;


	};
}