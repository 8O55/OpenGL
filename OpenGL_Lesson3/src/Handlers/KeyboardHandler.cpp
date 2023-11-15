#include "KeyboardHandler.h"
#include "../Main/OpenGLMainClass.h"
#include <memory>
#include "../Objects/Components/ComponentKeyboard.h"

CKeyboardHandler::CKeyboardHandler()
{
    
}

void CKeyboardHandler::KeyDispatcher( unsigned char key, int x, int y )
{
    std::shared_ptr<CComponentKeyboard> component = COpenGLMainClass::m_CameraHandler.GetCameraByID( 0 )->GetComponent<CComponentKeyboard>();

    if( !component )
        return;

    int modifiers = kmNONE;

    if( glutGetModifiers() & GLUT_ACTIVE_SHIFT ) modifiers |= kmSHIFT;
    if( glutGetModifiers() & GLUT_ACTIVE_CTRL )  modifiers |= kmCTRL;
    if( glutGetModifiers() & GLUT_ACTIVE_ALT )   modifiers |= kmALT;

    if( GLUT_ACTIVE_SHIFT )

    switch( key ) {
        case 'd':
        case 'D':
            component->KeyEvent( kkcD, modifiers, x, y );
            break;

        case 'a':
        case 'A':
            component->KeyEvent( kkcA, modifiers, x, y );
            break;

        case 'w':
        case 'W':
            component->KeyEvent( kkcW, modifiers, x, y );
            break;

        case 's':
        case 'S':
            component->KeyEvent( kkcS, modifiers, x, y );
            break;

        case 27:
            component->KeyEvent( kkcNONE, modifiers, x, y );
            break;
    }
}
