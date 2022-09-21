#pragma once


class Game : public fw::GameCore
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
