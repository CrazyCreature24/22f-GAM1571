#include "CoreHeaders.h"
#include "GameCore.h"
#include "Event.h"
#include "EventManager.h"


namespace fw {



    EventManager::EventManager(GameCore* game) :
        m_pGame(game)
    {

    }

    EventManager::~EventManager()
    {
        while (!m_Queue.empty())
        {
            Event* temp = m_Queue.front();
            m_Queue.pop();
            delete temp;
        }
    }

    void EventManager::AddEvent(Event* pEvent)
    {
        m_Queue.push(pEvent);
    }

    void EventManager::ProcessEvents()
    {
        while (!m_Queue.empty())
        {
            Event* temp = m_Queue.front();
            m_Queue.pop();
            m_pGame->OnEvent(temp);

            delete temp;
        }
    }

}