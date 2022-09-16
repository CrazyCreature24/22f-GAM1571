#pragma once

namespace fw {

    class Game : public GameCore
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
}