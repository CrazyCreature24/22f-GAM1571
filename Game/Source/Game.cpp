#include "Framework.h"
#include "Game.h"

//Will need to move for assignment (Mesh class)
struct VertexFormat
{
    float x, y;
    unsigned char r, g, b, a;
};


Game::Game(fw::FWCore& core) :
    m_Framework(core)
{
    m_pImGuiManager = new fw::ImGuiManager(&core);


    // Create our mesh.
    VertexFormat verticies[3] = {
        { -0.5f, -0.5f, 255, 255, 255, 255},
        { 0, 0.5f, 255, 255, 255, 255},
        { 0.5f, -0.5f, 255, 255, 255, 255}
    };

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 3, &verticies[0], GL_STATIC_DRAW);

    m_pBasicShader = new fw::ShaderProgram("Data/Shaders/Basic.vert", "Data/Shaders/Basic.frag" ); //We changed the path to start in the Game folder FOR THE GAMEPROJECT.

}

Game::~Game()
{
    delete m_pBasicShader;

    delete m_pImGuiManager;
}

void Game::StartFrame(float deltaTime)
{
    m_pImGuiManager->StartFrame(deltaTime);

    ImGui::ShowDemoWindow();
}

void Game::Update(float deltaTime)
{
    //ImGui example
    ImGui::DragFloat("Position X", &m_x, 0.01f);
    ImGui::DragFloat("Position Y", &m_y, 0.01f);

    if (ImGui::Button("Reset"))
    {
        m_x = 0.0f;
        m_y = 0.0f;
    }

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

    GLint u_offset = glGetUniformLocation(m_pBasicShader->GetProgram(), "u_Offset");
    glUniform2f(u_offset, m_x, m_y); //This pulls the the Uniform object from the Basic.vert file

    GLint u_scale = glGetUniformLocation(m_pBasicShader->GetProgram(), "u_Scale");
    glUniform2f(u_scale, m_scaleX, m_scaleY); //For scale

    GLint u_rotation= glGetUniformLocation(m_pBasicShader->GetProgram(), "u_Rotation");
    glUniform1f(u_rotation, 45.0f); //For rotation

    GLint u_color = glGetUniformLocation(m_pBasicShader->GetProgram(), "u_Color");
    glUniform4f(u_color, m_r, m_g, m_b, m_a);

    // This below may become obsolite
    
    GLint a_Position = glGetAttribLocation(m_pBasicShader->GetProgram(), "a_Position");
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glEnableVertexAttribArray(a_Position);
    glVertexAttribPointer(a_Position, 2, GL_FLOAT, false, sizeof(VertexFormat), (void*)0);


    //Leave this for later
    //GLint v_Color = glGetAttribLocation(m_pBasicShader->GetProgram(), "v_Color");
    //glEnableVertexAttribArray(v_Color);
    //glVertexAttribPointer(v_Color, 2, GL_FLOAT, false, sizeof(VertexFormat), (void*)0);

    glDrawArrays(GL_TRIANGLES, 0, 4);


    m_pImGuiManager->EndFrame();
}
