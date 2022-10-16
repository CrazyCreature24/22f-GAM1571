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

    if (pEvent->GetType() == fw::InputEvent::GetStaticType())
    {
        fw::InputEvent* pInputEvent = static_cast<fw::InputEvent*>(pEvent);

        int keyID = pInputEvent->GetID();

        if (pInputEvent->GetDeviceType() == fw::DeviceType::Keyboard)
        {
            if (pInputEvent->GetInputState() == fw::InputState::Pressed)
            {
                if (keyID == 'D' || keyID == VK_RIGHT) { m_Values |= Right; }
                if (keyID == 'A' || keyID == VK_LEFT) {m_Values |= Left;}
                if (keyID == 'W' || keyID == VK_UP) { m_Values |= Up; }
                if (keyID == 'S' || keyID == VK_DOWN) { m_Values |= Down; }
                if (keyID == 'K') { m_Values |= ScaleUpX; }
                if (keyID == 'H') { m_Values |= ScaleDownX; }
                if (keyID == 'U') { m_Values |= ScaleUpY; }
                if (keyID == 'J') { m_Values |= ScaleDownY; }
                if (keyID == '1') { m_Values |= AddVert; }
                if (keyID == '2') { m_Values |= RebuildVBO; }
            }

            if (pInputEvent->GetInputState() == fw::InputState::Released)
            {
                if (keyID == 'D' || keyID == VK_RIGHT) { m_Values &= ~Right;}
                if (keyID == 'A' || keyID == VK_LEFT) { m_Values &= ~Left; }
                if (keyID == 'W' || keyID == VK_UP) { m_Values &= ~Up; }
                if (keyID == 'S' || keyID == VK_DOWN) { m_Values &= ~Down; }
                if (keyID == 'K') { m_Values &= ~ScaleUpX; }
                if (keyID == 'H') { m_Values &= ~ScaleDownX; }
                if (keyID == 'U') { m_Values &= ~ScaleUpY; }
                if (keyID == 'J') { m_Values &= ~ScaleDownY; }
                if (keyID == '1') { m_Values &= ~AddVert; }
                if (keyID == '2') { m_Values &= ~RebuildVBO; }
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
