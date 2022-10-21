#pragma once
#include "DataTypes.h"

class GameObject;
class VirtualController;



class Game : public fw::GameCore 
{
public:
    Game(fw::FWCore& core);
    virtual ~Game();

    virtual void StartFrame(float deltaTime) override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
    virtual void OnEvent(fw::Event* pEvent) override;

protected:
    fw::ImGuiManager* m_pImGuiManager = nullptr;
    fw::FWCore& m_rFramework;

    Mesh* m_pPlayerMesh;
    Mesh* m_pEnemyMesh;
    Mesh* m_pHeadlessPlayerMesh;

    ShaderProgram* m_pBasicShader = nullptr;
    ShaderProgram* m_pEnemyShader = nullptr;

    std::vector<GameObject*> m_pGameObjects;

    static const int c_NumControllers = 4;
    VirtualController* m_pControllers[c_NumControllers] = { nullptr };

    Vec2 m_Resolution = { 0,0 };
    float m_ElapsedTime = 0;

    //For translation
    Vec2 m_Position = { 0, 0 };
    
    //For color
    float m_Color[4] = { 1,1,1,1 };
    float m_ColorChangeTimer = 0;

    //For scale
    Vec2 m_Scale = { 0.5f, 0.5f };



    Mesh* m_pBox;

    ShaderProgram* m_pBoxShader = nullptr;

    bool bHasHead = true;

    
};
