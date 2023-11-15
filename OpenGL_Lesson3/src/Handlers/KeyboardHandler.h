#pragma once
#include <GL/freeglut.h>

class CKeyboardHandler
{
public:
    enum KeysCodes
    {
        kcNONE = 0,

        kcW,
        kcS,
        kcD,
        kcA,

        kcSIZE,
    };

    enum KeyModifiers
    {
        kmNONE  = 0x0000,
        kmSHIFT = 0x0001,
        kmCTRL  = 0x0002,
        kmALT   = 0x0004,
    };

public:
    CKeyboardHandler();

    void KeyDispatcher( unsigned char key, int x, int y );
};


