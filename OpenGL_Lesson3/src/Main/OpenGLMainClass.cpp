#include "OpenGLMainClass.h"
#include "iostream"
#include "../Objects/Lights/BaseLight.h"
#include "../Objects/Components/ComponentLight.h"
#include <memory>

CKeyboardHandler        COpenGLMainClass::m_KeyboardHandler;
CMouseHandler           COpenGLMainClass::m_MouseHandler;
CDisplayHandler         COpenGLMainClass::m_DisplayHandler;
CTimeManager            COpenGLMainClass::m_TimeManager;
CSceneHandler           COpenGLMainClass::m_SceneHandler;
CCameraHandler          COpenGLMainClass::m_CameraHandler;
int                     COpenGLMainClass::m_FramesLimit = 60;
unsigned int            COpenGLMainClass::m_BiggestListNumber = 0;
std::list<unsigned int> COpenGLMainClass::m_FreeListNumbers;

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
    m_DisplayHandler.InitDisplay( GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE );
    glutSetOption( GLUT_MULTISAMPLE, 8 );
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
std::shared_ptr<CBaseLight> light = std::make_shared<CBaseLight>();
void COpenGLMainClass::Update()
{
    //if( !m_TimeManager.IsTimerEnded() )
    //    return;

    //std::shared_ptr<CComponentTransform> transform = light->GetComponent<CComponentLight>()->GetComponent<CComponentTransform>();
    //transform->m_Rot += CVector<float>{ 1, 0, 0 };
    //transform->a();

    m_SceneHandler.PreUpdate();
    m_CameraHandler.PreUpdate();
    m_SceneHandler.Update();
    m_CameraHandler.Update();
    m_SceneHandler.PostUpdate();
    m_CameraHandler.PostUpdate();
    glutPostRedisplay();
    //m_TimeManager.StartTimer( 1000.0 / m_FramesLimit );
}

void COpenGLMainClass::CreateScene()
{
    std::shared_ptr<CScene> scene1{ std::make_shared<CScene>() };

    scene1->AddObject( std::make_shared<CCube>( 200 ), CVector<float>{ +600, 0, 0 }, CVector<float>{ 0, 0, 0 } );
    scene1->AddObject( std::make_shared<CCube>( 200 ), CVector<float>{ -600, 0, 0 }, CVector<float>{ 0, 0, 0 } );
    scene1->AddObject( std::make_shared<CCube>( 200 ), CVector<float>{ 0, +600, 0 }, CVector<float>{ 0, 0, 0 } );
    scene1->AddObject( std::make_shared<CCube>( 200 ), CVector<float>{ 0, -600, 0 }, CVector<float>{ 0, 0, 0 } );
    scene1->AddObject( std::make_shared<CCube>( 200 ), CVector<float>{ 0, 0, +600 }, CVector<float>{ 0, 0, 0 } );
    scene1->AddObject( std::make_shared<CCube>( 200 ), CVector<float>{ 0, 0, -600 }, CVector<float>{ 0, 0, 0 } );

    

    scene1->AddObject( light, CVector<float>{ +600, 0, 0 }, CVector<float>{ 0, 0, 0 } );
    light->GetAddComponent<CComponentLight>( *light.get() )->SetLightPositionObject( std::make_shared<CCube>( 50 ) );

    //scene1->GetObjectByID( 0 )->AddComponent( std::make_shared<CComponentMesh3D<float>>( *(scene1->GetObjectByID( 0 ).get()) ) );
    //scene1->GetObjectByID( 0 )->GetComponent<CComponentLight>()->SetLightPositionObject( std::make_shared<CCube>( 50 ) );
    //scene1->GetObjectByID( 0 )->GetComponent<CComponentLight>()->m_LightPositionObject->AddComponent( std::make_shared<CComponentMesh3D<float>>( *(scene1->GetObjectByID( 0 )->GetComponent<CComponentLight>()->m_LightPositionObject.get()) ) );
    //scene1->GetObjectByID( 0 )->GetComponent<CComponentLight>()->ShowLightPosition( true );
    //std::dynamic_pointer_cast<CCube>( scene1->GetObjectByID( 0 )->GetComponent<CComponentLight>()->m_LightPositionObject )->MakeMesh();
    //std::dynamic_pointer_cast< CCube >( scene1->GetObjectByID( 0 ) )->MakeMesh();
    
    std::shared_ptr<CCameraObject> camera1( std::make_shared<CCameraObject>() );


    m_SceneHandler.AddScene( scene1 );
    m_CameraHandler.AddCamera( camera1 );

}
