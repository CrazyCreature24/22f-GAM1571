#include "Framework.h"
#include "GameObject.h"
#include "VirtualController.h"
#include "Game.h"

Game::Game(fw::FWCore& core) :
    m_Framework(core)
{
    m_pImGuiManager = new fw::ImGuiManager(&core);

    m_pEventManager = new fw::EventManager(this);

    // Create our mesh for player
    
    std::vector<fw::VertexFormat> player;
    
    
    player.push_back(fw::VertexFormat(-0.3f, 1.4f, 100, 255, 255, 255));
    player.push_back(fw::VertexFormat(0.3f, 1.4f, 255, 255, 255, 255));
    player.push_back(fw::VertexFormat(-0.3f, 1.1f, 255, 255, 255, 255));//1Triangle //Head
    player.push_back(fw::VertexFormat(0.3f, 1.4f, 255, 100, 255, 255));
    player.push_back(fw::VertexFormat(-0.3f, 1.1f, 255, 255, 255, 255));
    player.push_back(fw::VertexFormat(0.3f, 1.1f, 100, 255, 255, 255)); //2Triangle  //Head
    player.push_back(fw::VertexFormat(0.5f, 1.1f, 255, 255, 255, 255));
    player.push_back(fw::VertexFormat(-0.5f, 1.1f, 255, 255, 255, 255));
    player.push_back(fw::VertexFormat(-0.5f, 0.2f, 255, 255, 100, 255));//3Triangle //Body
    player.push_back(fw::VertexFormat(0.5f, 1.1f, 255, 255, 255, 255));
    player.push_back(fw::VertexFormat(-0.5f, 0.2f, 255, 255, 255, 255));
    player.push_back(fw::VertexFormat(0.5f, 0.2f, 255, 100, 255, 255)); //4Triangle //Body
    player.push_back(fw::VertexFormat(0.5f, 0.6f, 255, 0, 0, 255));
    player.push_back(fw::VertexFormat(0.5f, 0.8f, 0, 255, 0, 255));
    player.push_back(fw::VertexFormat(1.0f, 1.0f, 0, 0, 255, 255)); //5Triangle //Right arm
    player.push_back(fw::VertexFormat(-0.5f, 0.6f, 255, 255, 255, 255));
    player.push_back(fw::VertexFormat(-0.5f, 0.8f, 255, 255, 255, 255));
    player.push_back(fw::VertexFormat(-1.0f, 1.0f, 255, 255, 255, 255)); //6Triangle //Left arm
    player.push_back(fw::VertexFormat(0.1f, 0.2f, 255, 255, 255, 255));
    player.push_back(fw::VertexFormat(0.3f, 0.2f, 255, 255, 255, 255));
    player.push_back(fw::VertexFormat(0.2f, -0.6f, 255, 255, 255, 255)); //7Triangle //Right Leg
    player.push_back(fw::VertexFormat(-0.1f, 0.2f, 255, 255, 255, 255));
    player.push_back(fw::VertexFormat(-0.3f, 0.2f, 255, 255, 255, 255));
    player.push_back(fw::VertexFormat(-0.2f, -0.6f, 255, 255, 255, 255)); //8Triangle //Left Leg
    

    
    m_Player = new fw::Mesh(player, GL_TRIANGLES);
    
    //Create mesh for Enemy

    
    std::vector<fw::VertexFormat> enemy;


    
    enemy.push_back(fw::VertexFormat(0, 1.4f, 255, 255, 255, 255));
    enemy.push_back(fw::VertexFormat(0.3f, 1.1f, 255, 255, 255, 255)); //Line 1 // Head
    enemy.push_back(fw::VertexFormat(0, 1.4f, 255, 255, 255, 255));
    enemy.push_back(fw::VertexFormat(-0.3f, 1.1f, 255, 255, 255, 255)); //Line 2 //Head
    enemy.push_back(fw::VertexFormat(-0.3f, 1.1f, 255, 255, 255, 255));
    enemy.push_back(fw::VertexFormat(0.3f, 1.1f, 255, 255, 255, 255)); //Line 3 //Head
    enemy.push_back(fw::VertexFormat(0, 1.1f, 255, 255, 255, 255));
    enemy.push_back(fw::VertexFormat(0, 0.5f, 255, 255, 255, 255)); //Line 4 //Body
    enemy.push_back(fw::VertexFormat(0, 0.9f, 255, 255, 255, 255));
    enemy.push_back(fw::VertexFormat(0.7f, 1.1f, 255, 255, 255, 255));//Line 5 //Right Arm
    enemy.push_back(fw::VertexFormat(0, 0.9f, 255, 255, 255, 255));
    enemy.push_back(fw::VertexFormat(-0.7f, 1.1f, 255, 255, 255, 255)); //Line 6 //Left arm
    enemy.push_back(fw::VertexFormat(0, 0.5f, 255, 255, 255, 255));
    enemy.push_back(fw::VertexFormat(0.5f, 0, 255, 255, 255, 255)); //Line 7 //Right leg
    enemy.push_back(fw::VertexFormat(0, 0.5f, 255, 255, 255, 255));
    enemy.push_back(fw::VertexFormat(-0.5f, 0, 255, 255, 255, 255)); //Line 8 //Left leg
    

    m_Enemy = new fw::Mesh(enemy, GL_LINES);
    //m_Enemy->AddVertTriangle();
    
    m_pBasicShader = new fw::ShaderProgram("Data/Shaders/Basic.vert", "Data/Shaders/Basic.frag" ); //We changed the path to start in the Game folder FOR THE GAMEPROJECT.
    m_pEnemyShader = new fw::ShaderProgram("Data/Shaders/Basic.vert", "Data/Shaders/Basic.frag");

    resolution = { (float)m_Framework.GetWindowWidth(), (float)m_Framework.GetWindowHeight() };
    fw::Vec2 position1 = { -5 + m_Position.x, 0 + m_Position.y };

    m_pGameObjects.push_back(new GameObject(m_Player, m_pBasicShader, position1, m_ElapsedTime, resolution, m_Color, 4));
   // m_pGameObjects.push_back(new GameObject(MeshType::SquareLines, nullptr));
    //m_pGameObjects.push_back(new GameObject(MeshType::TriangleLines, nullptr));
    //m_pGameObjects.push_back(new GameObject(MeshType::SquareFilled, nullptr));


    for (int i = 0; i < m_NumControllers; i++)
    {
        m_pControllers[i] = new VirtualController();
    }

}

