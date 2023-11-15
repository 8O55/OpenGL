#pragma once
#include "Component.h"
#include "../../Handlers/KeyboardHandler.h"
#include "../../Utility/Queue.h"

class CComponentKeyboard : public CComponent
{
public:
    using KeyCode      = CKeyboardHandler::KeysCodes;
    using KeyModifier = CKeyboardHandler::KeyModifiers;
protected:
    struct Event
    {
        KeyCode key;
        int modifier;
        int x;
        int y;

        Event( KeyCode key, int modifier, int x, int y )
            : key{key}
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
    CComponentKeyboard( CBaseEntity& parent )
        : CComponent{ parent }
    {
        
    };

    virtual ~CComponentKeyboard() = default;

    virtual void Update() override
    {
        CComponent::Update();
    }

    void KeyEvent( KeyCode key, int modifier, int x, int y )
    {
        m_Queue.PushEvent( std::make_shared<Event>( key, modifier, x, y ) );
    };
};

