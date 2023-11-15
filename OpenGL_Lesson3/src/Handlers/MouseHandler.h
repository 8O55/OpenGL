#pragma once
#include <GL/freeglut.h>

class CMouseHandler
{
public:
    CMouseHandler();

    void PassiveMouseFunc( int x, int y );
    void MotionFunc( int x, int y );
    void MouseFunc( int button, int state, int x, int y );
};

