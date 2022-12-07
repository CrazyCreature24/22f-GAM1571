#pragma once
#include "DataTypes.h"

class fw::Camera;

class ScoreDisplay : public GameObject
{
public:
	ScoreDisplay(fw::Mesh* pMesh, fw::ShaderProgram* pShaderProgram, fw::Texture* pTexture);
	~ScoreDisplay();

	void Update(float deltaTime) override;
	void Draw(Camera* pCamera) override;

	int GetScore() { return m_Score; }

	void SetScore(int score) { m_Score = score; }

protected:
	int m_Score = 0;
	int m_DisplayScore = 0;
	int m_NumDigits = 0;
	Vec2 m_TextureOffset = { 0, 0 };
	Vec2 m_TextureScale = { 0.1f,1 };
};