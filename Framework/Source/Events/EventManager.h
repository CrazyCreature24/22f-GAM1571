#pragma once

namespace fw {

    class Event;
    class GameCore;

    class EventManager
    {
    public:
        EventManager();
        virtual ~EventManager();
        void AddEvent(Event* pEvent);
        void ProcessEvents();


    protected:
        std::queue<Event*> m_Queue;
        GameCore* m_pGame = nullptr;


    };
}