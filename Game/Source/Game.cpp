#include "Framework.h"
#include "Game.h"


Game::Game()
{
    // Create our mesh.
    float verticies[] = { 0.5f, 0.5f, 0.5f, 0.2f, 0.1f, 0.4f, 0.1f, 0.8f };
    int vertexSize = 2 * sizeof(float);
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertexSize * 4, &verticies[0], GL_STATIC_DRAW);

}

Game::~Game()
{

}

void Game::StartFrame()
{

}

void Game::Update()
{

}

void Game::Draw()
{
    glClearColor(0, 0, 0.2f, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw our mesh.
    glPointSize(20);
    glLineWidth(10);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, false, 8, (void*)0);
    glDrawArrays(GL_QUADS, 0, 4);

}
