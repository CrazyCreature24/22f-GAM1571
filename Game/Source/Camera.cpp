#include "Framework.h"
#include "Camera.h"

Camera::Camera(fw::FWCore& rFramework)
{
	m_WindowSize = Vec2(static_cast<float>(rFramework.GetWindowWidth()), static_cast<float>(rFramework.GetWindowHeight()));
}

Camera::~Camera()
{

}
