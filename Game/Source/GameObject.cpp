#include "Framework.h"
#include "GameObject.h"

GameObject::GameObject(fw::Mesh* pMesh, fw::ShaderProgram* shaderProgram, fw::Vec2 position, float timeElapsed, fw::Vec2 resolution, float color[], int size) // In everything that was going into
{
	
	m_Mesh = pMesh;
	m_ShaderProgram = shaderProgram;
	m_Position.x = position.x;
	m_Position.y = position.y;
	m_TimeElapsed = timeElapsed;
	m_Resolution = resolution;
	m_Color[m_ColorArraySize] = color[size]; //TODO: Fix how you bring in color
	
	
}

GameObject::~GameObject()
{
	
}

void GameObject::Update()
{
	//m_Mesh->AddVert(fw::VertexFormat())
}

void GameObject::Draw()
{
	m_Mesh->Draw(m_ShaderProgram, m_Scale, m_Angle, m_Position, m_TimeElapsed, m_Resolution, m_Color, m_ColorArraySize);
}
