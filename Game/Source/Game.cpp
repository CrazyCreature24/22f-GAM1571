#include "Framework.h"
#include "Game.h"


Game::Game(fw::FWCore& core) :
    m_Framework(core)
{
    // Create our mesh.
    float verticies[] = { -0.5f, -0.5f, 0, 0.5f, 0.5f, -0.5f };
    int vertexSize = 2 * sizeof(float);
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertexSize * 3, &verticies[0], GL_STATIC_DRAW);

    m_pBasicShader = new fw::ShaderProgram("Data/Shaders/Basic.vert", "Data/Shaders/Basic.frag" ); //We changed the path to start in the Game folder FOR THE GAMEPROJECT.

}

Game::~Game()
{
    delete m_pBasicShader;
}

void Game::StartFrame()
{

}

void Game::Update(float deltaTime)
{
    if (m_Framework.IsKeyDown('D')) //Does this to get only the first byte
    {
        m_x += 0.01f;
    }
    else if (m_Framework.IsKeyDown('A'))
    {
        m_x += -0.01f;
    }

    if (m_Framework.IsKeyDown('W'))
    {
        m_y += 0.01f;
    }
    else if (m_Framework.IsKeyDown('S'))
    {
        m_y += -0.01f;
    }

    //Change color over time
    m_elapsed += deltaTime;

    if (m_elapsed >= 0.1f)
    {
        m_r += 0.1f;
        m_g += 0.05f;
        m_b += 0.025f;

        if (m_r >= 1.0f)
        {
            m_r -= 1.0f;
        }

        if (m_g >= 1.0f)
        {
            m_g -= 1.0f;
        }

        if (m_b >= 1.0f)
        {
            m_b -= 1.0f;
        }

        m_elapsed -= 0.1f;
    }

    if (m_Framework.IsKeyDown('K')) //Does this to get only the first byte
    {
        m_scaleX += 0.01f;
    }
    else if (m_Framework.IsKeyDown('H'))
    {
        m_scaleX += -0.01f;
    }

    if (m_Framework.IsKeyDown('U'))
    {
        m_scaleY += 0.01f;
    }
    else if (m_Framework.IsKeyDown('J'))
    {
        m_scaleY += -0.01f;
    }
}

void Game::Draw()
{
    glPointSize(20);
    glLineWidth(10);
    glClearColor(0, 0, 0.2f, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(m_pBasicShader->GetProgram());

    GLint u_offset = glGetUniformLocation(m_pBasicShader->GetProgram(), "u_offset");
    glUniform2f(u_offset, m_x, m_y); //This pulls the the Uniform object from the Basic.vert file

    GLint u_scale = glGetUniformLocation(m_pBasicShader->GetProgram(), "u_scale");
    glUniform2f(u_scale, m_scaleX, m_scaleY); //For scale

    GLint u_rotation= glGetUniformLocation(m_pBasicShader->GetProgram(), "u_rotation");
    glUniform1f(u_rotation, 45.0f); //For rotation

    GLint u_color = glGetUniformLocation(m_pBasicShader->GetProgram(), "u_color");
    glUniform4f(u_color, m_r, m_g, m_b, m_a);

    // This below may become obsolite
    
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, false, 8, (void*)0);
    glDrawArrays(GL_TRIANGLES, 0, 4);

}
