#pragma once
#include <GL/freeglut.h>
#include "../Handlers/KeyboardHandler.h"
#include "../Handlers/MouseHandler.h"
#include "../Handlers/DisplayHandler.h"
#include "../Handlers/SceneHandler.h"
#include "../Handlers/CameraHandler.h"
#include "../Utility/TimeManager.h"

class COpenGLMainClass
{
private:
    static int m_FramesLimit;
    static CTimeManager m_TimeManager;
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
};

