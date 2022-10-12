#include "Framework.h"
#include "VirtualController.h"

VirtualController::VirtualController()
{

}

VirtualController::~VirtualController()
{

}

void VirtualController::Reset()
{
    m_Values = 0;
}

void VirtualController::StartFrame()
{
    m_OldValues = m_Values;
}

void VirtualController::OnEvent(fw::Event* pEvent)
{

}

bool VirtualController::IsHeld(Action action)
{
    return m_Values & action;
}

bool VirtualController::WasNewlyPressed(Action action)
{
    bool wasPressed = m_OldValues & action;
    bool isPressed = m_Values & action;

    return wasPressed == false && isPressed == true;
}

bool VirtualController::WasNewlyReleased(Action action)
{
    bool wasPressed = m_OldValues & action;
    bool isPressed = m_Values & action;

    return wasPressed == true && isPressed == false;
}
