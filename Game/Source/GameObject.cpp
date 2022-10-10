#include "Framework.h"
#include "GameObject.h"

GameObject::GameObject(const char type[]) // Bring in type
{
	if (type == "Triangle")
	{
		fw::VertexFormat points[] = {
			{-1, -1, 255, 0, 0, 255},
			{ 0, 1, 0, 255, 0, 255},
			{1, -1, 0, 0, 255, 255}
		};

		m_Mesh = new fw::Mesh(points, 3, GL_TRIANGLES);
	}

	m_ShaderProgram = new fw::ShaderProgram("Data/Shaders/Basic.vert", "Data/Shaders/Basic.frag");

	
}

GameObject::~GameObject()
{
	delete m_Mesh;

	delete m_ShaderProgram;
}

void GameObject::Update()
{

}

void GameObject::Draw(fw::ShaderProgram* shaderProgram, fw::Vec2 position, float timeElapsed, fw::Vec2 resolution)
{
	//m_ShaderProgram = shaderProgram;
	m_Mesh->Draw(m_ShaderProgram, m_Scale, m_Angle, position, timeElapsed, resolution);
}
