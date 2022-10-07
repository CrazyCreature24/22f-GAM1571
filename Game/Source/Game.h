#pragma once


class Game : public fw::GameCore //This just shows the scope. If we wrapped the class in teh fw namespace, then we would be adding the items to the namespace instead of jsut accessing it.
{
public:
    Game(fw::FWCore& core);
    virtual ~Game();

    virtual void StartFrame(float deltaTime) override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;

protected:

    fw::FWCore& m_Framework;

    GLuint m_vbo = 0; //Turn off for assignment work

    //fw::Mesh* m_mesh; //Assignment

    fw::ShaderProgram* m_pBasicShader = nullptr;
    fw::ShaderProgram* m_pTentacles = nullptr; //Turn off for assignment work

    fw::ImGuiManager* m_pImGuiManager = nullptr;

    //For translation
    float m_x = 0;
    float m_y = 0;
    
    //For color
    float m_r = 0;
    float m_g = 0;
    float m_b = 0;
    float m_a = 1;
    float m_Color[4] = { 1,1,1,1 };

    float m_elapsed = 0;

    //For scale
    float m_scaleX = 1;
    float m_scaleY = 1;

    float m_ElapsedTime = 0;
};
