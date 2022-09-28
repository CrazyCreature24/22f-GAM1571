#pragma once


class Game : public fw::GameCore //This just shows the scope. If we wrapped the class in teh fw namespace, then we would be adding the items to the namespace instead of jsut accessing it.
{
public:
    Game(fw::FWCore& core);
    virtual ~Game();

    virtual void StartFrame() override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;

protected:

    fw::FWCore& m_Framework;

    GLuint m_vbo = 0;

    fw::ShaderProgram* m_pBasicShader = nullptr;

    //For translation
    float m_x = 0;
    float m_y = 0;
    
    //For color
    float m_r = 0;
    float m_g = 0;
    float m_b = 0;
    float m_a = 1;

    float m_elapsed = 0;

    //For scale
    float m_scaleX = 0.5f;
    float m_scaleY = 0.5f;
};
