#include "CoreHeaders.h"
#include "FWCore.h"
#include "Camera.h"

namespace fw
{
	Camera::Camera(FWCore& rFramework) :
		m_rFramework(rFramework)
	{
		m_WindowSize = Vec2(static_cast<float>(rFramework.GetWindowWidth()), static_cast<float>(rFramework.GetWindowHeight()));
		m_Aspect = m_WindowSize.y / m_WindowSize.x;
		m_ProjectionScale.x *= m_Aspect;
	}

	Camera::~Camera()
	{

	}

	void Camera::UpdateAspect()
	{
		m_ProjectionScale = { 0.1f, 0.1f };
		m_WindowSize = Vec2(static_cast<float>(m_rFramework.GetWindowWidth()), static_cast<float>(m_rFramework.GetWindowHeight()));
		m_Aspect = m_WindowSize.y / m_WindowSize.x;
		m_ProjectionScale.x *= m_Aspect;
	}
}