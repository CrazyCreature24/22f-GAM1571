#include "Framework.h"
#include "GameObject.h"
#include "ScoreDisplay.h"

ScoreDisplay::ScoreDisplay(fw::Mesh* pMesh, fw::ShaderProgram* pShaderProgram, float timeElapsed, fw::Texture* pTexture, SpriteSheet* pSpriteSheet = nullptr)
{
	m_pMesh = pMesh;
	m_pShaderProgram = pShaderProgram;
	m_TimeElapsed = timeElapsed;
	m_pTexture = pTexture;
	m_pSpriteSheet = pSpriteSheet;


}

ScoreDisplay::~ScoreDisplay()
{

}

void ScoreDisplay::Update(float deltaTime)
{

}

void ScoreDisplay::Draw(float color[], Camera* pCamera)
{
	int temp = m_Score;
	while (temp > 1)
	{
		temp /= 10;
		m_NumDigits++;
	}

	for (int i = 0; i < m_NumDigits; i++)
	{
		m_pMesh->Draw(m_pShaderProgram, m_Scale, m_Angle, m_Position, m_TimeElapsed, color, m_pTexture, pCamera, m_TextureScale, m_TextureOffset);
	}
}


//TODO: Get the offset and scale for the Texture and have this match the score