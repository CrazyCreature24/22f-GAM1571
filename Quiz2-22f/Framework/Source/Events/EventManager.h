#pragma once

namespace fw {

class Event;
class GameCore;

class EventManager
{
public:
    EventManager(GameCore* pGame);
    virtual ~EventManager();

    void AddEvent(Event* pEvent);
    void ProcessEvents();

protected:
    GameCore* m_Game = nullptr;
    std::queue<Event*> m_Events;
};

}