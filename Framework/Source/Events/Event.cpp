#include "CoreHeaders.h"
#include "Event.h"

namespace fw {



    Event::Event()
    {

    }

    Event::~Event()
    {

    }





    InputEvent::InputEvent(DeviceType dType, InputState iState, WPARAM wParam) :
        m_DeviceType(dType),
        m_InputState(iState),
        m_ID(wParam)
    {

    }

    DeviceType InputEvent::GetDeviceType()
    {
        return m_DeviceType;
    }

    InputState InputEvent::GetInputState()
    {
        return m_InputState;
    }

    int InputEvent::GetID()
    {
        return m_ID;
    }

    Vec2 InputEvent::GetPosition()
    {
        return m_Pos;
    }

}