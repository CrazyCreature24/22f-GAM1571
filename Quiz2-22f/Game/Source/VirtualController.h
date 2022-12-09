#pragma once

class VirtualController
{
public:
    enum Action
    {
        Left  = 1 << 0,
        Right = 1 << 1,
        Jump  = 1 << 2,
    };

public:
    VirtualController();
    virtual ~VirtualController();

    void Reset();
    void StartFrame();
    void OnEvent(fw::Event* pEvent);

    bool IsHeld(Action action);
    bool WasNewlyPressed(Action action);
    bool WasNewlyReleased(Action action);

protected:
    unsigned int m_OldValues = 0;
    unsigned int m_Values = 0;
};
