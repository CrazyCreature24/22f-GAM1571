#include "Framework.h"
#include "GameObject.h"
#include "VirtualController.h"
#include <fstream>
#include "Game.h"


Game::Game(fw::FWCore& core) :
    m_rFramework(core)
{
    m_pImGuiManager = new fw::ImGuiManager(&core);
    m_pEventManager = new fw::EventManager(this);

    //Alpha Blend (Gets rid of borders on sprites)
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    // Create our mesh for player
    std::vector<VertexFormat> playerVerts;
    playerVerts.push_back(VertexFormat(-0.3f, 1.4f, 100, 255, 255, 255));
    playerVerts.push_back(VertexFormat(0.3f, 1.4f, 255, 255, 255, 255));
    playerVerts.push_back(VertexFormat(-0.3f, 1.1f, 255, 255, 255, 255));//1Triangle //Head
    playerVerts.push_back(VertexFormat(0.3f, 1.4f, 255, 100, 255, 255));
    playerVerts.push_back(VertexFormat(-0.3f, 1.1f, 255, 255, 255, 255));
    playerVerts.push_back(VertexFormat(0.3f, 1.1f, 100, 255, 255, 255)); //2Triangle  //Head
    playerVerts.push_back(VertexFormat(0.5f, 1.1f, 255, 255, 255, 255));
    playerVerts.push_back(VertexFormat(-0.5f, 1.1f, 255, 255, 255, 255));
    playerVerts.push_back(VertexFormat(-0.5f, 0.2f, 255, 255, 100, 255));//3Triangle //Body
    playerVerts.push_back(VertexFormat(0.5f, 1.1f, 255, 255, 255, 255));
    playerVerts.push_back(VertexFormat(-0.5f, 0.2f, 255, 255, 255, 255));
    playerVerts.push_back(VertexFormat(0.5f, 0.2f, 255, 100, 255, 255)); //4Triangle //Body
    playerVerts.push_back(VertexFormat(0.5f, 0.6f, 255, 0, 0, 255));
    playerVerts.push_back(VertexFormat(0.5f, 0.8f, 0, 255, 0, 255));
    playerVerts.push_back(VertexFormat(1.0f, 1.0f, 0, 0, 255, 255)); //5Triangle //Right arm
    playerVerts.push_back(VertexFormat(-0.5f, 0.6f, 255, 255, 255, 255));
    playerVerts.push_back(VertexFormat(-0.5f, 0.8f, 255, 255, 255, 255));
    playerVerts.push_back(VertexFormat(-1.0f, 1.0f, 255, 255, 255, 255)); //6Triangle //Left arm
    playerVerts.push_back(VertexFormat(0.1f, 0.2f, 255, 255, 255, 255));
    playerVerts.push_back(VertexFormat(0.3f, 0.2f, 255, 255, 255, 255));
    playerVerts.push_back(VertexFormat(0.2f, -0.6f, 255, 255, 255, 255)); //7Triangle //Right Leg
    playerVerts.push_back(VertexFormat(-0.1f, 0.2f, 255, 255, 255, 255));
    playerVerts.push_back(VertexFormat(-0.3f, 0.2f, 255, 255, 255, 255));
    playerVerts.push_back(VertexFormat(-0.2f, -0.6f, 255, 255, 255, 255)); //8Triangle //Left Leg

    //Create mesh for Enemy
    std::vector<VertexFormat> enemyVerts;
    enemyVerts.push_back(VertexFormat(0, 1.4f, 0, 255, 255, 255));
    enemyVerts.push_back(VertexFormat(0.3f, 1.1f, 255, 0, 255, 255)); //Line 1 // Head
    enemyVerts.push_back(VertexFormat(0, 1.4f, 255, 255, 0, 255));
    enemyVerts.push_back(VertexFormat(-0.3f, 1.1f, 0, 255, 255, 255)); //Line 2 //Head
    enemyVerts.push_back(VertexFormat(-0.3f, 1.1f, 255, 255, 0, 255));
    enemyVerts.push_back(VertexFormat(0.3f, 1.1f, 255, 0, 255, 255)); //Line 3 //Head
    enemyVerts.push_back(VertexFormat(0, 1.1f, 255, 0, 255, 255));
    enemyVerts.push_back(VertexFormat(0, 0.5f, 255, 255, 0, 255)); //Line 4 //Body
    enemyVerts.push_back(VertexFormat(0, 0.9f, 255, 255, 255, 255));
    enemyVerts.push_back(VertexFormat(0.7f, 1.1f, 255, 255, 255, 255));//Line 5 //Right Arm
    enemyVerts.push_back(VertexFormat(0, 0.9f, 255, 255, 255, 255));
    enemyVerts.push_back(VertexFormat(-0.7f, 1.1f, 255, 255, 255, 255)); //Line 6 //Left arm
    enemyVerts.push_back(VertexFormat(0, 0.5f, 255, 255, 255, 255));
    enemyVerts.push_back(VertexFormat(0.5f, 0, 255, 255, 255, 255)); //Line 7 //Right leg
    enemyVerts.push_back(VertexFormat(0, 0.5f, 255, 255, 255, 255));
    enemyVerts.push_back(VertexFormat(-0.5f, 0, 255, 255, 255, 255)); //Line 8 //Left leg

    std::vector<VertexFormat> boxVerts;
    boxVerts.push_back(VertexFormat(-1, -1, 100, 255, 255, 255, 0, 0));
    boxVerts.push_back(VertexFormat(-1, 1, 255, 255, 255, 255, 0, 1));
    boxVerts.push_back(VertexFormat(1, 1, 255, 255, 255, 255, 1, 1));
    boxVerts.push_back(VertexFormat(1, 1, 255, 255, 255, 255, 1, 1));
    boxVerts.push_back(VertexFormat(-1, -1, 255, 255, 255, 255, 0, 0));
    boxVerts.push_back(VertexFormat(1, -1, 100, 255, 255, 255, 1, 0));


    //Meshes
    m_Meshes["Player"] = new Mesh(playerVerts, GL_TRIANGLES);
    m_Meshes["Enemy"] = new Mesh(enemyVerts, GL_LINES);
    m_Meshes["Box"] = new Mesh(boxVerts, GL_TRIANGLES);

    //Shaders
    m_Shaders["Basic"] = new ShaderProgram("Data/Shaders/Basic.vert", "Data/Shaders/Basic.frag"); //We changed the path to start in the Game folder FOR THE GAMEPROJECT.
    m_Shaders["Enemy"] = new ShaderProgram("Data/Shaders/Basic.vert", "Data/Shaders/City.frag");
    m_Shaders["Box"] = new ShaderProgram("Data/Shaders/Texture.vert", "Data/Shaders/Texture.frag");

    //Textures
    m_Textures["Zelda"] = new fw::Texture("Data/Textures/Zelda.png");
    m_Textures["Numbers"] = new fw::Texture("Data/Textures/numbers.png");

    //Cameras
    m_Cameras["Game"] = new Camera(m_rFramework);
    m_Cameras["HUD"] = new Camera(m_rFramework);

    //Load SpriteSheets
    m_SpriteSheets["Zelda"] = new SpriteSheet("Data/Textures/Zelda.json");

    //Sprite Info
    m_SpriteInfos["LinkWalkLeft1"] = new SpriteInfo("LinkWalkLeft1", m_SpriteSheets["Zelda"]->GetUVScale("LinkWalkLeft1"), m_SpriteSheets["Zelda"]->GetUVOffset("LinkWalkLeft1"));

    //Resolution set up for GameObject declarations
    m_Resolution = { (float)m_rFramework.GetWindowWidth(), (float)m_rFramework.GetWindowHeight() };

    //GameObject Creations
    m_pGameObjects.push_back(new GameObject(m_Meshes["Player"], m_Shaders["Basic"], m_ElapsedTime, 0, m_SpriteSheets["Zelda"]));
    m_pGameObjects.push_back(new GameObject(m_Meshes["Enemy"], m_Shaders["Basic"], m_ElapsedTime, 0, m_SpriteSheets["Zelda"]));
    m_pGameObjects.push_back(new GameObject(m_Meshes["Box"], m_Shaders["Box"], m_ElapsedTime, m_Textures["Zelda"], m_SpriteSheets["Zelda"]));
    m_pGameObjects.push_back(new GameObject(m_Meshes["Box"], m_Shaders["Box"], m_ElapsedTime, m_Textures["Zelda"], m_SpriteSheets["Zelda"]));

    //GameObject initial positions
    Vec2 position1 = { -5.0f, 0.0f };
    Vec2 position2 = { 0.0f, 5.0f };
    Vec2 position3 = { 0.0f, -5.0f };
    Vec2 position4 = { 5.0f, 0.0f };

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

    for (auto& it : m_Meshes)
    {
        delete it.second; 
    }

    for (auto& it : m_Shaders)
    {
       delete it.second;
    }

    for (auto& it : m_Textures)
    {
        delete it.second;
    }
     
    for (auto& it : m_SpriteSheets)
    {
        delete it.second;
    }

    for (auto& it : m_SpriteInfos)
    {
        delete it.second;
    }

    for (auto& it : m_Cameras)
    {
        delete it.second;
    }
     
}

