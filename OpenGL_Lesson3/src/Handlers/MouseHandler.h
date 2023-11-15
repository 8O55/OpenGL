#pragma once
#include <GL/freeglut.h>
#include <unordered_map>

class CMouseHandler
{
#define GLUT_WHEEL_UP   3
#define GLUT_WHEEL_DOWN 4

public:
    enum MouseKeyCodes
    {
        mkcNONE = 0,

        mkcLEFT,
        mkcMIDDLE,
        mkcRIGHT,
        mkcWHEEL_UP,
        mkcWHEEL_DOWN,

        mkcSIZE,
    };

    enum MouseKeyStates
    {
        mksNONE = 0,

        mksDOWN,
        mksUP,

        mksSIZE,
    };

    enum KeyModifiers
    {
        kmNONE = 0x0000,
        kmSHIFT = 0x0001,
        kmCTRL = 0x0002,
        kmALT = 0x0004,
    };

    enum CoursorType
    {
        ctNONE = 0,
        ctRIGHT_ARROW,
        ctLEFT_ARROW,
        ctINFO,
        ctDESTROY,
        ctHELP,
        ctCYCLE,
        ctSPRAY,
        ctWAIT,
        ctTEXT,
        ctCROSSHAIR,
        ctUP_DOWN,
        ctLEFT_RIGHT,
        ctTOP_SIDE,
        ctBOTTOM_SIDE,
        ctLEFT_SIDE,
        ctRIGHT_SIDE,
        ctTOP_LEFT_CORNER,
        ctTOP_RIGHT_CORNER,
        ctBOTTOM_RIGHT_CORNER,
        ctBOTTOM_LEFT_CORNER,
        ctINHERIT,
        ctFULL_CROSSHAIR,
    };

private:
    
    std::unordered_map<int, MouseKeyCodes>  m_MouseKeyCodesConvertationMap;
    std::unordered_map<int, MouseKeyStates> m_MouseKeyStatesConvertationMap;
    std::unordered_map<CoursorType, int>    m_CursorTypeConvertationMap;
    
public:
    CMouseHandler();

    int GetCurrentModifier();
    void InitMaps();

    void MakeMouseEvent( MouseKeyCodes key, MouseKeyStates state, int modifier, int x, int y );

    void PassiveMouseFunc( int x, int y );
    void MotionFunc( int x, int y );
    void MouseFunc( int button, int state, int x, int y );

    void SetCoursorType( CoursorType type );
};

