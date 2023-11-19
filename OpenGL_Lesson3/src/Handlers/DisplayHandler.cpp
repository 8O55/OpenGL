#include "DisplayHandler.h"
#include <iostream>
#include <memory>
#include "../Main/OpenGLMainClass.h"

#define ENABLE_POLYGON_SMOOTH   0
#define ENABLE_LINE_SMOOT       1
#define ENABLE_DEPTH_TEST       1
#define ENABLE_BLENT            1
#define ENABLE_POLYGON_OFFSET   1
#define ENABLE_CULL_FACE        1

CDisplayHandler::CDisplayHandler()
    : m_ProjectType{ ptOrtho }
    {}

void CDisplayHandler::InitDisplay( int mode )
{
    glutInitDisplayMode( mode );
}

void CDisplayHandler::InitWindow( const char* name, int sizeX, int sizeY, int posX, int posY )
{
    glutInitWindowSize( sizeX, sizeY );
    glutInitWindowPosition( posX, posY );
    glutCreateWindow( name );

#if ENABLE_DEPTH_TEST
    EnableDepthTest();
#else
    DisableDepthTest();
#endif

#if ENABLE_BLENT
    EnableBlend();
#else
    DisableBlend();
#endif

#if ENABLE_LINE_SMOOT
    EnableLineSmooth();
#else
    DisableLineSmooth();
#endif

#if ENABLE_POLYGON_SMOOTH
    EnablePolygonSmooth();
#else
    DisablePolygonSmooth();
#endif

#if ENABLE_POLYGON_OFFSET
    EnablePolygonOffset();
#else
    DisablePolygonOffset();
#endif

#if ENABLE_CULL_FACE
    EnableCullFace();
#else
    DisableCullFace();
#endif

    glClearColor( 1.0, 1.0, 1.0, 0.0 );
    glShadeModel( GL_SMOOTH );
}

void CDisplayHandler::DisplayFunc()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glLoadIdentity();
    glColor3f( 1.0, 0.0, 0.0 );
    //gluLookAt( 0, 1000, 100, 0, 0, 0, 0, 1, 0 );
    //glRotatef( 45, 1.0, 1.0, 0.0 );
    COpenGLMainClass::m_CameraHandler.Draw();
    COpenGLMainClass::m_SceneHandler.Draw();
    glFlush();
}

void CDisplayHandler::ReshapeFunc( int w, int h )
{
    double z = std::fmax( w, h );
    glViewport( 0, 0, w, h );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    switch( m_ProjectType ) {
        case CDisplayHandler::ptPerspective:
            gluPerspective( 60, ( double )w / h, 2, 100000 );
            break;
        case CDisplayHandler::ptOrtho:
            glOrtho( -w, w, -h, h, -z, z );
            break;
        default:
            break;
    }

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
}

void CDisplayHandler::ShowWindow()
{
    glutShowWindow();
}

bool CDisplayHandler::IsBlendEnabled() const
{
    GLboolean isEnabled;
    glGetBooleanv( GL_BLEND, &isEnabled );
    return static_cast<bool>( isEnabled );
}

void CDisplayHandler::EnableBlend( bool state )
{
    if( state == IsBlendEnabled() )
        return;

    if( state ) {
        glEnable( GL_BLEND );
        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    }
    else {
        glDisable( GL_BLEND );
    }
}

void CDisplayHandler::DisableBlend( bool state )
{
    EnableBlend( !state );
}

bool CDisplayHandler::IsLineSmoothEnabled() const
{
    GLboolean isEnabled;
    glGetBooleanv( GL_LINE_SMOOTH, &isEnabled );
    return static_cast< bool >( isEnabled );
}

void CDisplayHandler::EnableLineSmooth( bool state )
{
    if( state == IsLineSmoothEnabled() )
        return;

    if( state ) {
        glEnable( GL_LINE_SMOOTH );
        glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
    }
    else {
        glDisable( GL_LINE_SMOOTH );
    }
}

void CDisplayHandler::DisableLineSmooth( bool state )
{
    EnableLineSmooth( !state );
}

bool CDisplayHandler::IsPolygonSmoothEnabled() const
{
    GLboolean isEnabled;
    glGetBooleanv( GL_POLYGON_SMOOTH, &isEnabled );
    return static_cast< bool >( isEnabled );
}

void CDisplayHandler::EnablePolygonSmooth( bool state )
{
    if( state == IsPolygonSmoothEnabled() )
        return;

    if( state )
    {
        glEnable( GL_POLYGON_SMOOTH );
        glHint( GL_POLYGON_SMOOTH_HINT, GL_NICEST );
    }
    else {
        glDisable( GL_POLYGON_SMOOTH );
    }
}

void CDisplayHandler::DisablePolygonSmooth( bool state )
{
    EnablePolygonSmooth( !state );
}

bool CDisplayHandler::IsDepthTestEnabled() const
{
    GLboolean isEnabled;
    glGetBooleanv( GL_DEPTH_TEST, &isEnabled );
    return static_cast< bool >( isEnabled );
}

void CDisplayHandler::EnableDepthTest( bool state )
{
    if( state == IsDepthTestEnabled() )
        return;

    if( state )
        glEnable( GL_DEPTH_TEST );
    else
        glDisable( GL_DEPTH_TEST );
}

void CDisplayHandler::DisableDepthTest( bool state )
{
    EnableDepthTest( !state );
}

bool CDisplayHandler::IsPolygonOffsetEnabled() const
{
    GLboolean isEnabled;
    glGetBooleanv( GL_POLYGON_OFFSET_LINE, &isEnabled );
    return static_cast< bool >( isEnabled );
}

void CDisplayHandler::EnablePolygonOffset( bool state )
{
    if( state == IsPolygonOffsetEnabled() )
        return;

    if( state )
        glEnable( GL_POLYGON_OFFSET_LINE );
    else
        glDisable( GL_POLYGON_OFFSET_LINE );
}

void CDisplayHandler::DisablePolygonOffset( bool state )
{
    EnablePolygonOffset( !state );
}

bool CDisplayHandler::IsCullFaceEnabled() const
{
    GLboolean isEnabled;
    glGetBooleanv( GL_CULL_FACE, &isEnabled );
    return static_cast< bool >( isEnabled );
}

void CDisplayHandler::EnableCullFace( bool state )
{
    if( state == IsCullFaceEnabled() )
        return;

    if( state )
        glEnable( GL_CULL_FACE );
    else
        glDisable( GL_CULL_FACE );
}

void CDisplayHandler::DisableCullFace( bool state )
{
    EnablePolygonOffset( !state );
}


void CDisplayHandler::SetProjection( ProjectTypes pt )
{
    if( pt == m_ProjectType )
        return;

    m_ProjectType = pt;
    ReshapeFunc( glutGet( GLUT_WINDOW_WIDTH ), glutGet( GLUT_WINDOW_HEIGHT ) );
}
