#include "CoreHeaders.h"
#include "FWCore.h"
#include "Utility/ShaderProgram.h"
#include "Rendering/Texture.h"
#include "Mesh.h"

namespace fw {

	VertexFormat::VertexFormat(float x, float y, unsigned char r, unsigned char g, unsigned char b, unsigned char a) :
		position(x, y),
		r(r),
		g(g),
		b(b),
		a(a)
	{
	}

	VertexFormat::VertexFormat(float x, float y, unsigned char r, unsigned char g, unsigned char b, unsigned char a, float uvx, float uvy) :
		position(x, y),
		r(r),
		g(g),
		b(b),
		a(a),
		uv(uvx,uvy)
	{

	}




	Mesh::Mesh(const std::vector<VertexFormat>& verticies, GLenum pType)
	{
		m_NumVerts = (int)verticies.size();

		glGenBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * m_NumVerts, verticies.data(), GL_STATIC_DRAW);

		m_VerticiesCopy = verticies;

		m_Type = pType;
	}

	Mesh::~Mesh()
	{

		glDeleteBuffers(1, &m_VBO);
	}

	void Mesh::Draw(ShaderProgram* m_pBasicShader, Vec2 scale, float angle, Vec2 position, float timeElapsed, Vec2 resolution, float color[], fw::Texture* pTexture)
	{
		glPointSize(20);
		glLineWidth(5);
		

		glUseProgram(m_pBasicShader->GetProgram());

		GLint u_Offset = glGetUniformLocation(m_pBasicShader->GetProgram(), "u_Offset");
		glUniform2f(u_Offset, position.x, position.y); //This pulls the the Uniform object from the Basic.vert file

		GLint u_Scale = glGetUniformLocation(m_pBasicShader->GetProgram(), "u_Scale");
		glUniform2f(u_Scale, scale.x, scale.y); //For scale

		GLint u_Rotation = glGetUniformLocation(m_pBasicShader->GetProgram(), "u_Rotation");
		glUniform1f(u_Rotation, angle); //For rotation

		GLint u_Color = glGetUniformLocation(m_pBasicShader->GetProgram(), "u_Color");
		glUniform4f(u_Color, color[0], color[1], color[2], color[3]);

		float Aspect = resolution.y / resolution.x;

		GLint u_Aspect = glGetUniformLocation(m_pBasicShader->GetProgram(), "u_Aspect");
		glUniform1f(u_Aspect, Aspect);

		GLint u_iGlobalTime = glGetUniformLocation(m_pBasicShader->GetProgram(), "iGlobalTime");
		glUniform1f(u_iGlobalTime, timeElapsed);

		GLint u_iDate = glGetUniformLocation(m_pBasicShader->GetProgram(), "iDate");
		glUniform4f(u_iDate, 0, 0, 0, timeElapsed);

		GLint u_iResolution = glGetUniformLocation(m_pBasicShader->GetProgram(), "iResolution");
		glUniform3f(u_iResolution, resolution.x, resolution.y, 1);

		if (pTexture != nullptr)
		{
			int textureUnitNumber = 0;
			glActiveTexture(GL_TEXTURE0 + textureUnitNumber);
			glBindTexture(GL_TEXTURE_2D, pTexture->GetTextureID());
			GLint u_ColorTexture = glGetUniformLocation(m_pBasicShader->GetProgram(), "u_ColorTexture");
			glUniform1i(u_ColorTexture, textureUnitNumber);
		}



		GLint a_Position = glGetAttribLocation(m_pBasicShader->GetProgram(), "a_Position");
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glEnableVertexAttribArray(a_Position);
		glVertexAttribPointer(a_Position, 2, GL_FLOAT, false, sizeof(VertexFormat), (void*)offsetof(VertexFormat, position)); //Be careful of this

		GLint a_Color = glGetAttribLocation(m_pBasicShader->GetProgram(), "a_Color");
		glEnableVertexAttribArray(a_Color);
		glVertexAttribPointer(a_Color, 4, GL_UNSIGNED_BYTE, true, sizeof(VertexFormat), (void*)offsetof(VertexFormat, r));

		GLint a_UV = glGetAttribLocation(m_pBasicShader->GetProgram(), "a_UV");
		glEnableVertexAttribArray(a_UV);
		glVertexAttribPointer(a_UV, 2, GL_FLOAT, false, sizeof(VertexFormat), (void*)offsetof(VertexFormat, uv));

		

		glDrawArrays(m_Type, 0, m_NumVerts);
	}

	void Mesh::RebuildVBO()
	{
		glDeleteBuffers(1, &m_VBO);

		m_NumVerts = (int)m_VerticiesCopy.size();

		glGenBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * m_NumVerts, m_VerticiesCopy.data(), GL_STATIC_DRAW);
	}

	void Mesh::AddVert(fw::VertexFormat vert)
	{
		m_VerticiesCopy.push_back(vert);
	}

	void Mesh::AddVerts(const std::vector<VertexFormat>& verticies)
	{
		for (int i = 0; i < verticies.size(); i++)
		{
			m_VerticiesCopy.push_back(verticies[i]);
		}
	}

	void Mesh::ClearVerts()
	{
		m_VerticiesCopy.clear();
	}

	void Mesh::RemoveVerts(int numRemoved)
	{
		for (int i = 0; i < numRemoved; i++)
		{
			if (m_VerticiesCopy.size() > 0)
			{
				m_VerticiesCopy.pop_back();
			}
		}
	}

	

}