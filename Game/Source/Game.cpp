#include "Framework.h"
#include "GameObject.h"
#include "VirtualController.h"
#include "ScoreDisplay.h"
#include "Player.h"
#include "AI/AI.h"
#include "Car.h"
#include "Tilemap.h"
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

    std::vector<VertexFormat> boxVerts;
    boxVerts.push_back(VertexFormat(-0.5f, -0.5f, 100, 255, 255, 255, 0, 0));
    boxVerts.push_back(VertexFormat(-0.5f, 0.5f, 255, 255, 255, 255, 0, 1));
    boxVerts.push_back(VertexFormat(0.5f, 0.5f, 255, 255, 255, 255, 1, 1));
    boxVerts.push_back(VertexFormat(0.5f, 0.5f, 255, 255, 255, 255, 1, 1));
    boxVerts.push_back(VertexFormat(-0.5f, -0.5f, 255, 255, 255, 255, 0, 0));
    boxVerts.push_back(VertexFormat(0.5f, -0.5f, 100, 255, 255, 255, 1, 0));

    std::vector<VertexFormat> ground;
    ground.push_back(VertexFormat(-10, -10, 0, 100, 0, 255, 0, 0));
    ground.push_back(VertexFormat(-10, -5, 0, 100, 0, 255, 0, 1));
    ground.push_back(VertexFormat(10, -5, 0, 100, 0, 255, 1, 1));
    ground.push_back(VertexFormat(10, -5, 0, 100, 0, 255, 1, 1));
    ground.push_back(VertexFormat(-10, -10, 0, 100, 0, 255, 0, 0));
    ground.push_back(VertexFormat(10, -10, 0, 100, 0, 255, 1, 0));


    //Meshes
    m_Meshes["Box"] = new Mesh(boxVerts, GL_TRIANGLES);
    m_Meshes["Box2"] = new Mesh(boxVerts, GL_TRIANGLES);
    m_Meshes["Ground"] = new Mesh(ground, GL_TRIANGLES);

    //Shaders
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

    //Tilemap
    m_pTilemap = new Tilemap(m_Meshes["Box2"], m_Shaders["Box"], m_Textures["Zelda"], m_SpriteSheets["Zelda"]);

    //ScoreDisplay Decleration
    m_pPlayerScore = new ScoreDisplay(m_Meshes["Box"], m_Shaders["Box"], m_Textures["Numbers"]);

    //Player
    m_pPlayer1 = new Player(m_Meshes["Box"], m_Shaders["Box"], m_Textures["Zelda"], m_SpriteSheets["Zelda"], m_pTilemap);

    //Car
    m_pCar = new Car(m_Meshes["Box"], m_Shaders["Box"], m_Textures["Car"]);
    m_pCar->SetPosition(Vec2(2.0f, 5.0f));

    //Enemy AI
    m_pEnemy = new AI(m_Meshes["Box"], m_Shaders["Box"], m_Textures["Zelda"], m_SpriteSheets["Zelda"], m_pTilemap);

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

    delete m_pTilemap;

    delete m_pEnemy;
     
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
    //Calling all the different updates
    m_Cameras["Game"]->UpdateAspect();
    m_Cameras["HUD"]->UpdateAspect();

    m_pCar->Update(deltaTime);

    m_pPlayer1->Update(deltaTime);

    m_pEnemy->Update(deltaTime);

    //Set the Player Sprite to be active if the Player ejects from the car
    if (m_pCar->GetController() == nullptr)
    {
        m_pPlayer1->SetIsActive(true);
    }

    //Sets the player position to the Cars position so the Camera follows the Car
    if (m_pPlayer1->GetIsActive() == false)
    {
        m_pPlayer1->SetPosition(m_pCar->GetPosition());
    }

    //This makes it so the Camera follows the player
    m_Cameras["Game"]->SetPosition(m_pPlayer1->GetPosition());

    //Calls all the key inputs from the different object
    OnKeyEvent(deltaTime);

    //Test for Score display
    m_pPlayerScore->SetScore(abs(static_cast<int>(m_pPlayer1->GetPosition().x * 1000)));
    
    //Clipspace update
    glViewport(0, 0, m_rFramework.GetWindowWidth(), m_rFramework.GetWindowHeight());

    //ImGui Code Example
    {
        //ImGui::DragFloat("Position X", &m_Position.x, 0.01f);
        //ImGui::DragFloat("Position Y", &m_Position.y, 0.01f);

        /*if (ImGui::Button("Reset"))
        {
            m_Position.x = 0.0f;
            m_Position.y = 0.0f;
        }*/
    }
}

void Game::Draw()
{
    //Clear screen every frame
    glClearColor(0, 0, 0.2f, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    //Draws all the different objects
    m_pTilemap->Draw(m_Cameras["Game"]);

    m_pPlayer1->Draw(m_Cameras["Game"]);

    m_pEnemy->Draw(m_Cameras["Game"]);

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

    //If the player is within the set distance to the Car, The key press allows them to "Get in" the car
    if (m_pPlayer1->GetPosition().DistanceTo(m_pCar->GetPosition()) < 3.0f)
    {
        if (m_pControllers[0]->WasNewlyPressed(VirtualController::Action::Interact) && m_pPlayer1->GetIsActive() == true) // E
        {
            m_pPlayer1->SetIsActive(false);
            m_pCar->GetIn(m_pControllers[0]);
        }
    }
}
