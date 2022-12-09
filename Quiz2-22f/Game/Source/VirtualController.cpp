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
    if( pEvent->GetType() == fw::InputEvent::GetStaticType() )
    {
        fw::InputEvent* pInputEvent = static_cast<fw::InputEvent*>( pEvent );

        int keyID = pInputEvent->GetID();

        if( pInputEvent->GetDevice() == fw::DeviceType::Keyboard )
        {
            if( pInputEvent->GetState() == fw::InputState::Pressed )
            {
                if( keyID == 'D' || keyID == VK_RIGHT ) { m_Values |= Action::Right; }
                if( keyID == 'A' || keyID == VK_LEFT )  { m_Values |= Action::Left; }
            }
            if( pInputEvent->GetState() == fw::InputState::Released )
            {
                if( keyID == 'D' || keyID == VK_RIGHT ) { m_Values &= ~Action::Right; }
                if( keyID == 'A' || keyID == VK_LEFT )  { m_Values &= ~Action::Left; }
            }
        }
    }
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