Game::~Game()
{
    delete m_Player;

    delete m_Enemy;

    delete m_pBasicShader;

    delete m_pEnemyShader;

    delete m_pImGuiManager;

    delete m_pEventManager;

    for (auto& i : m_pGameObjects)
    {
        delete i;
    }

    for (auto& i : m_pControllers)
    {
        delete i;
    }
}

void Game::StartFrame(float deltaTime)
{
    m_pImGuiManager->StartFrame(deltaTime);

    ImGui::ShowDemoWindow();

    m_pEventManager->ProcessEvents();
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


    if (m_pControllers[0]->IsHeld(VirtualController::Action::Right))
    {
        m_Position.x += 5.0f * deltaTime;
    }
    else if (m_pControllers[0]->IsHeld(VirtualController::Action::Left))
    {
        m_Position.x += -5.0f * deltaTime;
    }
    
    
    //TODO: Switch to Virtual Controller
    if (m_Framework.IsKeyDown('W'))
    {
        m_Position.y += 5.0f * deltaTime;
    }
    else if (m_Framework.IsKeyDown('S'))
    {
        m_Position.y += -5.0f * deltaTime;
    }

    resolution = { (float)m_Framework.GetWindowWidth(), (float)m_Framework.GetWindowHeight() };

    /*
    if (m_Framework.IsKeyDown('T'))
    {
        m_pGameObjects[0]->AddVertTriangle();
        m_pGameObjects[1]->AddVertTriangle();
        m_pGameObjects[2]->AddVertTriangle();
        m_pGameObjects[3]->AddVertTriangle();
    }

    if (m_Framework.IsKeyDown('1'))
    {
       m_pGameObjects[0]->AddRandomVert();
       m_pGameObjects[0]->RemoveVerts(1);
       m_pGameObjects[1]->RemoveVerts(1);
       m_pGameObjects[2]->RemoveVerts(1);
       m_pGameObjects[3]->RemoveVerts(1);
    }

    if (m_Framework.IsKeyDown('C'))
    {
        m_pGameObjects[0]->ClearVerts();
        m_pGameObjects[1]->ClearVerts();
        m_pGameObjects[2]->ClearVerts();
        m_pGameObjects[3]->ClearVerts();
    }
    */

    //Change color over time
    m_elapsed += deltaTime;

    if (m_elapsed >= 0.1f)
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
    }

    if (m_Framework.IsKeyDown('K')) //Does this to get only the first byte
    {
        m_Scale.x += 2.0f * deltaTime;
    }
    else if (m_Framework.IsKeyDown('H'))
    {
        m_Scale.x += -2.0f * deltaTime;
    }

    if (m_Framework.IsKeyDown('U'))
    {
        m_Scale.y += 2.0f * deltaTime;
    }
    else if (m_Framework.IsKeyDown('J'))
    {
        m_Scale.y += -2.0f * deltaTime;
    }

    glViewport(0, 0, m_Framework.GetWindowWidth(), m_Framework.GetWindowHeight());

    m_ElapsedTime += deltaTime;
}

void Game::Draw()
{
    //fw::Vec2 resolution = { (float)m_Framework.GetWindowWidth(), (float)m_Framework.GetWindowHeight() };
   //fw::Vec2 position1 = { -5 + m_Position.x, 0 + m_Position.y };
    //fw::Vec2 position2 = { 0 + m_Position.x, 5 + m_Position.y };
    //fw::Vec2 position3 = { 0 + m_Position.x, -5 + m_Position.y };
    //fw::Vec2 position4 = { 5 + m_Position.x, 0 + m_Position.y };

    m_pGameObjects[0]->Draw();
    //m_pGameObjects[1]->Draw(m_pBasicShader, position2, m_ElapsedTime, resolution, m_Color, 4);
    //m_pGameObjects[2]->Draw(m_pBasicShader, position3, m_ElapsedTime, resolution, m_Color, 4);
    //m_pGameObjects[3]->Draw(m_pBasicShader, position4, m_ElapsedTime, resolution, m_Color, 4);

    //for (auto& i : m_pGameObjects)
    //{
      //  i->Draw(m_pBasicShader, position1, m_ElapsedTime, resolution);
    //}
    
    m_Player->Draw(m_pBasicShader, m_Scale, 0, m_Position, m_ElapsedTime, resolution, m_Color, 4);

    fw::Vec2 position = { 1.2f, 0 };
    m_Enemy->Draw(m_pBasicShader, m_Scale, 0, position, m_ElapsedTime, resolution, m_Color, 4);
    
    
    m_pImGuiManager->EndFrame();
}

void Game::OnEvent(fw::Event* pEvent)
{
    m_pControllers[0]->OnEvent(pEvent);
}
