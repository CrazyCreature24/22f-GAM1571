#pragma once
#include "DataTypes.h"

struct SpriteInfo
{
	SpriteInfo(string name, fw::Vec2 uvScale, fw::Vec2 uvOffset);

	string Name;
	fw::Vec2 UVScale = { 1, 1 };
	fw::Vec2 UVOffset = { 0, 0 };
};

class SpriteSheet
{
public:
	SpriteSheet(const char* filePath);
	~SpriteSheet();

	fw::Vec2 GetUVScale(string spriteName);
	fw::Vec2 GetUVOffset(string spriteName);
	fw::Vec2 GetSizePicture();

protected:
	fw::Vec2 m_SizePicture = { 0, 0 };
	std::map<string, SpriteInfo*> m_Sprites;
};