void Game::StartFrame(float deltaTime)
{
    m_pImGuiManager->StartFrame(deltaTime);

    ImGui::ShowDemoWindow();

    for (int i = 0; i < c_NumControllers; i++)
    {
        m_pControllers[i]->StartFrame();
    }

    m_pEventManager->ProcessEvents();

}

void Game::Update(float deltaTime)
{

    //Camera Update
    m_Cameras["Game"]->UpdateAspect();
    m_Cameras["HUD"]->UpdateAspect();

    for (auto& i : m_pGameObjects)
    {
        i->Update(deltaTime);
    }

    //ImGui Code
    ImGui::DragFloat("Position X", &m_Position.x, 0.01f);
    ImGui::DragFloat("Position Y", &m_Position.y, 0.01f);

    if (ImGui::Button("Reset"))
    {
        m_Position.x = 0.0f;
        m_Position.y = 0.0f;
    }

    ImGui::ColorEdit3("Color", m_Color);

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

    OnKeyEvent(deltaTime);

    m_Cameras["Game"]->SetPosition(m_Position);
}

void Game::Draw()
{
    //Clear screen every frame
    glClearColor(0, 0, 0.2f, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    // Quiz 1 Draw
    m_Meshes["Box"]->Draw(m_Shaders["Box"], m_Scale, 0, m_Position, m_ElapsedTime, m_Color, m_Textures["Zelda"], m_Cameras["Game"], m_SpriteSheets["Zelda"], m_SpriteInfos["LinkWalkLeft1"]);

    //Draw GameObjects
    for (auto& i : m_pGameObjects)
    {
        i->Draw(m_Color, m_Cameras["Game"]);
    }

    m_pImGuiManager->EndFrame();
}

void Game::OnEvent(fw::Event* pEvent)
{
    m_pControllers[0]->OnEvent(pEvent);
}

void Game::OnKeyEvent(float deltaTime)
{
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
        m_pGameObjects[0]->GetMesh()->AddVert(fw::VertexFormat(-0.5, 1.4f, 0, 0, 100, 255));
        m_pGameObjects[0]->GetMesh()->AddVert(fw::VertexFormat(0.5f, 1.4f, 0, 0, 100, 255));
        m_pGameObjects[0]->GetMesh()->AddVert(fw::VertexFormat(0, 2.0f, 0, 0, 100, 255));
    }

    if (m_pControllers[0]->WasNewlyPressed(VirtualController::Action::RebuildVBO)) // 3
    {
        m_pGameObjects[0]->GetMesh()->RebuildVBO();
    }

    if (m_pControllers[0]->WasNewlyPressed(VirtualController::Action::RemoveVerts)) // 4
    {
        m_pGameObjects[0]->GetMesh()->RemoveVerts(1);
    }

    if (m_pControllers[0]->IsHeld(VirtualController::Action::ReplaceMesh)) // 5
    {
        
    }
}
