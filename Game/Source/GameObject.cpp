#include "Framework.h"
#include "GameObject.h"

GameObject::GameObject(fw::Mesh* pMesh, fw::ShaderProgram* shaderProgram, float timeElapsed, fw::Vec2 resolution)
{
	
	m_Mesh = pMesh;
	m_ShaderProgram = shaderProgram;
	m_TimeElapsed = timeElapsed;
	m_Resolution = resolution;

	
}

GameObject::~GameObject()
{
	
}

void GameObject::Update()
{

}

void GameObject::Draw(float color[])
{
	m_Mesh->Draw(m_ShaderProgram, m_Scale, m_Angle, m_Position, m_TimeElapsed, m_Resolution, color);
}

void GameObject::SetResolution(fw::Vec2 resolution)
{
	m_Resolution = resolution;
}

void GameObject::SetTimeElapsed(float timeElapsed)
{
	m_TimeElapsed = timeElapsed;
}

void GameObject::SetPosition(fw::Vec2 position)
{
	m_Position = position;
}

void GameObject::SetScale(fw::Vec2 scale)
{
	m_Scale = scale;
}

void GameObject::SetAngle(float angle)
{
	m_Angle = angle;
}

fw::Vec2 GameObject::GetPosition()
{
	return m_Position;
}

fw::Vec2 GameObject::GetScale()
{
	return m_Scale;
}

float GameObject::GetAngle()
{
	return m_Angle;
}

fw::Mesh* GameObject::GetMesh()
{
	return m_Mesh;
}
