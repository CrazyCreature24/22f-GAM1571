#pragma once
#include "Math/Vec2.h"

namespace fw {

    class Event
    {
    public:
        Event();
        virtual ~Event();
        virtual const char* GetType() = 0;

    };
    



    enum class DeviceType
    {
        Keyboard,
        Mouse
    };

    enum class InputState
    {
        Pressed,
        Released
    };


    class InputEvent : public Event
    {
    public:
        InputEvent(DeviceType dType, InputState iState, WPARAM wParam);

        virtual const char* GetType() override { return GetStaticType(); }
        static const char* GetStaticType() { return "InputEvent"; }

        //Getters
        DeviceType GetDeviceType();
        InputState GetInputState();
        int GetID();
        Vec2 GetPosition();

    protected:
        DeviceType m_DeviceType;
        InputState m_InputState;
        int m_ID = 0;
        Vec2 m_Pos;

    };

  


}