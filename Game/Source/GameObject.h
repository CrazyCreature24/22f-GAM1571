#pragma once
#include "DataTypes.h"

class fw::Mesh;
class fw::ShaderProgram;
class fw::Texture;
class SpriteSheet;
struct SpriteInfo;

class GameObject
{
public:
	GameObject(fw::Mesh* pMesh, fw::ShaderProgram* pShaderProgram, float timeElapsed, fw::Vec2 resolution, fw::Texture* pTexture, SpriteSheet* pSpriteSheet);
	~GameObject();
	void Update();
	void Draw(float color[]);

	//Setters
	void SetResolution(fw::Vec2 resolution) { m_Resolution = resolution; }
	void SetTimeElapsed(float timeElapsed) { m_TimeElapsed = timeElapsed; }
	void SetPosition(fw::Vec2 position) { m_Position = position; }
	void SetScale(fw::Vec2 scale) { m_Scale = scale; }
	void SetAngle(float angle) { m_Angle = angle; }
	void SetMesh(Mesh* mesh) { m_pMesh = mesh; }

	//Getters
	fw::Vec2 GetPosition() { return m_Position; }
	fw::Vec2 GetScale() { return m_Scale; }
	float GetAngle() { return m_Angle; }
	fw::Mesh* GetMesh() { return m_pMesh; }

protected:
	float m_TimeElapsed = 0.0f;
	Vec2 m_Resolution = { 0,0 };

	Vec2 m_Position = { 0, 0 };
	Vec2 m_Scale = { 1.0f, 1.0f };
	float m_Angle = 0.0f;
	fw::Mesh* m_pMesh = nullptr;
	fw::ShaderProgram* m_pShaderProgram = nullptr;
	fw::Texture* m_pTexture = nullptr;
	SpriteSheet* m_pSpriteSheet = nullptr;
	
	SpriteInfo* m_pSpriteInfo = nullptr;

};