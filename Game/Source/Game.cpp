#include "Framework.h"
#include "Game.h"

//Will need to move for assignment (Mesh class) Uncomment for class work
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
        { -0.5f, -0.5f, 1, 1, 1, 1},
        { 0, 0.5f, 1, 1, 1, 1},
        { 0.5f, -0.5f, 1, 1, 1, 1}
    };

    

    //m_mesh = new fw::Mesh(verticies, GL_TRIANGLES); //Comment this out for assignment and uncomment all below
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 3, &verticies[0], GL_STATIC_DRAW);

    m_pBasicShader = new fw::ShaderProgram("Data/Shaders/Basic.vert", "Data/Shaders/Basic.frag" ); //We changed the path to start in the Game folder FOR THE GAMEPROJECT.

    m_pTentacles = new fw::ShaderProgram("Data/Shaders/Basic.vert", "Data/Shaders/TheRoadToHell.frag");
}

Game::~Game()
{
    //delete m_mesh;

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

    ImGui::ColorEdit3("Color", m_Color);


    if (m_Framework.IsKeyDown('D')) //Does this to get only the first byte
    {
        m_x += 2.0f * deltaTime;
    }
    else if (m_Framework.IsKeyDown('A'))
    {
        m_x += -2.0f * deltaTime;
    }

    if (m_Framework.IsKeyDown('W'))
    {
        m_y += 2.0f * deltaTime;
    }
    else if (m_Framework.IsKeyDown('S'))
    {
        m_y += -2.0f * deltaTime;
    }

    //Change color over time
    m_elapsed += deltaTime;

    /*if (m_elapsed >= 0.1f)
    {
        m_Color[0] += 0.1f;
        m_Color[1] += 0.05f;
        m_Color[2] += 0.025f;

        if (m_Color[0] >= 1.0f)
        {
            m_Color[0] -= 1.0f;
        }

        if (m_Color[1] >= 1.0f)
        {
            m_Color[1] -= 1.0f;
        }

        if (m_Color[2] >= 1.0f)
        {
            m_Color[2] -= 1.0f;
        }

        m_elapsed -= 0.1f;
    }*/

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

    glViewport(0, 0, m_Framework.GetWindowWidth(), m_Framework.GetWindowHeight());

    m_ElapsedTime += deltaTime;
}

void Game::Draw()
{
    //m_mesh->Draw(m_pBasicShader, m_scaleX, m_scaleY, 45.0f, m_x, m_y);
    
    glPointSize(20);
    glLineWidth(10);
    glClearColor(0, 0, 0.2f, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    //Triangle 1 ------------------------------------------------------------------------------

    glUseProgram(m_pBasicShader->GetProgram());

    GLint u_offset = glGetUniformLocation(m_pBasicShader->GetProgram(), "u_Offset");
    glUniform2f(u_offset, m_x, m_y); //This pulls the the Uniform object from the Basic.vert file

    GLint u_scale = glGetUniformLocation(m_pBasicShader->GetProgram(), "u_Scale");
    glUniform2f(u_scale, m_scaleX, m_scaleY); //For scale

    GLint u_rotation= glGetUniformLocation(m_pBasicShader->GetProgram(), "u_Rotation");
    glUniform1f(u_rotation, 45.0f); //For rotation

    GLint u_color = glGetUniformLocation(m_pBasicShader->GetProgram(), "u_Color");
    glUniform4f(u_color, m_Color[0], m_Color[1], m_Color[2], m_Color[3]);

    GLint u_windowSize = glGetUniformLocation(m_pBasicShader->GetProgram(), "u_WindowSize");
    glUniform2f(u_windowSize, m_Framework.GetWindowWidth(), m_Framework.GetWindowHeight());



    GLint u_iGlobalTime = glGetUniformLocation(m_pBasicShader->GetProgram(), "iGlobalTime");
    glUniform1f(u_iGlobalTime, m_ElapsedTime);

    GLint u_iDate = glGetUniformLocation(m_pBasicShader->GetProgram(), "iDate");
    glUniform4f(u_iDate, 0, 0, 0, m_ElapsedTime);

    GLint u_iResolution = glGetUniformLocation(m_pBasicShader->GetProgram(), "iResolution");
    glUniform3f(u_iResolution, m_Framework.GetWindowWidth(), m_Framework.GetWindowHeight(), 1);

    // This below may become obsolite
    
    GLint a_Position = glGetAttribLocation(m_pBasicShader->GetProgram(), "a_Position");
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glEnableVertexAttribArray(a_Position);
    glVertexAttribPointer(a_Position, 2, GL_FLOAT, false, sizeof(VertexFormat), (void*)0);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    //Triangle 2 ----------------------------------------------------
    glUseProgram(m_pTentacles->GetProgram());

    GLint u_offset1 = glGetUniformLocation(m_pTentacles->GetProgram(), "u_Offset");
    glUniform2f(u_offset1, 0.2f, 0.5); //This pulls the the Uniform object from the Basic.vert file

    GLint u_scale1 = glGetUniformLocation(m_pTentacles->GetProgram(), "u_Scale");
    glUniform2f(u_scale1, m_scaleX, m_scaleY); //For scale

    GLint u_rotation1 = glGetUniformLocation(m_pTentacles->GetProgram(), "u_Rotation");
    glUniform1f(u_rotation1, 45.0f); //For rotation

    GLint u_color1 = glGetUniformLocation(m_pTentacles->GetProgram(), "u_Color");
    glUniform4f(u_color1, m_r, m_g, m_b, m_a);

    GLint u_windowSize1 = glGetUniformLocation(m_pTentacles->GetProgram(), "u_WindowSize");
    glUniform2f(u_windowSize1, m_Framework.GetWindowWidth(), m_Framework.GetWindowHeight());



    GLint u_iGlobalTime1 = glGetUniformLocation(m_pTentacles->GetProgram(), "iGlobalTime");
    glUniform1f(u_iGlobalTime1, m_ElapsedTime);

    GLint u_iDate1 = glGetUniformLocation(m_pTentacles->GetProgram(), "iDate");
    glUniform4f(u_iDate1, 0, 0, 0, m_ElapsedTime);

    GLint u_iResolution1 = glGetUniformLocation(m_pTentacles->GetProgram(), "iResolution");
    glUniform3f(u_iResolution1, m_Framework.GetWindowWidth(), m_Framework.GetWindowHeight(), 1);

    

    // This below may become obsolite

    GLint a_Position1 = glGetAttribLocation(m_pTentacles->GetProgram(), "a_Position");
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glEnableVertexAttribArray(a_Position1);
    glVertexAttribPointer(a_Position1, 2, GL_FLOAT, false, sizeof(VertexFormat), (void*)0);


    //Leave this for later
    //GLint v_Color = glGetAttribLocation(m_pBasicShader->GetProgram(), "v_Color");
    //glEnableVertexAttribArray(v_Color);
    //glVertexAttribPointer(v_Color, 2, GL_FLOAT, false, sizeof(VertexFormat), (void*)0);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    
    m_pImGuiManager->EndFrame();
}
