#include "Framework.h"
#include "ScoreDisplay.h"

ScoreDisplay::ScoreDisplay()
{

}

ScoreDisplay::~ScoreDisplay()
{

}

void ScoreDisplay::Draw()
{
	int temp = m_Score;
	while (temp > 1)
	{
		temp /= 10;
		m_NumDigits++;
	}

	for (int i = 0; i < m_NumDigits; i++)
	{

	}
}
