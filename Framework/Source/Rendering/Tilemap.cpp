#include "CoreHeaders.h"
#include "Mesh.h"
#include "Texture.h"
#include "Tilemap.h"

namespace fw {

	Tilemap::Tilemap()
	{
		//m_pTileProperties = new TileProperties[static_cast<std::underlying_type<TileType>::type>(TileType::NumTypes)];
		
	}

	Tilemap::~Tilemap()
	{
		//delete[] m_pTileProperties;
	}

}