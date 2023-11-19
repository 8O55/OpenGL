#pragma once
#include <GL/freeglut.h>
#include "../Handlers/KeyboardHandler.h"
#include "../Handlers/MouseHandler.h"
#include "../Handlers/DisplayHandler.h"
#include "../Handlers/SceneHandler.h"
#include "../Handlers/CameraHandler.h"
#include "../Utility/TimeManager.h"
#include <list>

class COpenGLMainClass
{
private:
    static int m_FramesLimit;
    static CTimeManager m_TimeManager;

    static std::list<unsigned int> m_FreeListNumbers;
    static unsigned int m_BiggestListNumber;
public:
    COpenGLMainClass( int* argc, char** argv );

    static void SetFuncs();
    static void Start();
    static void Update();

    static void CreateScene();

    static CKeyboardHandler m_KeyboardHandler;
    static CMouseHandler    m_MouseHandler;
    static CDisplayHandler  m_DisplayHandler;
    static CSceneHandler    m_SceneHandler;
    static CCameraHandler   m_CameraHandler;

    // «арезервировать номер отображаемого списка OpenGL
    static unsigned int ObtainListNumber()
    {
        if( m_FreeListNumbers.size() ) {
            unsigned int number = *m_FreeListNumbers.begin();
            m_FreeListNumbers.pop_front();
            return number;
        }
        
        return ++m_BiggestListNumber;
    }

    static void FreeListNumber( unsigned int listNumber )
    {/*
        if( listNumber != m_BiggestListNumber )
            m_FreeListNumbers.push_back( listNumber );
        else*/
            --m_BiggestListNumber;
    }

};

