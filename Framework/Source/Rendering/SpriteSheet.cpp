#include "CoreHeaders.h"
#include "../Libraries/json/json.hpp"
#include <fstream>
#include "SpriteSheet.h"

namespace fw
{
	SpriteInfo::SpriteInfo(std::string name, Vec2 uvScale, fw::Vec2 uvOffset) :
		Name(name), UVScale(uvScale), UVOffset(uvOffset)
	{

	}



	SpriteSheet::SpriteSheet(const char* filePath)
	{
		std::ifstream f(filePath);
		nlohmann::json data = nlohmann::json::parse(f);

		m_SizePicture = Vec2(data["size"][0], data["size"][1]);

		nlohmann::json spritesArray = data["sprites"];

		for (int i = 0; i < spritesArray.size(); i++)
		{
			nlohmann::json temp = spritesArray[i];
			std::string name = temp["name"];
			fw::Vec2 scale = { temp["size"][0] / m_SizePicture.x, temp["size"][1] / m_SizePicture.y }; //TODO: Do the divid by picture size
			fw::Vec2 offset = { temp["pos"][0] / m_SizePicture.x, temp["pos"][1] / m_SizePicture.y };
			m_Sprites[name] = new SpriteInfo(name, scale, offset);
		}

	}

	SpriteSheet::~SpriteSheet()
	{
		for (auto& it : m_Sprites)
		{
			delete it.second;
		}
	}

	fw::Vec2 SpriteSheet::GetUVScale(std::string spriteName)
	{
		return m_Sprites[spriteName]->UVScale;
	}

	fw::Vec2 SpriteSheet::GetUVOffset(std::string spriteName)
	{
		return m_Sprites[spriteName]->UVOffset;
	}

	fw::Vec2 SpriteSheet::GetSizePicture()
	{
		return m_SizePicture;
	}

	SpriteInfo* SpriteSheet::GetSpriteInfo(std::string spriteName)
	{
		return m_Sprites[spriteName];
	}


}