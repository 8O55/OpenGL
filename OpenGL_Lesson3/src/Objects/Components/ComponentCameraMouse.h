#pragma once
#include "ComponentMouse.h"
#include "ComponentTransform.h"

class CComponentCameraMouse : public CComponentMouse
{
protected:
    int m_PrevX;
    int m_PrevY;

    int m_CurrX;
    int m_CurrY;

    int m_ActiveKeysMsk;
    int m_ActiveModifiersMsk;

    std::weak_ptr<CComponentTransform> m_CurTransform;

public:
    float m_Sensivity;

    CComponentCameraMouse( CBaseEntity& parent )
        : CComponentMouse{ parent }
        , m_PrevX{ 0 }
        , m_PrevY{ 0 }
        , m_ActiveKeysMsk{ 0 }
        , m_ActiveModifiersMsk{ 0 }
        , m_Sensivity{ 0.5f }
    {     
    };

    virtual ~CComponentCameraMouse() = default;

    void MouseMove( int deltaX, int deltaY );
    
    void SetKeyActive( KeyCode key, bool state )
    {
        if( state )
            m_ActiveKeysMsk |=  ( 1 << static_cast<int>( key ) );
        else
            m_ActiveKeysMsk &= ~( 1 << static_cast<int>( key ) );
    }

    void SetModifiersMsk( int msk )
    {
        m_ActiveModifiersMsk = msk;
    }

    void ClearActiveKeys()
    {
        m_ActiveKeysMsk = 0;
    }

    void ClearActiveModifiers()
    {
        m_ActiveModifiersMsk = 0;
    }

    bool IsKeyActive( KeyCode key )
    {
        return key == KeyCode::mkcNONE ? m_ActiveKeysMsk != 0 : m_ActiveKeysMsk & 1 << key;
    }

    bool isModifierActive( KeyModifier modifier )
    {
        return modifier != KeyModifier::kmNONE ? m_ActiveModifiersMsk!= 0 : m_ActiveModifiersMsk & modifier;
    }

    virtual void ProcessKeyEvent( Event& event ) override;

    virtual void Update() override
    {
        CComponentMouse::Update();

        if( m_Queue.Size() ) {
            while( m_Queue.Size() ) {
                if( m_Queue.Event() )
                    ProcessKeyEvent( *( m_Queue.Event()->get() ) );

                m_Queue.RemoveFirst();
            }
        }
    }
};

