#pragma once

//Comment out for class work

namespace fw
{
	class ShaderProgram;

	struct VertexFormat
	{
		float x, y;
		unsigned char r, g, b, a;
	};

	class Mesh
	{
	public:
		Mesh(VertexFormat* verticies, GLenum pType);
		~Mesh();
		void Draw(ShaderProgram* m_pBasicShader, float scaleX, float scaleY, float angle, float posX, float posY, float aspec);

	protected:

		GLuint m_vbo = 0;

		GLenum m_Type = 0;
	};
}