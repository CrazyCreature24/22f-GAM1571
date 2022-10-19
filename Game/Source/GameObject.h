#pragma once
#include "DataTypes.h"

class fw::Mesh;
class fw::ShaderProgram;

class GameObject
{
public:
	GameObject(fw::Mesh* pMesh, fw::ShaderProgram* shaderProgram, float timeElapsed, fw::Vec2 resolution);
	~GameObject();
	void Update();
	void Draw(float color[]);

	//Setters
	void SetResolution(fw::Vec2 resolution);
	void SetTimeElapsed(float timeElapsed);
	void SetPosition(fw::Vec2 position);
	void SetScale(fw::Vec2 scale);
	void SetAngle(float angle);

	//Getters
	fw::Vec2 GetPosition();
	fw::Vec2 GetScale();
	float GetAngle();
	fw::Mesh* GetMesh();

protected:
	float m_TimeElapsed = 0.0f;
	Vec2 m_Resolution = { 0,0 };

	Vec2 m_Position = {0, 0};
	Vec2 m_Scale = { 1.0f,1.0f };
	float m_Angle = 0.0f;
	fw::Mesh* m_Mesh = nullptr;
	fw::ShaderProgram* m_ShaderProgram = nullptr;

	

};