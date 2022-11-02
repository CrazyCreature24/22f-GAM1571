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


//TODO: Find out how to deal with TimeElapsed and Resolution better