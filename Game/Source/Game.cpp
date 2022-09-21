#include "Framework.h"
#include "Game.h"


Game::Game() : 
    m_x(0),
    m_y(0)
{
    // Create our mesh.
    float verticies[] = { 0.5f, 0.5f, 0.5f, 0.2f, 0.1f, 0.4f };
    int vertexSize = 2 * sizeof(float);
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertexSize * 3, &verticies[0], GL_STATIC_DRAW);

    m_pBasicShader = new fw::ShaderProgram("Data/Shaders/Basic.vert", "Data/Shaders/Basic.frag" );

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
    if (GetKeyState('D') & 0x8000)
    {
        m_x += 0.01f;
    }
    else if (GetKeyState('A') & 0x8000)
    {
        m_x += -0.01f;
    }

    if (GetKeyState('W') & 0x8000)
    {
        m_y += 0.01f;
    }
    else if (GetKeyState('S') & 0x8000)
    {
        m_y += -0.01f;
    }
}

void Game::Draw()
{
    glPointSize(20);
    glLineWidth(10);
    glClearColor(0, 0, 0.2f, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(m_pBasicShader->GetProgram());

    glUniform2f(0, m_x, m_y);

    // Draw our mesh.
    
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, false, 8, (void*)0);
    glDrawArrays(GL_TRIANGLES, 0, 4);

}
