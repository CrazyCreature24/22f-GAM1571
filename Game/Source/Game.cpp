#include "Framework.h"
#include "GameObject.h"
#include "Game.h"

Game::Game(fw::FWCore& core) :
    m_Framework(core)
{
    m_pImGuiManager = new fw::ImGuiManager(&core);


    // Create our mesh for player
    fw::VertexFormat verticies[] = {
        { -0.3f, 1.4f, 100, 255, 255, 255},
        { 0.3, 1.4f, 255, 255, 255, 255},
        { -0.3f, 1.1f, 255, 255, 255, 255},//1Triangle //Head
        { 0.3, 1.4f, 255, 100, 255, 255},
        { -0.3f, 1.1f, 255, 255, 255, 255},
        { 0.3f, 1.1f, 100, 255, 255, 255},//2Triangle  //Head
        { 0.5f, 1.1f, 255, 255, 255, 255},
        { -0.5f, 1.1f, 255, 255, 255, 255},
        { -0.5f, 0.2f, 255, 255, 100, 255},//3Triangle //Body
        { 0.5f, 1.1f, 255, 255, 255, 255},
        { -0.5f, 0.2f, 255, 255, 255, 255},
        { 0.5f, 0.2f, 255, 100, 255, 255}, //4Triangle //Body
        { 0.5f, 0.6f, 255, 0, 0, 255},
        { 0.5f, 0.8f, 0, 255, 0, 255},
        { 1.0f, 1.0f, 0, 0, 255, 255}, //5Triangle //Right arm
        { -0.5f, 0.6f, 255, 255, 255, 255},
        { -0.5f, 0.8f, 255, 255, 255, 255},
        { -1.0f, 1.0f, 255, 255, 255, 255}, //6Triangle //Left arm
        { 0.1f, 0.2f, 255, 255, 255, 255},
        { 0.3f, 0.2f, 255, 255, 255, 255},
        { 0.2f, -0.6f, 255, 255, 255, 255}, //7Triangle //Right Leg
        { -0.1f, 0.2f, 255, 255, 255, 255},
        { -0.3f, 0.2f, 255, 255, 255, 255},
        { -0.2f, -0.6f, 255, 255, 255, 255} //8Triangle //Left Leg
    };

    numVertsPlayer = (int)sizeof(verticies) / sizeof(fw::VertexFormat);
    m_Player = new fw::Mesh(verticies, numVertsPlayer, GL_TRIANGLES);

    //Create mesh for Enemy
    fw::VertexFormat enemyVerts[] = {
        { 0, 1.4f, 255, 255, 255, 255},
        { 0.3, 1.1f, 255, 255, 255, 255}, //Line 1 // Head
        { 0, 1.4f, 255, 255, 255, 255},
        { -0.3f, 1.1f, 255, 255, 255, 255}, //Line 2 //Head
        { -0.3f, 1.1f, 255, 255, 255, 255},
        { 0.3f, 1.1f, 255, 255, 255, 255}, //Line 3 //Head
        { 0, 1.1f, 255, 255, 255, 255},
        { 0, 0.5f, 255, 255, 255, 255}, //Line 4 //Body
        { 0, 0.9f, 255, 255, 255, 255},
        { 0.7f, 1.1f, 255, 255, 255, 255},//Line 5 //Right Arm
        { 0, 0.9f, 255, 255, 255, 255},
        { -0.7f, 1.1f, 255, 255, 255, 255}, //Line 6 //Left arm
        { 0, 0.5f, 255, 255, 255, 255},
        { 0.5f, 0, 255, 255, 255, 255}, //Line 7 //Right leg
        { 0, 0.5f, 255, 255, 255, 255},
        { -0.5f, 0, 255, 255, 255, 255} //Line 8 //Left leg
    };

    

    numVertsEnemy = sizeof(enemyVerts) / sizeof(fw::VertexFormat);
    m_Enemy = new fw::Mesh(enemyVerts, numVertsEnemy, GL_LINES);
    
    m_pBasicShader = new fw::ShaderProgram("Data/Shaders/Basic.vert", "Data/Shaders/Basic.frag" ); //We changed the path to start in the Game folder FOR THE GAMEPROJECT.
    m_pEnemyShader = new fw::ShaderProgram("Data/Shaders/Basic.vert", "Data/Shaders/Basic.frag");

    m_pGameObjects.push_back(new GameObject("Triangle"));
    //m_pGameObjects.push_back(new GameObject());
    //m_pGameObjects.push_back(new GameObject());
    //m_pGameObjects.push_back(new GameObject());

}

Game::~Game()
{
    delete m_Player;

    delete m_Enemy;

    delete m_pBasicShader;

    delete m_pEnemyShader;

    delete m_pImGuiManager;

    for (auto& i : m_pGameObjects)
    {
        delete i;
    }
}

void Game::StartFrame(float deltaTime)
{
    m_pImGuiManager->StartFrame(deltaTime);

    ImGui::ShowDemoWindow();
}

void Game::Update(float deltaTime)
{
    //ImGui example
    ImGui::DragFloat("Position X", &m_Position.x, 0.01f);
    ImGui::DragFloat("Position Y", &m_Position.y, 0.01f);

    if (ImGui::Button("Reset"))
    {
        m_Position.x = 0.0f;
        m_Position.y = 0.0f;
    }

    ImGui::ColorEdit3("Color", m_Color);


    if (m_Framework.IsKeyDown('D')) //Does this to get only the first byte
    {
        m_Position.x += 2.0f * deltaTime;
    }
    else if (m_Framework.IsKeyDown('A'))
    {
        m_Position.x += -2.0f * deltaTime;
    }

    if (m_Framework.IsKeyDown('W'))
    {
        m_Position.y += 2.0f * deltaTime;
    }
    else if (m_Framework.IsKeyDown('S'))
    {
        m_Position.y += -2.0f * deltaTime;
    }

    //Change color over time
    m_elapsed += deltaTime;

    //TODO: Needs to be actioned in Mesh (Color)
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
        m_Scale.x += 0.01f;
    }
    else if (m_Framework.IsKeyDown('H'))
    {
        m_Scale.x += -0.01f;
    }

    if (m_Framework.IsKeyDown('U'))
    {
        m_Scale.y += 0.01f;
    }
    else if (m_Framework.IsKeyDown('J'))
    {
        m_Scale.y += -0.01f;
    }

    glViewport(0, 0, m_Framework.GetWindowWidth(), m_Framework.GetWindowHeight());

    m_ElapsedTime += deltaTime;
}

void Game::Draw()
{
    fw::Vec2 resolution = { (float)m_Framework.GetWindowWidth(), (float)m_Framework.GetWindowHeight() };
    fw::Vec2 position1 = { -1.2f, 0 };

    m_pGameObjects[0]->Draw(m_pBasicShader, position1, m_ElapsedTime, resolution);

    for (auto& i : m_pGameObjects)
    {
        i->Draw(m_pBasicShader, position1, m_ElapsedTime, resolution);
    }
    
    m_Player->Draw(m_pBasicShader, m_Scale, 0, m_Position, m_ElapsedTime, resolution);

    fw::Vec2 position = { 1.2f, 0 };
    m_Enemy->Draw(m_pBasicShader, m_Scale, 0, position, m_ElapsedTime, resolution);
    
    /* -----------Can be Killed soon----
     {
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
    }
    */
    
    m_pImGuiManager->EndFrame();
}

void Game::OnEvent(fw::Event* pEvent)
{

}
