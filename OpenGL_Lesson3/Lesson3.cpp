#include <iostream>
#include "src/Main/OpenGLMainClass.h"

COpenGLMainClass* oglMainPtr;

void update( int )
{
    oglMainPtr->Update();
    glutTimerFunc( 1, update, 1 );
}

int main( int argc, char** argv )
{
    COpenGLMainClass oglMain{ &argc, argv };
    oglMainPtr = &oglMain;
    glutTimerFunc( 25, update, 1 );
    oglMain.Start();
    return 0;
}