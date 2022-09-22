#pragma once


class Game : public fw::GameCore //This just shows the scope. If we wrapped the class in teh fw namespace, then we would be adding the items to the namespace instead of jsut accessing it.
{
public:
    Game();
    virtual ~Game();

    virtual void StartFrame() override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;

protected:
    GLuint m_vbo = 0;

    fw::ShaderProgram* m_pBasicShader = nullptr;

    float m_x;
    float m_y;
};
