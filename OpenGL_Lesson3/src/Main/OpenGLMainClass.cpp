#include "OpenGLMainClass.h"
#include "iostream"
#include "../Objects/Components/ComponentLight.h"
#include <memory>

CKeyboardHandler COpenGLMainClass::m_KeyboardHandler;
CMouseHandler    COpenGLMainClass::m_MouseHandler;
CDisplayHandler  COpenGLMainClass::m_DisplayHandler;
CTimeManager     COpenGLMainClass::m_TimeManager;
CSceneHandler    COpenGLMainClass::m_SceneHandler;
CCameraHandler   COpenGLMainClass::m_CameraHandler;
int              COpenGLMainClass::m_FramesLimit = 60;

static void keyDispathcer( unsigned char key, int x, int y )
{
    COpenGLMainClass::m_KeyboardHandler.KeyDispatcher( key, x, y);
}

static void passiveMouseFunc( int x, int y )
{
    COpenGLMainClass::m_MouseHandler.PassiveMouseFunc( x, y );
}

static void mouseFunc( int button, int state, int x, int y )
{
    COpenGLMainClass::m_MouseHandler.MouseFunc( button, state, x ,y );
}

static void motionFunc( int x, int y )
{
    COpenGLMainClass::m_MouseHandler.MotionFunc( x, y );
}

static void displayFunc()
{
    COpenGLMainClass::m_DisplayHandler.DisplayFunc();
}

static void reshapeFunc( int w, int h )
{
    COpenGLMainClass::m_DisplayHandler.ReshapeFunc( w, h);
}

static void updateFunc( int )
{

    glutTimerFunc( 25, updateFunc, 1 );
}

COpenGLMainClass::COpenGLMainClass( int* argc, char** argv )
{
    glutInit( argc, argv );
    m_DisplayHandler.InitDisplay( GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH );
    m_DisplayHandler.InitWindow( "Lesson 3", 500, 500, 500, 500 );
    SetFuncs();
    m_DisplayHandler.SetProjection( CDisplayHandler::ptPerspective );
    m_DisplayHandler.ShowWindow();
    CreateScene();
}

void COpenGLMainClass::SetFuncs()
{
    glutKeyboardFunc( keyDispathcer );
    glutMouseFunc( mouseFunc );
    glutMotionFunc( motionFunc );
    glutPassiveMotionFunc( passiveMouseFunc );
    glutDisplayFunc( displayFunc );
    glutReshapeFunc( reshapeFunc );
}

void COpenGLMainClass::Start()
{
    glutMainLoop();
}

void COpenGLMainClass::Update()
{
    if( !m_TimeManager.IsTimerEnded() )
        return;

    m_SceneHandler.PreUpdate();
    m_CameraHandler.PreUpdate();
    m_SceneHandler.Update();
    m_CameraHandler.Update();
    glutPostRedisplay();
    m_TimeManager.StartTimer( 1000.0 / m_FramesLimit );
}

void COpenGLMainClass::CreateScene()
{
    std::shared_ptr<CScene> scene1{ std::make_shared<CScene>() };

    scene1->AddObject( std::make_shared<CCube>( 200 ) );
    //scene1->GetObjectByID( 0 )->AddComponent( std::make_shared<CComponentMesh3D<float>>( *(scene1->GetObjectByID( 0 ).get()) ) );
    scene1->GetObjectByID( 0 )->GetComponent<CComponentLight>()->SetLightPositionObject( std::make_shared<CCube>( 50 ) );
    //scene1->GetObjectByID( 0 )->GetComponent<CComponentLight>()->m_LightPositionObject->AddComponent( std::make_shared<CComponentMesh3D<float>>( *(scene1->GetObjectByID( 0 )->GetComponent<CComponentLight>()->m_LightPositionObject.get()) ) );
    scene1->GetObjectByID( 0 )->GetComponent<CComponentLight>()->ShowLightPosition( true );
    //std::dynamic_pointer_cast<CCube>( scene1->GetObjectByID( 0 )->GetComponent<CComponentLight>()->m_LightPositionObject )->MakeMesh();
    //std::dynamic_pointer_cast< CCube >( scene1->GetObjectByID( 0 ) )->MakeMesh();
    std::shared_ptr<CCameraObject> camera1( std::make_shared<CCameraObject>() );


    m_SceneHandler.AddScene( scene1 );
    m_CameraHandler.AddCamera( camera1 );

}
