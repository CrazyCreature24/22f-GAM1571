#include "Framework.h"
#include "GameObject.h"
#include "ScoreDisplay.h"

ScoreDisplay::ScoreDisplay(fw::Mesh* pMesh, fw::ShaderProgram* pShaderProgram, float timeElapsed, fw::Texture* pTexture)
{
	m_pMesh = pMesh;
	m_pShaderProgram = pShaderProgram;
	m_TimeElapsed = timeElapsed;
	m_pTexture = pTexture;

	
}

ScoreDisplay::~ScoreDisplay()
{

}

void ScoreDisplay::Update(float deltaTime)
{

}

void ScoreDisplay::Draw(Camera* pCamera)
{
	m_NumDigits = 0;
	m_DisplayScore = m_Score;

	//Find number of digits
	int temp = m_Score;
	while (temp >= 1)
	{
		temp /= 10;
		m_NumDigits++;
	}

	int RemainingDigits = m_Score;

	//Gets leftmost digit and displays it
	for (int i = 0; i < m_NumDigits; i++)
	{
		int whichDigit = 1;

		for (int j = 0; j < (m_NumDigits - i - 1); j++)
		{
			whichDigit *= 10;
		}

		if (whichDigit != 0)
		{
			m_DisplayScore = RemainingDigits / whichDigit;

			RemainingDigits = RemainingDigits - (m_DisplayScore * whichDigit);
			
			m_Position = Vec2((17.0f - m_NumDigits) + (i), 9.0f);
			m_TextureOffset = Vec2(m_DisplayScore * 0.1f, 0);
			m_pMesh->Draw(m_pShaderProgram, m_Scale, m_Angle, m_Position, m_TimeElapsed, m_pTexture, pCamera, m_TextureScale, m_TextureOffset);
		}
	}
}