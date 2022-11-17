#pragma once
#include "DataTypes.h"

class fw::Mesh;
class fw::ShaderProgram;
class fw::Texture;
class fw::SpriteSheet;
struct fw::SpriteInfo;

class GameObject
{
public:
	GameObject();
	GameObject(fw::Mesh* pMesh, fw::ShaderProgram* pShaderProgram, float timeElapsed, fw::Texture* pTexture, SpriteSheet* pSpriteSheet);
	virtual ~GameObject();
	virtual void Update(float deltaTime);
	virtual void Draw(Camera* pCamera);

	//Setters
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

	Vec2 m_Position = { 0, 0 };
	Vec2 m_Scale = { 1.0f, 1.0f };
	float m_Angle = 0.0f;
	fw::Mesh* m_pMesh = nullptr;
	fw::ShaderProgram* m_pShaderProgram = nullptr;
	fw::Texture* m_pTexture = nullptr;
	SpriteSheet* m_pSpriteSheet = nullptr;
	
	SpriteInfo* m_pSpriteInfo = nullptr;

};