#pragma once

namespace fw {

class Event;
class EventManager;

class GameCore
{
public:
    GameCore();
    virtual ~GameCore();

    virtual void StartFrame(float deltaTime) = 0;
    virtual void OnEvent(Event* pEvent) = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Draw() = 0;

    EventManager* GetEventManager() { return m_EventManager; }

protected:
    EventManager* m_EventManager = nullptr;
};

} // namespace fw
