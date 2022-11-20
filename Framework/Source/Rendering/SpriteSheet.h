#pragma once
#include "Math/Vec2.h"

namespace fw
{
	struct SpriteInfo
	{
		SpriteInfo(std::string name, fw::Vec2 uvScale, fw::Vec2 uvOffset);

		std::string Name;
		fw::Vec2 UVScale = { 1, 1 };
		fw::Vec2 UVOffset = { 0, 0 };
	};

	class SpriteSheet
	{
	public:
		SpriteSheet(const char* filePath);
		~SpriteSheet();

		fw::Vec2 GetUVScale(std::string spriteName);
		fw::Vec2 GetUVOffset(std::string spriteName);
		fw::Vec2 GetSizePicture();
		SpriteInfo* GetSpriteInfo(std::string spriteName);

	protected:
		fw::Vec2 m_SizePicture = { 0, 0 };
		std::map<std::string, SpriteInfo*> m_Sprites;
	};
}