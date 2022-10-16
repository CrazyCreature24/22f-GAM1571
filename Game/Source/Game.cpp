#include "Framework.h"
#include "GameObject.h"
#include "VirtualController.h"
#include "Game.h"

Game::Game(fw::FWCore& core) :
    m_rFramework(core)
{
    m_pImGuiManager = new fw::ImGuiManager(&core);

    m_pEventManager = new fw::EventManager(this);

    // Create our mesh for player
    std::vector<fw::VertexFormat> playerVerts;
    
    playerVerts.push_back(fw::VertexFormat(-0.3f, 1.4f, 100, 255, 255, 255));
    playerVerts.push_back(fw::VertexFormat(0.3f, 1.4f, 255, 255, 255, 255));
    playerVerts.push_back(fw::VertexFormat(-0.3f, 1.1f, 255, 255, 255, 255));//1Triangle //Head
    playerVerts.push_back(fw::VertexFormat(0.3f, 1.4f, 255, 100, 255, 255));
    playerVerts.push_back(fw::VertexFormat(-0.3f, 1.1f, 255, 255, 255, 255));
    playerVerts.push_back(fw::VertexFormat(0.3f, 1.1f, 100, 255, 255, 255)); //2Triangle  //Head
    playerVerts.push_back(fw::VertexFormat(0.5f, 1.1f, 255, 255, 255, 255));
    playerVerts.push_back(fw::VertexFormat(-0.5f, 1.1f, 255, 255, 255, 255));
    playerVerts.push_back(fw::VertexFormat(-0.5f, 0.2f, 255, 255, 100, 255));//3Triangle //Body
    playerVerts.push_back(fw::VertexFormat(0.5f, 1.1f, 255, 255, 255, 255));
    playerVerts.push_back(fw::VertexFormat(-0.5f, 0.2f, 255, 255, 255, 255));
    playerVerts.push_back(fw::VertexFormat(0.5f, 0.2f, 255, 100, 255, 255)); //4Triangle //Body
    playerVerts.push_back(fw::VertexFormat(0.5f, 0.6f, 255, 0, 0, 255));
    playerVerts.push_back(fw::VertexFormat(0.5f, 0.8f, 0, 255, 0, 255));
    playerVerts.push_back(fw::VertexFormat(1.0f, 1.0f, 0, 0, 255, 255)); //5Triangle //Right arm
    playerVerts.push_back(fw::VertexFormat(-0.5f, 0.6f, 255, 255, 255, 255));
    playerVerts.push_back(fw::VertexFormat(-0.5f, 0.8f, 255, 255, 255, 255));
    playerVerts.push_back(fw::VertexFormat(-1.0f, 1.0f, 255, 255, 255, 255)); //6Triangle //Left arm
    playerVerts.push_back(fw::VertexFormat(0.1f, 0.2f, 255, 255, 255, 255));
    playerVerts.push_back(fw::VertexFormat(0.3f, 0.2f, 255, 255, 255, 255));
    playerVerts.push_back(fw::VertexFormat(0.2f, -0.6f, 255, 255, 255, 255)); //7Triangle //Right Leg
    playerVerts.push_back(fw::VertexFormat(-0.1f, 0.2f, 255, 255, 255, 255));
    playerVerts.push_back(fw::VertexFormat(-0.3f, 0.2f, 255, 255, 255, 255));
    playerVerts.push_back(fw::VertexFormat(-0.2f, -0.6f, 255, 255, 255, 255)); //8Triangle //Left Leg
    
    m_pPlayerMesh = new fw::Mesh(playerVerts, GL_TRIANGLES);
    

    //Create mesh for Enemy
    std::vector<fw::VertexFormat> enemyVerts;
    
    enemyVerts.push_back(fw::VertexFormat(0, 1.4f, 255, 255, 255, 255));
    enemyVerts.push_back(fw::VertexFormat(0.3f, 1.1f, 255, 255, 255, 255)); //Line 1 // Head
    enemyVerts.push_back(fw::VertexFormat(0, 1.4f, 255, 255, 255, 255));
    enemyVerts.push_back(fw::VertexFormat(-0.3f, 1.1f, 255, 255, 255, 255)); //Line 2 //Head
    enemyVerts.push_back(fw::VertexFormat(-0.3f, 1.1f, 255, 255, 255, 255));
    enemyVerts.push_back(fw::VertexFormat(0.3f, 1.1f, 255, 255, 255, 255)); //Line 3 //Head
    enemyVerts.push_back(fw::VertexFormat(0, 1.1f, 255, 255, 255, 255));
    enemyVerts.push_back(fw::VertexFormat(0, 0.5f, 255, 255, 255, 255)); //Line 4 //Body
    enemyVerts.push_back(fw::VertexFormat(0, 0.9f, 255, 255, 255, 255));
    enemyVerts.push_back(fw::VertexFormat(0.7f, 1.1f, 255, 255, 255, 255));//Line 5 //Right Arm
    enemyVerts.push_back(fw::VertexFormat(0, 0.9f, 255, 255, 255, 255));
    enemyVerts.push_back(fw::VertexFormat(-0.7f, 1.1f, 255, 255, 255, 255)); //Line 6 //Left arm
    enemyVerts.push_back(fw::VertexFormat(0, 0.5f, 255, 255, 255, 255));
    enemyVerts.push_back(fw::VertexFormat(0.5f, 0, 255, 255, 255, 255)); //Line 7 //Right leg
    enemyVerts.push_back(fw::VertexFormat(0, 0.5f, 255, 255, 255, 255));
    enemyVerts.push_back(fw::VertexFormat(-0.5f, 0, 255, 255, 255, 255)); //Line 8 //Left leg
   
    m_pEnemyMesh = new fw::Mesh(enemyVerts, GL_LINES);
    
    //Shaders
    m_pBasicShader = new fw::ShaderProgram("Data/Shaders/Basic.vert", "Data/Shaders/Basic.frag" ); //We changed the path to start in the Game folder FOR THE GAMEPROJECT.
    m_pEnemyShader = new fw::ShaderProgram("Data/Shaders/Basic.vert", "Data/Shaders/City.frag");

    //Resolution set up for GameObject declarations
    m_Resolution = { (float)m_rFramework.GetWindowWidth(), (float)m_rFramework.GetWindowHeight() };

    //GameObject Creations
    m_pGameObjects.push_back(new GameObject(m_pPlayerMesh, m_pBasicShader, m_ElapsedTime, m_Resolution));
    m_pGameObjects.push_back(new GameObject(m_pEnemyMesh, m_pBasicShader, m_ElapsedTime, m_Resolution));
    m_pGameObjects.push_back(new GameObject(m_pPlayerMesh, m_pEnemyShader, m_ElapsedTime, m_Resolution));
    m_pGameObjects.push_back(new GameObject(m_pEnemyMesh, m_pEnemyShader, m_ElapsedTime, m_Resolution));

    //GameObject initial positions
    fw::Vec2 position1 = { -5.0f, 0.0f };
    fw::Vec2 position2 = { 0.0f, 5.0f };
    fw::Vec2 position3 = { 0.0f, -5.0f };
    fw::Vec2 position4 = { 5.0f, 0.0f };

    //GameObject Setting positions
    m_pGameObjects[0]->SetPosition(position1);
    m_pGameObjects[1]->SetPosition(position2);
    m_pGameObjects[2]->SetPosition(position3);
    m_pGameObjects[3]->SetPosition(position4);

    //Creating Virtual Controllers
    for (int i = 0; i < c_NumControllers; i++)
    {
        m_pControllers[i] = new VirtualController();
    }

}

