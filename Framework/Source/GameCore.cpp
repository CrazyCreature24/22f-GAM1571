#include "CoreHeaders.h"
#include "Events/EventManager.h"
#include "GameCore.h"


namespace fw
{
    GameCore::GameCore()
    {
        m_pEventManager = new EventManager();
    }

    GameCore::~GameCore()
    {
        delete m_pEventManager;
    }
}