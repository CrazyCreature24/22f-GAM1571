#include "CoreHeaders.h"
#include "EventManager.h"
#include "GameCore.h"
#include "Events/Events.h"

namespace fw {

EventManager::EventManager(GameCore* pGame)
    : m_Game( pGame )
{
}

EventManager::~EventManager()
{
    while( !m_Events.empty() )
    {
        Event* pEvent = m_Events.front();
        m_Events.pop();

        delete pEvent;
    }
}

void EventManager::AddEvent(Event* pEvent)
{
    m_Events.push( pEvent );
}

void EventManager::ProcessEvents()
{
    while( !m_Events.empty() )
    {
        Event* pEvent = m_Events.front();
        m_Events.pop();

        m_Game->OnEvent( pEvent );

        delete pEvent;
    }
}

}
