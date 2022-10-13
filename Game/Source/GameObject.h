#pragma once
#include "Vec2.h"

class fw::Mesh;
class fw::ShaderProgram;

class GameObject
{
public:
	GameObject(int num);
	~GameObject();
	void Update();
	void Draw(fw::ShaderProgram* shaderProgram, fw::Vec2 position, float timeElapsed, fw::Vec2 resolution);


protected:
	fw::Vec2 m_Position = { 0, 0 };
	fw::Vec2 m_Scale = { 1.0f,1.0f };
	float m_Angle = 0.0f;
	fw::Mesh* m_Mesh = nullptr;
	fw::ShaderProgram* m_ShaderProgram = nullptr;

};