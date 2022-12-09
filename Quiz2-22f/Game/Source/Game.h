#pragma once

#include "DataTypes.h"

class VirtualController;
class GameObject;

class Game : public fw::GameCore
{
public:
    Game(fw::FWCore& core);
    virtual ~Game();

    virtual void StartFrame(float deltaTime) override;
    virtual void Game::OnEvent(fw::Event* pEvent) override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;

protected:
    fw::FWCore& m_Framework;
    fw::ImGuiManager* m_ImGuiManager = nullptr;

    VirtualController* m_Controllers[4] = { nullptr };

    std::map<std::string, fw::ShaderProgram*> m_Shaders;
    std::map<std::string, fw::Mesh*> m_Meshes;
    std::map<std::string, fw::Texture*> m_Textures;

    std::vector<GameObject*> m_GameObjects;
};
