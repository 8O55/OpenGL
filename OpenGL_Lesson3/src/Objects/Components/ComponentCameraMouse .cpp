#include "ComponentCameraMouse.h"
#include "../../Main/OpenGLMainClass.h"
#include "ComponentTransform.h"
#include "../Object.h"

void CComponentCameraMouse::MouseMove( int deltaX, int deltaY )
{
    if( m_CurTransform.expired() || !IsKeyActive( KeyCode::mkcLEFT ) ) {
        COpenGLMainClass::m_MouseHandler.SetCoursorType( CoursorType::ctLEFT_ARROW );
        //COpenGLMainClass::m_MouseHandler.SetMouseHold( false );
        return;
    }

    CVector<float>& rot = m_CurTransform.lock()->m_Rot;
    rot += CVector<float>{ static_cast<float>(deltaY)* m_Sensivity, static_cast<float>(deltaX)* m_Sensivity, 0 };
    COpenGLMainClass::m_MouseHandler.SetCoursorType( CoursorType::ctNONE );
    //COpenGLMainClass::m_MouseHandler.SetMouseHold( true );
    //COpenGLMainClass::m_MouseHandler.WarpCursor( m_PrevX, m_PrevY );
    //m_CurrX = m_PrevX;
    //m_CurrY = m_PrevY;
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