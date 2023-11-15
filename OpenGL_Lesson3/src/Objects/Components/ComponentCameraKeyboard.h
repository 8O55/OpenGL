#pragma once
#include "ComponentKeyboard.h"
#include "ComponentTransform.h"

class CComponentCameraKeyboard : public CComponentKeyboard
{
public:
    using KeyCode = CKeyboardHandler::KeysCodes;

public:
    CComponentCameraKeyboard( CBaseEntity& parent )
        : CComponentKeyboard{ parent }
    {
        
    };

    virtual ~CComponentCameraKeyboard() = default;

    virtual void ProcessKeyEvent( Event& event ) override
    {
        std::shared_ptr<CComponentTransform> transform;

        if(!transform)
            transform = GetAddParentComponent<CComponentTransform, CObject>( m_Parent );
        
        if(!transform)
            transform = GetAddParentComponent<CComponentTransform, CComponent>( m_Parent );

        switch( event.key ) {
            case KeyCode::kcA:
                if( event.modifier & KeyModifier::kmSHIFT )
                    transform->m_Rot[1]  += 10.0;
                else
                    transform->m_Move[0] -= 10.0;
                transform->Update();
                break;
            case KeyCode::kcD:
                if( event.modifier & KeyModifier::kmSHIFT )
                    transform->m_Rot[1]  -= 10.0;
                else
                    transform->m_Move[0] += 10.0;
                transform->Update();
                break;
            case KeyCode::kcW:
                if( event.modifier & KeyModifier::kmSHIFT )
                    transform->m_Rot[0]  += 10.0;
                else
                    transform->m_Move[2] -= 10.0;
                transform->Update();
                break;
            case KeyCode::kcS:
                if( event.modifier & KeyModifier::kmSHIFT )
                    transform->m_Rot[0]  -= 10.0;
                else
                    transform->m_Move[2] += 10.0;
                transform->Update();
                break;
            default:
                break;
        }
    }

    virtual void Update() override
    {
        CComponentKeyboard::Update();

        if( m_Queue.Size() ) {
            while( m_Queue.Size() ) {
                if( m_Queue.Event() )
                    ProcessKeyEvent( *( m_Queue.Event()->get() ) );

                m_Queue.RemoveFirst();
            }
        }
    }
};

