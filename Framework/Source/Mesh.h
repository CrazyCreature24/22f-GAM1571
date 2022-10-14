#pragma once
#include "Vec2.h"

namespace fw
{
	class ShaderProgram;
	
	//Other classes rely on VertexFormat
	struct VertexFormat
	{
		VertexFormat(float x, float y, unsigned char r, unsigned char g, unsigned char b, unsigned char a);

		Vec2 position;
		unsigned char r, g, b, a;
	};

	class Mesh
	{
	public:
		Mesh(std::vector<VertexFormat> verticies, GLenum pType);
		~Mesh();
		void Draw(ShaderProgram* m_pBasicShader, Vec2 scale, float angle, Vec2 position, float timeElapsed, Vec2 resolution, float color[], int size);

		void RebuildVBO();

		void AddVert(fw::VertexFormat vert);
		void AddVertTriangle();
		
		void ClearVerts();
		void RemoveVerts(int numRemoved);

	protected:

		GLuint m_vbo = 0;

		GLenum m_Type = 0;

		int m_NumVerts = 0;

		std::vector<VertexFormat> verticies1;
	};
}