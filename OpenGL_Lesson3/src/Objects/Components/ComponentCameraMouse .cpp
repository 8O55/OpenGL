#include "ComponentCameraMouse.h"
#include "../../Main/OpenGLMainClass.h"
#include "ComponentTransform.h"
#include "../Object.h"

void CComponentCameraMouse::MouseMove( int deltaX, int deltaY )
{
    if( m_CurTransform.expired() || !IsKeyActive( KeyCode::mkcLEFT ) ) {
        COpenGLMainClass::m_MouseHandler.SetCoursorType( CoursorType::ctLEFT_ARROW );
        return;
    }

    m_CurTransform.lock()->m_Rot += CVector<float>{ static_cast< float >( -deltaY )* m_Sensivity, static_cast< float >( deltaX )* m_Sensivity, 0 };

    COpenGLMainClass::m_MouseHandler.SetCoursorType( CoursorType::ctNONE );
}

void CComponentCameraMouse::ProcessKeyEvent( Event& event )
{
    m_CurrX = event.x;
    m_CurrY = event.y;

    std::shared_ptr<CComponentTransform> transform;

    if( !transform )
        transform = GetAddParentComponent<CComponentTransform, CObject>( m_Parent );

    if( !transform )
        transform = GetAddParentComponent<CComponentTransform, CComponent>( m_Parent );

    m_CurTransform = transform;

    SetModifiersMsk( event.modifier );

    if( event.state != KeyState::mksNONE && event.key != KeyCode::mkcNONE )
        SetKeyActive( event.key, event.state == KeyState::mksDOWN );

    if( m_CurrY != m_PrevX || m_CurrY != m_PrevY ) {
        MouseMove( m_PrevX - m_CurrX, m_PrevY - m_CurrY );
        m_PrevX = m_CurrX;
        m_PrevY = m_CurrY;
    }

    ClearActiveModifiers();

    m_CurTransform.reset();
}