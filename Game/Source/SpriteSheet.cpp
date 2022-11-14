#include "Framework.h"
#include <fstream>
#include "SpriteSheet.h"

SpriteInfo::SpriteInfo(string name, fw::Vec2 uvScale, fw::Vec2 uvOffset) :
	Name(name), UVScale(uvScale), UVOffset(uvOffset)
{

}



SpriteSheet::SpriteSheet(const char* filePath)
{
	std::ifstream f(filePath);
	json data = json::parse(f);

	m_SizePicture = Vec2(data["size"][0], data["size"][1]);

	json spritesArray = data["sprites"];

	for (int i = 0; i < spritesArray.size(); i++)
	{
		json temp = spritesArray[i];
		string name = temp["name"];
		fw::Vec2 scale = { temp["size"][0], temp["size"][1] };
		fw::Vec2 offset = { temp["pos"][0], temp["pos"][1] };
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

fw::Vec2 SpriteSheet::GetUVScale(string spriteName)
{
	return m_Sprites[spriteName]->UVScale;
}

fw::Vec2 SpriteSheet::GetUVOffset(string spriteName)
{
	return m_Sprites[spriteName]->UVOffset;
}

fw::Vec2 SpriteSheet::GetSizePicture()
{
	return m_SizePicture;
}