Game::~Game()
{
    delete m_pPlayerMesh;

    delete m_pEnemyMesh;

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
    //ImGui Code
    ImGui::DragFloat("Position X", &m_Position.x, 0.01f);
    ImGui::DragFloat("Position Y", &m_Position.y, 0.01f);

    if (ImGui::Button("Reset"))
    {
        m_Position.x = 0.0f;
        m_Position.y = 0.0f;
    }

    ImGui::ColorEdit3("Color", m_Color);

    //Movement
    if (m_pControllers[0]->IsHeld(VirtualController::Action::Right)) // D or Right Arrow
    {
        m_Position.x += 5.0f * deltaTime;
    }
    else if (m_pControllers[0]->IsHeld(VirtualController::Action::Left)) // A or Left arrow
    {
        m_Position.x += -5.0f * deltaTime;
    }

    if (m_pControllers[0]->IsHeld(VirtualController::Action::Up)) // W or Up arrow
    {
        m_Position.y += 5.0f * deltaTime;
    }
    else if (m_pControllers[0]->IsHeld(VirtualController::Action::Down)) // S or Down arrow
    {
        m_Position.y += -5.0f * deltaTime;
    }
    
    //Scale
    if (m_pControllers[0]->IsHeld(VirtualController::Action::ScaleUpX)) // K 
    {
        m_Scale.x += 2.0f * deltaTime;
    }
    else if (m_pControllers[0]->IsHeld(VirtualController::Action::ScaleDownX)) // H
    {
        m_Scale.x += -2.0f * deltaTime;
    }

    if (m_pControllers[0]->IsHeld(VirtualController::Action::ScaleUpY)) // U
    {
        m_Scale.y += 2.0f * deltaTime;
    }
    else if (m_pControllers[0]->IsHeld(VirtualController::Action::ScaleDownY)) // J
    {
        m_Scale.y += -2.0f * deltaTime;
    }

    //Mesh Modification
    if (m_pControllers[0]->WasNewlyPressed(VirtualController::Action::AddVert)) // 1
    {
        m_pGameObjects[0]->GetMesh()->AddVert(fw::VertexFormat(1.0f, 8.0f, 0, 0, 100, 255));
        m_pGameObjects[0]->GetMesh()->AddVert(fw::VertexFormat(3.0f, 5.0f, 0, 0, 100, 255));
        m_pGameObjects[0]->GetMesh()->AddVert(fw::VertexFormat(2.0f, 9.0f, 0, 0, 100, 255));
    }

    if (m_pControllers[0]->WasNewlyPressed(VirtualController::Action::RebuildVBO)) // 2
    {
        m_pGameObjects[0]->GetMesh()->RebuildVBO();
    }
    
    //Change color over time
    m_ColorChangeTimer += deltaTime;

    if (m_ColorChangeTimer >= 0.1f)
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

        m_ColorChangeTimer -= 0.1f;
    }

    //Clipspace update
    glViewport(0, 0, m_rFramework.GetWindowWidth(), m_rFramework.GetWindowHeight());

    //Elapsed Time variable update
    m_ElapsedTime += deltaTime;

    for (auto& i : m_pGameObjects)
    {
        i->SetTimeElapsed(m_ElapsedTime);
    }

    //Resolution Variable update
    m_Resolution = fw::Vec2((float)m_rFramework.GetWindowWidth(), (float)m_rFramework.GetWindowHeight() );

    for (auto& i : m_pGameObjects)
    {
        i->SetResolution(m_Resolution);
    }
}

void Game::Draw()
{
    //Clear screen every frame
    glClearColor(0, 0, 0.2f, 1);
    glClear(GL_COLOR_BUFFER_BIT);


    //Draw GameObjects
    for (auto& i : m_pGameObjects)
    {
        i->Draw(m_Color);
    }
    
    //Draw Player and Enemy
    m_pPlayerMesh->Draw(m_pEnemyShader, m_Scale, 0, m_Position, m_ElapsedTime, m_Resolution, m_Color);

    fw::Vec2 position = { 1.2f, 0 };
    m_pEnemyMesh->Draw(m_pBasicShader, m_Scale, 0, position, m_ElapsedTime, m_Resolution, m_Color);
    
    
    m_pImGuiManager->EndFrame();
}

void Game::OnEvent(fw::Event* pEvent)
{
    m_pControllers[0]->OnEvent(pEvent);
}
