#pragma once

namespace fw {

    class GameCore
    {
    public:
        GameCore() {}
        virtual ~GameCore() {}
        virtual void StartFrame( float deltaTime ) = 0;
        virtual void Update(float deltaTime) = 0;
        virtual void Draw() = 0;

    };

}