#pragma once
#include "DataTypes.h"


class GameObject;
class VirtualController;
class fw::Texture;
class fw::SpriteSheet;
class fw::Camera;
class ScoreDisplay;
class Player;
class Car;
class Tilemap;




class Game : public fw::GameCore 
{
public:
    Game(fw::FWCore& core);
    virtual ~Game();

    virtual void StartFrame(float deltaTime) override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
    virtual void OnEvent(fw::Event* pEvent) override;
    virtual void OnKeyEvent(float deltaTime) override;

protected:
    fw::ImGuiManager* m_pImGuiManager = nullptr;
    fw::FWCore& m_rFramework;

    std::map<string, GameObject*> m_pGameObjects;

    static const int c_NumControllers = 4;
    VirtualController* m_pControllers[c_NumControllers] = { nullptr };

    float m_ElapsedTime = 0;

    std::map<string, ShaderProgram*> m_Shaders;
    std::map<string, Mesh*> m_Meshes;
    std::map<string, fw::Texture*> m_Textures;
    std::map<string, SpriteSheet*> m_SpriteSheets;
    std::map<string, SpriteInfo*> m_SpriteInfos;
    std::map<string, Camera*> m_Cameras;
    
    ScoreDisplay* m_pPlayerScore = nullptr;

    Player* m_pPlayer1 = nullptr;

    Car* m_pCar = nullptr;

    Tilemap* m_pTilemap = nullptr;
    
};
