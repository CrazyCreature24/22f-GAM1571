#pragma once
#include "Vec2.h"

namespace fw
{
	class ShaderProgram;
	
	//Other classes rely on VertexFormat
	struct VertexFormat
	{
		Vec2 position;
		unsigned char r, g, b, a;
	};

	class Mesh
	{
	public:
		Mesh(VertexFormat* verticies, int size, GLenum pType);
		~Mesh();
		void Draw(ShaderProgram* m_pBasicShader, Vec2 scale, float angle, Vec2 position, float timeElapsed, Vec2 resolution);

	protected:

		GLuint m_vbo = 0;

		GLenum m_Type = 0;

		int m_NumVerts = 0;
	};
}