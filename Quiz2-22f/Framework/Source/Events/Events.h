#pragma once

namespace fw {

enum class DeviceType
{
    Keyboard,
    Mouse,
};

enum class InputState
{
    Pressed,
    Released,
};

class Event
{
public:
    Event() {}
    virtual ~Event() {}

    virtual const char* GetType() = 0;
};

class InputEvent : public Event
{
public:
    InputEvent(DeviceType device, InputState state, int id)
        : m_Device(device), m_State(state), m_ID(id) {}
    ~InputEvent() {}

    virtual const char* GetType() override { return GetStaticType(); }
    static const char* GetStaticType() { return "InputEvent"; }

    DeviceType GetDevice() { return m_Device; }
    InputState GetState() { return m_State; }
    int GetID() { return m_ID; }

protected:
    DeviceType m_Device;
    InputState m_State;
    int m_ID;
};

}