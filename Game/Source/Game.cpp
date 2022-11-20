#include "Framework.h"
#include "GameObject.h"
#include "VirtualController.h"
#include "ScoreDisplay.h"
#include "Player.h"
#include "Car.h"
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

    std::vector<VertexFormat> ground;
    ground.push_back(VertexFormat(-10, -10, 0, 100, 0, 255, 0, 0));
    ground.push_back(VertexFormat(-10, -5, 0, 100, 0, 255, 0, 1));
    ground.push_back(VertexFormat(10, -5, 0, 100, 0, 255, 1, 1));
    ground.push_back(VertexFormat(10, -5, 0, 100, 0, 255, 1, 1));
    ground.push_back(VertexFormat(-10, -10, 0, 100, 0, 255, 0, 0));
    ground.push_back(VertexFormat(10, -10, 0, 100, 0, 255, 1, 0));


    //Meshes
    m_Meshes["Player"] = new Mesh(playerVerts, GL_TRIANGLES);
    m_Meshes["Enemy"] = new Mesh(enemyVerts, GL_LINES);
    m_Meshes["Box"] = new Mesh(boxVerts, GL_TRIANGLES);
    m_Meshes["Ground"] = new Mesh(ground, GL_TRIANGLES);

    //Shaders
    m_Shaders["Basic"] = new ShaderProgram("Data/Shaders/Basic.vert", "Data/Shaders/Basic.frag"); //We changed the path to start in the Game folder FOR THE GAMEPROJECT.
    m_Shaders["Enemy"] = new ShaderProgram("Data/Shaders/Basic.vert", "Data/Shaders/City.frag");
    m_Shaders["Box"] = new ShaderProgram("Data/Shaders/Texture.vert", "Data/Shaders/Texture.frag");

    //Textures
    m_Textures["Zelda"] = new fw::Texture("Data/Textures/Zelda.png");
    m_Textures["Numbers"] = new fw::Texture("Data/Textures/numbers.png");
    m_Textures["Car"] = new fw::Texture("Data/Textures/Car.png");

    //Cameras
    m_Cameras["Game"] = new Camera(m_rFramework);
    m_Cameras["HUD"] = new Camera(m_rFramework);

    //Load SpriteSheets
    m_SpriteSheets["Zelda"] = new SpriteSheet("Data/Textures/Zelda.json");

    //Sprite Info
    m_SpriteInfos["LinkWalkLeft1"] = new SpriteInfo("LinkWalkLeft1", m_SpriteSheets["Zelda"]->GetUVScale("LinkWalkLeft1"), m_SpriteSheets["Zelda"]->GetUVOffset("LinkWalkLeft1"));

    //ScoreDisplay Decleration
    m_pPlayerScore = new ScoreDisplay(m_Meshes["Box"], m_Shaders["Box"], m_ElapsedTime, m_Textures["Numbers"]);

    //Player
    m_pPlayer1 = new Player(m_Meshes["Box"], m_Shaders["Box"], m_Textures["Zelda"], m_SpriteSheets["Zelda"]);

    //Car
    m_pCar = new Car(m_Meshes["Box"], m_Shaders["Box"], m_Textures["Car"]);
    m_pCar->SetPosition(Vec2(5.0f, 5.0f));

    //Resolution set up for GameObject declarations
    m_Resolution = { (float)m_rFramework.GetWindowWidth(), (float)m_rFramework.GetWindowHeight() };

    //GameObject Creations
    m_pGameObjects["Ground"] = new GameObject(m_Meshes["Ground"], m_Shaders["Basic"], m_ElapsedTime, m_Textures["Zelda"], m_SpriteSheets["Zelda"]);
    m_pGameObjects["Obj1"] = new GameObject(m_Meshes["Player"], m_Shaders["Basic"], m_ElapsedTime, 0, m_SpriteSheets["Zelda"]);
    m_pGameObjects["Obj2"] = new GameObject(m_Meshes["Enemy"], m_Shaders["Basic"], m_ElapsedTime, 0, m_SpriteSheets["Zelda"]);
    m_pGameObjects["Obj3"] = new GameObject(m_Meshes["Box"], m_Shaders["Box"], m_ElapsedTime, m_Textures["Zelda"], m_SpriteSheets["Zelda"]);
    m_pGameObjects["Obj4"] = new GameObject(m_Meshes["Box"], m_Shaders["Box"], m_ElapsedTime, m_Textures["Zelda"], m_SpriteSheets["Zelda"]);

    //GameObject initial positions
    Vec2 position1 = { -5.0f, 0.0f };
    Vec2 position2 = { 0.0f, 5.0f };
    Vec2 position3 = { 0.0f, -5.0f };
    Vec2 position4 = { 5.0f, 0.0f };

    //GameObject Setting positions
    m_pGameObjects["Obj1"]->SetPosition(position2);
    m_pGameObjects["Obj2"]->SetPosition(position3);
    m_pGameObjects["Obj3"]->SetPosition(position4);
    m_pGameObjects["Obj4"]->SetPosition(position1);

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
        delete i.second;
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

    delete m_pPlayerScore;

    delete m_pPlayer1;

    delete m_pCar;
     
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
        i.second->Update(deltaTime);
    }

    m_pCar->Update(deltaTime);

    if (m_pCar->GetController() == nullptr)
    {
        m_pPlayer1->SetIsActive(true);
    }

    if (m_pPlayer1->GetIsActive() == false)
    {
        m_pPlayer1->SetPosition(m_pCar->GetPosition());
    }

    m_pPlayer1->Update(deltaTime);

    OnKeyEvent(deltaTime);

    //Test for Score display
    m_pPlayerScore->SetScore(abs(static_cast<int>(m_pPlayer1->GetPosition().x * 1000)));

    m_Cameras["Game"]->SetPosition(m_pPlayer1->GetPosition());
    
    //ImGui Code
    ImGui::DragFloat("Position X", &m_Position.x, 0.01f);
    ImGui::DragFloat("Position Y", &m_Position.y, 0.01f);

    if (ImGui::Button("Reset"))
    {
        m_Position.x = 0.0f;
        m_Position.y = 0.0f;
    }

    //Clipspace update
    glViewport(0, 0, m_rFramework.GetWindowWidth(), m_rFramework.GetWindowHeight());

    //Elapsed Time variable update
    m_ElapsedTime += deltaTime;

    for (auto& i : m_pGameObjects)
    {
        i.second->SetTimeElapsed(m_ElapsedTime);
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
        i.second->Draw(m_Cameras["Game"]);
    }

    m_pPlayer1->Draw(m_Cameras["Game"]);

    m_pCar->Draw(m_Cameras["Game"]);

    m_pPlayerScore->Draw(m_Cameras["HUD"]);

    m_pImGuiManager->EndFrame();
}

void Game::OnEvent(fw::Event* pEvent)
{
    m_pControllers[0]->OnEvent(pEvent);
}

void Game::OnKeyEvent(float deltaTime)
{
    m_pPlayer1->OnKeyEvent(m_pControllers[0], deltaTime);

    m_pCar->OnKeyEvent(deltaTime);

    if (m_pPlayer1->GetPosition().DistanceTo(m_pCar->GetPosition()) < 3.0f)
    {
        if (m_pControllers[0]->WasNewlyPressed(VirtualController::Action::Interact) && m_pPlayer1->GetIsActive() == true) // E
        {
            m_pPlayer1->SetIsActive(false);
            m_pCar->GetIn(m_pControllers[0]);
        }
    }
}
