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
    virtual void OnKeyEvent(float deltaTime) override;

protected:
    fw::ImGuiManager* m_pImGuiManager = nullptr;
    fw::FWCore& m_rFramework;

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

    bool bHasHead = true;


    std::map<string, ShaderProgram*> m_Shaders;
    std::map<string, Mesh*> m_Meshes;
    
};
