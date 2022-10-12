#pragma once
#include "Vec2.h"

class GameObject;

class Game : public fw::GameCore //This just shows the scope. If we wrapped the class in the fw namespace, then we would be adding the items to the namespace instead of jsut accessing it.
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
    fw::FWCore& m_Framework;

    fw::Mesh* m_Player; 
    int numVertsPlayer = 0;

    fw::Mesh* m_Enemy;
    int numVertsEnemy = 0;

    fw::ShaderProgram* m_pBasicShader = nullptr;
    fw::ShaderProgram* m_pEnemyShader = nullptr;

    //std::vector<GameObject*> m_pGameObjects;
    

    //For translation
    fw::Vec2 m_Position = { 0, 0 };
    
    //For color
    float m_r = 0;
    float m_g = 0;
    float m_b = 0;
    float m_a = 1;
    float m_Color[4] = { 1,1,1,1 };

    float m_elapsed = 0;

    //For scale
    fw::Vec2 m_Scale = { 0.5f, 0.5f };

    float m_ElapsedTime = 0;

    

    
};
