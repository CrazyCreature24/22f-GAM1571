#pragma once
#include "DataTypes.h"

class fw::Camera;

class ScoreDisplay : public GameObject
{
public:
	ScoreDisplay(fw::Mesh* pMesh, fw::ShaderProgram* pShaderProgram, float timeElapsed, fw::Texture* pTexture);
	~ScoreDisplay();

	void Update(float deltaTime) override;

	void Draw(float color[], Camera* pCamera) override;

	int GetScore() { return m_Score; }
	Vec2 GetOffset() { return m_MeshOffset; }

	void SetScore(int score) { m_Score = score; }
	void SetOffset(Vec2 offset) { m_MeshOffset = offset; }

protected:
	int m_Score = 0;
	int m_TempScore = 0;
	int m_NumDigits = 0;
	Vec2 m_MeshOffset = { 0, 0 };
	Vec2 m_TextureOffset = { 0, 0 };
	Vec2 m_TextureScale = { 0.1f,1 };
};