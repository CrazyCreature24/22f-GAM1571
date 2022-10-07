#include "CoreHeaders.h"
#include "GameCore.h"
#include "Event.h"
#include "EventManager.h"


namespace fw {



    EventManager::EventManager()
    {

    }

    EventManager::~EventManager()
    {

    }

    void EventManager::AddEvent(Event* pEvent)
    {
        m_Queue.push(pEvent);
    }

    void EventManager::ProcessEvents()
    {

    }

}