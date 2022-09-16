#pragma once


class Game : public fw::GameCore
{
public:
    Game();
    virtual ~Game();

    virtual void StartFrame() override;
    virtual void Update() override;
    virtual void Draw() override;

protected:
    GLuint m_vbo;
};
