#pragma once
#include "DataTypes.h"

class ScoreDisplay
{
public:
	ScoreDisplay();
	~ScoreDisplay();

	void Draw();

	int GetScore() { return m_Score; }
	Vec2 GetOffset() { return m_Offset; }

	void SetScore(int score) { m_Score = score; }
	void SetOffset(Vec2 offset) { m_Offset = offset; }

protected:
	int m_Score = 0;
	int m_NumDigits = 1;
	Vec2 m_Offset = { 0, 0 };
};