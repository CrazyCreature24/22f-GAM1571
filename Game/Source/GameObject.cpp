#include "Framework.h"
#include "GameObject.h"

GameObject::GameObject(int num) // Bring in type
{
	if (num == 1)
	{
		fw::VertexFormat points[] = {
			{-1, -1, 255, 0, 0, 255},
			{ 0, 1, 0, 255, 0, 255},
			{1, -1, 0, 0, 255, 255}
		};

		m_Mesh = new fw::Mesh(points, 3, GL_TRIANGLES);
	}
	else if (num == 2)
	{
		fw::VertexFormat points[] = {
			{-1, -1, 255, 0, 0, 255},
			{ 0, 1, 0, 255, 0, 255},
			{1, -1, 0, 0, 255, 255},
			{ 0, 1, 0, 255, 0, 255},
			{1, -1, 0, 0, 255, 255},
			{-1, -1, 255, 0, 0, 255}
		};

		m_Mesh = new fw::Mesh(points, 6, GL_LINES);
	}
	else if (num == 3)
	{
		fw::VertexFormat points[] = {
			{-1, -1, 255, 0, 0, 255},
			{ 0, 1, 0, 255, 0, 255},
			{1, -1, 0, 0, 255, 255}
		};

		m_Mesh = new fw::Mesh(points, 3, GL_TRIANGLES);
	}
	else if (num == 4)
	{
		fw::VertexFormat points[] = {
			{-1, -1, 255, 0, 0, 255},
			{ 0, 1, 0, 255, 0, 255},
			{1, -1, 0, 0, 255, 255}
		};

		m_Mesh = new fw::Mesh(points, 3, GL_TRIANGLES);
	}
	

	
}

GameObject::~GameObject()
{
	delete m_Mesh;

	
}

void GameObject::Update()
{

}

void GameObject::Draw(fw::ShaderProgram* shaderProgram, fw::Vec2 position, float timeElapsed, fw::Vec2 resolution)
{
	m_ShaderProgram = shaderProgram;
	m_Mesh->Draw(m_ShaderProgram, m_Scale, m_Angle, position, timeElapsed, resolution);
}
