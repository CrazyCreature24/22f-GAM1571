#include "CoreHeaders.h"
#include "FWCore.h"
#include "Utility/ShaderProgram.h"
#include "Rendering/Texture.h"
#include "Rendering/Camera.h"
#include "Rendering/SpriteSheet.h"
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


	void SetUniform1f(ShaderProgram* m_pBasicShader, const char* name, float num)
	{
		GLint Location = glGetUniformLocation(m_pBasicShader->GetProgram(), name);
		glUniform1f(Location, num);
	}

	void SetUniform2f(ShaderProgram* m_pBasicShader, const char* name, Vec2 nums)
	{
		GLint Location = glGetUniformLocation(m_pBasicShader->GetProgram(), name);
		glUniform2f(Location, nums.x, nums.y);
	}

	void SetUniform3f(ShaderProgram* m_pBasicShader, const char* name, float num1, float num2, float num3)
	{
		GLint Location = glGetUniformLocation(m_pBasicShader->GetProgram(), name);
		glUniform3f(Location, num1, num2, num3);
	}

	void SetUniform4f(ShaderProgram* m_pBasicShader, const char* name, float num1, float num2, float num3, float num4 )
	{
		GLint Location = glGetUniformLocation(m_pBasicShader->GetProgram(), name);
		glUniform4f(Location, num1, num2, num3, num4);
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

	void Mesh::Draw(ShaderProgram* m_pBasicShader, Vec2 scale, float angle, Vec2 position, float timeElapsed, fw::Texture* pTexture, Camera* pCamera, SpriteSheet* pSpriteSheet, SpriteInfo* pSpriteInfo)
	{
		Vec2 uvscale = Vec2(pSpriteInfo->UVScale.x / pSpriteSheet->GetSizePicture().x, pSpriteInfo->UVScale.y / pSpriteSheet->GetSizePicture().y);
		Vec2 uvoffset = Vec2(pSpriteInfo->UVOffset.x / pSpriteSheet->GetSizePicture().x, pSpriteInfo->UVOffset.y / pSpriteSheet->GetSizePicture().y);

		Draw(m_pBasicShader, scale, angle, position, timeElapsed, pTexture, pCamera, uvscale, uvoffset);
	}

	void Mesh::Draw(ShaderProgram* m_pBasicShader, Vec2 scale, float angle, Vec2 position, float timeElapsed, fw::Texture* pTexture, Camera* pCamera, Vec2 UVscale, Vec2 UVoffset)
	{
		glPointSize(20);
		glLineWidth(5);
		
		//float Aspect = resolution.y / resolution.x;

		glUseProgram(m_pBasicShader->GetProgram());

		SetUniform1f(m_pBasicShader, "u_Angle", angle);
		SetUniform2f(m_pBasicShader, "u_Scale", scale);
		SetUniform2f(m_pBasicShader, "u_Offset", position);
		SetUniform4f(m_pBasicShader, "u_Color", 0, 0, 0, 255 );

		SetUniform1f(m_pBasicShader, "iGlobalTime", timeElapsed);
		SetUniform4f(m_pBasicShader, "iDate", 0, 0, 0, timeElapsed);
		SetUniform3f(m_pBasicShader, "iResolution", pCamera->GetWindowSize().x, pCamera->GetWindowSize().y, 1);

		SetUniform2f(m_pBasicShader, "u_ProjectionScale", pCamera->GetProjectionScale());
		SetUniform2f(m_pBasicShader, "u_CameraPosition", pCamera->GetPosition());

		
		SetUniform2f(m_pBasicShader, "u_UVScale", Vec2(UVscale.x, UVscale.y));
		SetUniform2f(m_pBasicShader, "u_UVOffset", Vec2(UVoffset.x, UVoffset.y));


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