#include "CoreHeaders.h"
#include "FWCore.h"
#include "Utility/ShaderProgram.h"
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




	Mesh::Mesh(std::vector<VertexFormat> verticies, GLenum pType)
	{
		//BindBuffer(verticies);

		m_NumVerts = (int)verticies.size();

		glGenBuffers(1, &m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * m_NumVerts, verticies.data(), GL_STATIC_DRAW);

		verticies1 = verticies;

		m_Type = pType;
	}

	Mesh::~Mesh()
	{
		
	}

	void Mesh::Draw(ShaderProgram* m_pBasicShader, Vec2 scale, float angle, Vec2 position, float timeElapsed, Vec2 resolution, float color[], int size)
	{
		glPointSize(20);
		glLineWidth(10);
		

		glUseProgram(m_pBasicShader->GetProgram());

		GLint u_offset = glGetUniformLocation(m_pBasicShader->GetProgram(), "u_Offset");
		glUniform2f(u_offset, position.x, position.y); //This pulls the the Uniform object from the Basic.vert file

		GLint u_scale = glGetUniformLocation(m_pBasicShader->GetProgram(), "u_Scale");
		glUniform2f(u_scale, scale.x, scale.y); //For scale

		GLint u_rotation = glGetUniformLocation(m_pBasicShader->GetProgram(), "u_Rotation");
		glUniform1f(u_rotation, angle); //For rotation

		GLint u_color = glGetUniformLocation(m_pBasicShader->GetProgram(), "u_Color");
		glUniform4f(u_color, color[0], color[1], color[2], color[3]);

		float Aspect = resolution.y / resolution.x;

		GLint u_Aspect = glGetUniformLocation(m_pBasicShader->GetProgram(), "u_Aspect");
		glUniform1f(u_Aspect, Aspect);

		GLint u_iGlobalTime = glGetUniformLocation(m_pBasicShader->GetProgram(), "iGlobalTime");
		glUniform1f(u_iGlobalTime, timeElapsed);

		GLint u_iDate = glGetUniformLocation(m_pBasicShader->GetProgram(), "iDate");
		glUniform4f(u_iDate, 0, 0, 0, timeElapsed);

		GLint u_iResolution = glGetUniformLocation(m_pBasicShader->GetProgram(), "iResolution");
		glUniform3f(u_iResolution, resolution.x, resolution.y, 1);

		GLint a_Position = glGetAttribLocation(m_pBasicShader->GetProgram(), "a_Position");
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glEnableVertexAttribArray(a_Position);
		glVertexAttribPointer(a_Position, 2, GL_FLOAT, false, sizeof(VertexFormat), (void*)0);

		GLint a_Color = glGetAttribLocation(m_pBasicShader->GetProgram(), "a_Color");
		glEnableVertexAttribArray(a_Color);
		glVertexAttribPointer(a_Color, 4, GL_UNSIGNED_BYTE, false, sizeof(VertexFormat), (void*)8);

		

		glDrawArrays(m_Type, 0, m_NumVerts);
	}

	void Mesh::RebuildVBO()
	{

		//TODO: Find out how to rebuild vbo properly.
		m_vbo = 0;

		m_NumVerts = (int)verticies1.size();

		glGenBuffers(1, &m_vbo); //Google this thing.
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * m_NumVerts, verticies1.data(), GL_STATIC_DRAW);
	}

	void Mesh::AddVert(fw::VertexFormat vert)
	{
		verticies1.push_back(vert);
	}

	void Mesh::AddVertTriangle()
	{
		verticies1.push_back(fw::VertexFormat(-2.5f, -0.5f, 255, 0, 0, 255));
		verticies1.push_back(fw::VertexFormat(2, 0.5f, 0, 255, 0, 255));
		verticies1.push_back(fw::VertexFormat(2.5f, -0.5f, 0, 0, 255, 255));
	}

	void Mesh::ClearVerts()
	{
		verticies1.clear();
	}

	void Mesh::RemoveVerts(int numRemoved)
	{

		for (int i = 0; i < numRemoved; i++)
		{
			if (verticies1.size() > 0)
			{
				verticies1.pop_back();
			}
		}
	}

	

}