#include "MouseHandler.h"
#include "../Main/OpenGLMainClass.h"
#include <memory>
#include "../Objects/Components/ComponentMouse.h"

CMouseHandler::CMouseHandler()
    : m_MouseHold{ false }
{
    InitMaps();
}

int CMouseHandler::GetCurrentModifier()
{
    int modifiers = kmNONE;

    if( glutGetModifiers() & GLUT_ACTIVE_SHIFT ) modifiers |= kmSHIFT;
    if( glutGetModifiers() & GLUT_ACTIVE_CTRL )  modifiers |= kmCTRL;
    if( glutGetModifiers() & GLUT_ACTIVE_ALT )   modifiers |= kmALT;

    return modifiers;
}

void CMouseHandler::MakeMouseEvent( MouseKeyCodes key, MouseKeyStates state, int modifier, int x, int y )
{
    std::shared_ptr<CComponentMouse> component = COpenGLMainClass::m_CameraHandler.GetCameraByID( 0 )->GetComponent<CComponentMouse>();

    if( !component )
        return;
    
    component->KeyEvent( key, state, modifier, x, y );

    static int prevX = x;
    static int prevY = y;

    if( m_MouseHold ) {
        glutWarpPointer( x, y );
    }
    else {
        prevX = x;
        prevY = y;
    }
}

void CMouseHandler::PassiveMouseFunc( int x, int y )
{
    MakeMouseEvent( mkcNONE, mksNONE, GetCurrentModifier(), x, y );
}

void CMouseHandler::MotionFunc( int x, int y )
{
    MakeMouseEvent( mkcNONE, mksNONE, GetCurrentModifier(), x, y );
}

void CMouseHandler::MouseFunc( int button, int state, int x, int y )
{
    MouseKeyStates keyState = m_MouseKeyStatesConvertationMap.find( state )  != m_MouseKeyStatesConvertationMap.end() ? m_MouseKeyStatesConvertationMap[state]  : mksNONE;
    MouseKeyCodes  keyCode  = m_MouseKeyCodesConvertationMap.find( button )  != m_MouseKeyCodesConvertationMap.end()  ? m_MouseKeyCodesConvertationMap[button]  : mkcNONE;

    MakeMouseEvent( keyCode, keyState, GetCurrentModifier(), x, y );
}

void CMouseHandler::InitMaps()
{
    // Коды кнопок
    m_MouseKeyCodesConvertationMap = std::unordered_map<int, MouseKeyCodes> {
                                        { GLUT_LEFT_BUTTON,   mkcLEFT       },
                                        { GLUT_RIGHT_BUTTON,  mkcRIGHT      },
                                        { GLUT_MIDDLE_BUTTON, mkcMIDDLE     },
                                        { GLUT_WHEEL_UP,      mkcWHEEL_UP   },
                                        { GLUT_WHEEL_DOWN,    mkcWHEEL_DOWN }
                                    };

    // Коды состояний
    m_MouseKeyStatesConvertationMap = std::unordered_map<int, MouseKeyStates>{
                                        { GLUT_DOWN, mksDOWN },
                                        { GLUT_UP,   mksUP   },
                                    };

    // Коды типов курсора
    m_CursorTypeConvertationMap = std::unordered_map<CoursorType, int>{
                                        { ctRIGHT_ARROW,         GLUT_CURSOR_RIGHT_ARROW         },
                                        { ctLEFT_ARROW,          GLUT_CURSOR_LEFT_ARROW          },
                                        { ctINFO,                GLUT_CURSOR_INFO                },
                                        { ctDESTROY,             GLUT_CURSOR_DESTROY             },
                                        { ctHELP,                GLUT_CURSOR_HELP                },
                                        { ctCYCLE,               GLUT_CURSOR_CYCLE               },
                                        { ctSPRAY,               GLUT_CURSOR_SPRAY               },
                                        { ctWAIT,                GLUT_CURSOR_WAIT                },
                                        { ctTEXT,                GLUT_CURSOR_TEXT                },
                                        { ctCROSSHAIR,           GLUT_CURSOR_CROSSHAIR           },
                                        { ctUP_DOWN,             GLUT_CURSOR_UP_DOWN             },
                                        { ctLEFT_RIGHT,          GLUT_CURSOR_LEFT_RIGHT          },
                                        { ctTOP_SIDE,            GLUT_CURSOR_TOP_SIDE            },
                                        { ctBOTTOM_SIDE,         GLUT_CURSOR_BOTTOM_SIDE         },
                                        { ctLEFT_SIDE,           GLUT_CURSOR_LEFT_SIDE           },
                                        { ctRIGHT_SIDE,          GLUT_CURSOR_RIGHT_SIDE          },
                                        { ctTOP_LEFT_CORNER,     GLUT_CURSOR_TOP_LEFT_CORNER     },
                                        { ctTOP_RIGHT_CORNER,    GLUT_CURSOR_TOP_RIGHT_CORNER    },
                                        { ctBOTTOM_RIGHT_CORNER, GLUT_CURSOR_BOTTOM_RIGHT_CORNER },
                                        { ctBOTTOM_LEFT_CORNER,  GLUT_CURSOR_BOTTOM_LEFT_CORNER  },
                                        { ctINHERIT,             GLUT_CURSOR_INHERIT             },
                                        { ctNONE,                GLUT_CURSOR_NONE                },
                                        { ctFULL_CROSSHAIR,      GLUT_CURSOR_FULL_CROSSHAIR      },
                                    };
}

void CMouseHandler::SetCoursorType( CoursorType coursor )
{
    if( m_CursorTypeConvertationMap.find( coursor ) != m_CursorTypeConvertationMap.end() )
        glutSetCursor( m_CursorTypeConvertationMap[coursor] );
    else 
        glutSetCursor( GLUT_CURSOR_NONE );
}

void CMouseHandler::SetMouseHold( bool state )
{
    m_MouseHold = state;
}

void CMouseHandler::WarpCursor( int x, int y )
{
    glutWarpPointer( x, y );
}
