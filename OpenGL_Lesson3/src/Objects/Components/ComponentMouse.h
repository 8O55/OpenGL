#pragma once
#include "Component.h"
#include "../../Handlers/MouseHandler.h"
#include "../../Utility/Queue.h"

class CComponentMouse : public CComponent
{
public:
    using KeyCode      = CMouseHandler::MouseKeyCodes;
    using KeyState     = CMouseHandler::MouseKeyStates;
    using KeyModifier  = CMouseHandler::KeyModifiers;
    using CoursorType  = CMouseHandler::CoursorType;
protected:
    struct Event
    {
        KeyCode key;
        KeyState state;
        int modifier;
        int x;
        int y;

        Event( KeyCode key, KeyState state, int modifier, int x, int y )
            : key{key}
            , state{state}
            , modifier{modifier}
            , x{x}
            , y{y}
        { }
    };

    CQueue<std::shared_ptr<Event>> m_Queue;
    virtual void ProcessKeyEvent( Event& event )
    {

    }
public:
    CComponentMouse( CBaseEntity& parent )
        : CComponent{ parent }
    {
        
    };

    virtual ~CComponentMouse() = default;

    virtual void Update() override
    {
        CComponent::Update();
    }

    void KeyEvent( KeyCode key, KeyState state, int modifier, int x, int y )
    {
        m_Queue.PushEvent( std::make_shared<Event>( key, state, modifier, x, y ) );
    };
};

