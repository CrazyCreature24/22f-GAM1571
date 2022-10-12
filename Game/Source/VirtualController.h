#pragma once


class VirtualController
{
public:
    enum Action
    {
        Left = 1 << 0, //Bitwise shift = 0x0001
        Right = 1 << 1, //Bitwise shift = 0x0010
        Jump = 1 << 2 //Bitwise shift = 0x0100
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