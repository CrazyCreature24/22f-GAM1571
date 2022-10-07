#include "CoreHeaders.h"
#include "FWCore.h"
#include "Vec2.h"
#include "Mesh.h"
#include "Utility/ShaderProgram.h"

//Comment out for class work
/*
namespace fw {


	Mesh::Mesh(VertexFormat* verticies, GLenum pType)
	{
		glGenBuffers(1, &m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 3, &verticies[0], GL_STATIC_DRAW);

		//m_pBasicShader = new fw::ShaderProgram("Data/Shaders/Basic.vert", "Data/Shaders/Basic.frag");

		m_Type = pType;
	}

	Mesh::~Mesh()
	{
		//delete m_pBasicShader;
	}

	void Mesh::Draw(ShaderProgram* m_pBasicShader, float scaleX, float scaleY, float angle, float posX, float posY)
	{
		glPointSize(20);
		glLineWidth(10);
		glClearColor(0, 0, 0.2f, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(m_pBasicShader->GetProgram());

		GLint u_offset = glGetUniformLocation(m_pBasicShader->GetProgram(), "u_Offset");
		glUniform2f(u_offset, posX, posY); //This pulls the the Uniform object from the Basic.vert file

		GLint u_scale = glGetUniformLocation(m_pBasicShader->GetProgram(), "u_Scale");
		glUniform2f(u_scale, scaleX, scaleY); //For scale

		GLint u_rotation = glGetUniformLocation(m_pBasicShader->GetProgram(), "u_Rotation");
		glUniform1f(u_rotation, angle); //For rotation

		//GLint u_color = glGetUniformLocation(m_pBasicShader->GetProgram(), "u_Color");
		//glUniform4f(u_color, m_Color[0], m_Color[1], m_Color[2], m_Color[3]);

		//GLint u_windowSize = glGetUniformLocation(m_pBasicShader->GetProgram(), "u_WindowSize");
		//glUniform2f(u_windowSize, GetWindowWidth(), GetWindowHeight());

		GLint a_Position = glGetAttribLocation(m_pBasicShader->GetProgram(), "a_Position");
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glEnableVertexAttribArray(a_Position);
		glVertexAttribPointer(a_Position, 2, GL_FLOAT, false, sizeof(VertexFormat), (void*)0);

		glDrawArrays(m_Type, 0, 3);
	}

}*/