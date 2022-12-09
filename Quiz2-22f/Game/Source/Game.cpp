#include "Framework.h"
#include "Game.h"
#include "VirtualController.h"
#include "Objects/GameObject.h"

Game::Game(fw::FWCore& core) : m_Framework(core)
{
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    m_ImGuiManager = new fw::ImGuiManager(&core);

    // Create controllers.
    for (int i = 0; i < 4; i++)
    {
        m_Controllers[i] = new VirtualController();
    }

    // Initialize our mesh.
    std::vector<fw::VertexFormat> values = {
        { { -0.5f, -0.5f }, 255, 255, 255, 255, {0.0f,0.0f} },
        { { 0.5f, -0.5f }, 255, 255, 255, 255, {1.0f,0.0f} },
        { { 0.0f,  0.5f }, 255, 255, 255, 255, {0.5f,1.0f} },
    };

    // Load the basic shader.
    m_Shaders["Basic"] = new fw::ShaderProgram( "Data/Shaders/Basic.vert", "Data/Shaders/Basic.frag" );
    m_Shaders["Texture"] = new fw::ShaderProgram( "Data/Shaders/Texture.vert", "Data/Shaders/Texture.frag" );

    // Create some meshes.
    m_Meshes["Triangle"] = new fw::Mesh( values, GL_TRIANGLES );

    // Create some textures.
    m_Textures["Default"] = new fw::Texture( "Data/Textures/windman.png" );

    // Create gameobjects.
    m_GameObjects.push_back( new GameObject( m_Meshes["Triangle"], m_Shaders["Texture"], m_Textures["Default"], vec2(0,0), 0, vec2(1,1) ) );
}

Game::~Game()
{
    for( int i=0; i<4; i++ )
    {
        delete m_Controllers[i];
    }

    for( GameObject* pObject : m_GameObjects )
    {
        delete pObject;
    }

    for( auto it : m_Meshes )
    {
        delete it.second;
    }

    for( auto it : m_Shaders )
    {
        delete it.second;
    }

    delete m_ImGuiManager;
}

void Game::StartFrame(float deltaTime)
{
    m_ImGuiManager->StartFrame( deltaTime );
    ImGui::ShowDemoWindow();

    m_EventManager->ProcessEvents();
}

void Game::OnEvent(fw::Event* pEvent)
{
    m_Controllers[0]->OnEvent( pEvent );
}

void Game::Update(float deltaTime)
{
    for( int i=0; i<m_GameObjects.size(); i++ )
    {
        m_GameObjects[i]->Update( deltaTime );
    }
}

void Game::Draw()
{
    glPointSize( 20 );
    glClearColor( 0, 0, 0.2f, 1 );
    glClear( GL_COLOR_BUFFER_BIT );

    for( int i=0; i<m_GameObjects.size(); i++ )
    {
        m_GameObjects[i]->Draw();
    }

    m_ImGuiManager->EndFrame();
}
