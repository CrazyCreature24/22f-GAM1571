#pragma once

namespace fw {

    class GameCore
    {
    public:
        GameCore() {}
        virtual ~GameCore() {}
        virtual void StartFrame() = 0;
        virtual void Update() = 0;
        virtual void Draw() = 0;

    };

}