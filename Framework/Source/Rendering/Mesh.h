#pragma once
#include "Math/Vec2.h"

namespace fw
{
	class ShaderProgram;
	class Texture;
	class Camera;
	class SpriteSheet;
	struct SpriteInfo;
	
	//Other classes rely on VertexFormat
	struct VertexFormat
	{
		VertexFormat(float x, float y, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
		VertexFormat(float x, float y, unsigned char r, unsigned char g, unsigned char b, unsigned char a, float uvx, float uvy);

		Vec2 position = { 0, 0 };
		unsigned char r, g, b, a;
		Vec2 uv = { 0, 0 };
	};

	class Mesh
	{
	public:
		Mesh(const std::vector<VertexFormat>& verticies, GLenum pType);
		~Mesh();
		void Draw(ShaderProgram* m_pBasicShader, Vec2 scale, float angle, Vec2 position, float timeElapsed, fw::Texture* pTexture, Camera* pCamera, SpriteSheet* pSpriteSheet, SpriteInfo* pSpriteInfo);
		void Draw(ShaderProgram* m_pBasicShader, Vec2 scale, float angle, Vec2 position, float timeElapsed, fw::Texture* pTexture, Camera* pCamera, Vec2 UVscale, Vec2 UVoffset);


		void RebuildVBO();
		void AddVert(fw::VertexFormat vert);
		void AddVerts(const std::vector<VertexFormat>& verticies);
		void ClearVerts();
		void RemoveVerts(int numRemoved);

	protected:

		GLuint m_VBO = 0;

		GLenum m_Type = 0;

		int m_NumVerts = 0;

		std::vector<VertexFormat> m_VerticiesCopy;

		
	};
}