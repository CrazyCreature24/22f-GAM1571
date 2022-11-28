#pragma once

namespace fw {

	class Mesh;
	class Texture;

	enum class TileType
	{
		Grass,
		Water,
		Wall,
		NumTypes
	};

	struct TileProperties
	{
		Mesh* m_pSprite = nullptr;
		Texture* m_pTexture = nullptr;
		bool m_Walkable = true;

	};

	class Tilemap
	{
	public:
		Tilemap();
		~Tilemap();

	protected:

		int m_Width = 0;
		int m_Height = 0;

		TileProperties* m_pTileProperties = nullptr;

	};
}