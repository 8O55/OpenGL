#include <iostream>
#include <GL/freeglut.h>
#include <chrono>
#define _USE_MATH_DEFINES
#include <math.h>

#define D_T 30
#define ENABLE_POLYGON_SMOOTH   0
#define ENABLE_LINE_SMOOT       1
#define ENABLE_DEPTH_TEST       1
#define ENABLE_BLENT            1
#define ENABLE_LIGHTING         1
#define SHOW_LIGHTS             1
#define DIST_BORDER             2000
#define MOUSE_ROTATING_MULT     4
#define DIST_SPEED_MULT         10.0
#define MOVEMENT_SPEED_MULT     10.0

using namespace std;

float theta = 0, beta = 0, dist = 750;
float rotatingSpeed = 2.0, distSpeed = 1.0;
float movementSpeed = 2.0;

float x_0 = 0, y_0 = 0, z_0 = 0;

double deltaTime( std::chrono::system_clock::time_point prevTime )
{
    return std::chrono::duration_cast< std::chrono::milliseconds >( std::chrono::system_clock::now() - prevTime ).count();
}

void enableGLFuncs()
{
#if ENABLE_DEPTH_TEST
    glEnable( GL_DEPTH_TEST );
#endif

#if ENABLE_BLENT
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
#endif

#if ENABLE_LINE_SMOOT
    glEnable( GL_LINE_SMOOTH );
    glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
#endif

#if ENABLE_POLYGON_SMOOTH
    glEnable( GL_POLYGON_SMOOTH );
    glHint( GL_POLYGON_SMOOTH_HINT, GL_NICEST );
#endif

#if ENABLE_LIGHTING
    glEnable( GL_LIGHTING );
    glEnable( GL_COLOR_MATERIAL );
#endif
}

namespace Lighting
{
    GLfloat light0Posistion[] = { 0.0, 0.0, 200, 1.0 };
    GLfloat spot_direction[] = { 0.0, 0.0, -1.0 };
    GLfloat light0Deffuse[]   = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light0ModelviewMatrix[16];

    void setLight()
    {
        glLightfv( GL_LIGHT0, GL_POSITION,             light0Posistion );
        glLightfv( GL_LIGHT0, GL_DIFFUSE,              light0Deffuse );
        glLightf(  GL_LIGHT0, GL_SPOT_CUTOFF,          45.0 );
        glLightfv( GL_LIGHT0, GL_SPOT_DIRECTION,       spot_direction );
        glLightf(  GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0 );
        glLightf(  GL_LIGHT1, GL_SPOT_EXPONENT,        2.0 );


        glGetFloatv( GL_MODELVIEW_MATRIX, light0ModelviewMatrix );


        glEnable( GL_LIGHT0 );
    }

    void showLight()
    {
    #if SHOW_LIGHTS
        glColor3f( 0.0, 1.0, 0.0 );
        glPushMatrix();
        glLoadMatrixf( light0ModelviewMatrix );
        glTranslatef( light0Posistion[0], light0Posistion[1], light0Posistion[2] );
        glutWireCone( 10, 50, 5, 2 );
        glPopMatrix();
    #endif
    }

    void rotateLight( float angle, float x, float y, float z )
    {
        glPushMatrix();
        glLoadMatrixf( light0ModelviewMatrix );
        glRotatef( angle, x, y, z );
        glLightfv( GL_LIGHT0, GL_POSITION, light0Posistion );
        glLightfv( GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction );
        glGetFloatv( GL_MODELVIEW_MATRIX, light0ModelviewMatrix );
        glPopMatrix();
    }

    void updateLight()
    {
        glLightfv( GL_LIGHT0, GL_POSITION, light0Posistion );

        glGetFloatv( GL_MODELVIEW_MATRIX, light0ModelviewMatrix );
    }
};

namespace Mouse
{
#define GLUT_WHEEL_UP   3
#define GLUT_WHEEL_DOWN 4

    bool isLeftBtnHold = false;
    bool isRightBtnHold = false;
    bool isMiddleBtnHold = false;

    int prevX, prevY;

    void mouse( int button, int state, int x, int y )
    {
        switch( button ) {
            case GLUT_LEFT_BUTTON:
                isLeftBtnHold = !isLeftBtnHold;
                break;
            case GLUT_RIGHT_BUTTON:
                isRightBtnHold = !isRightBtnHold;
                break;
            case GLUT_MIDDLE_BUTTON:
                isMiddleBtnHold = !isMiddleBtnHold;
                prevX = x;
                prevY = y;
                break;
            case GLUT_WHEEL_UP:
                dist -= glutGetModifiers() == GLUT_ACTIVE_SHIFT ? distSpeed * DIST_SPEED_MULT
                    : distSpeed;
                if( dist < 0 )
                    dist = 0;
                glutPostRedisplay();
                break;
            case GLUT_WHEEL_DOWN:
                dist += glutGetModifiers() == GLUT_ACTIVE_SHIFT ? distSpeed * DIST_SPEED_MULT
                    : distSpeed;
                if( dist > DIST_BORDER )
                    dist = DIST_BORDER;
                glutPostRedisplay();
                break;
        }
    }

    void mouseCursor( int x, int y )
    {
        if( !isMiddleBtnHold ) {
            glutSetCursor( GLUT_CURSOR_LEFT_ARROW );
            return;
        }

        glutSetCursor( GLUT_CURSOR_NONE );

        if( glutGetModifiers() == GLUT_ACTIVE_SHIFT ) {

            float moveX = prevX - x;
            float moveY = prevY - y;

            float deltaTheta = atan( moveX / dist );
            float deltaBeta = atan( moveY / dist );

            theta += deltaTheta * 180 * MOUSE_ROTATING_MULT / M_PI;
            beta -= deltaBeta * 180 * MOUSE_ROTATING_MULT / M_PI;

            if( theta < 0 ) theta = 360;
            if( beta < 0 ) beta = 360;

            if( theta > 360 ) theta = 0;
            if( beta > 360 ) beta = 0;

            x = glutGet( GLUT_WINDOW_WIDTH ) / 2;
            y = glutGet( GLUT_WINDOW_HEIGHT ) / 2;

            prevX = x;
            prevY = y;

            glutWarpPointer( x, y );

            glutPostRedisplay();
            return;
        }

        if( glutGetModifiers() == GLUT_ACTIVE_CTRL ) {
            float moveX = prevX - x;
            float moveY = prevY - y;

            float deltaPos[] = { moveX, moveY, 0 };

            x_0 -= deltaPos[0] * cos( theta * M_PI / 180 );
            y_0 += deltaPos[1];
            z_0 += deltaPos[0] * sin( theta * M_PI / 180 );

            x = glutGet( GLUT_WINDOW_WIDTH ) / 2;
            y = glutGet( GLUT_WINDOW_HEIGHT ) / 2;

            prevX = x;
            prevY = y;

            glutWarpPointer( x, y );

            glutPostRedisplay();
            return;
        }
    }
};

void setMaterial()
{
    GLfloat mat0Deffuse[] = { 1.0, 1.0, 1.0, 1.0 };

    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat0Deffuse );
}

void drawCube( int a, int x, int y, int z )
{
    float hA = a / 2.0;
    glPushMatrix();
    glTranslatef( x, y, z );
    //glEnable( GL_CULL_FACE );
    glFrontFace( GL_CCW );

    for( auto i = 0; i < 6; i++ ){
        glPushMatrix();
        if( i < 4 )
            glRotatef( 90 * i, 0, 1, 0 );
        else
            glRotatef( 90 + 180 * ( i - 4 ), 1, 0, 0 );
        glBegin( GL_POLYGON );
        glColor4f( 1.0, 0.0, 0.0, 1.0 );
        glNormal3f( 0.0, 0.0, 1.0 );
        glVertex3f( +hA, +hA, +hA );
        glVertex3f( -hA, +hA, +hA );
        glVertex3f( -hA, -hA, +hA );
        glVertex3f( +hA, -hA, +hA );
        glEnd();
        glPopMatrix();
    }

    for( auto i = 0; i < 6; i++ ){
        glPushMatrix();
        if( i < 4 )
            glRotatef( 90 * i, 0, 1, 0 );
        else
            glRotatef( 90 + 180 * ( i - 4 ), 1, 0, 0 );
        glBegin( GL_LINE_STRIP );
        glColor3f( 0.0, 0.0, 0.0 );
        glLineWidth( 2.0 );
        //glPolygonOffset( 25.0, 1.0 );
        glVertex3f( +hA, +hA, +hA );
        glVertex3f( -hA, +hA, +hA );
        glVertex3f( -hA, -hA, +hA );
        glVertex3f( +hA, -hA, +hA );
        glEnd();
        glPopMatrix();
    }
    glPopMatrix();
}

void reshape( int w, int h )
{
    int z = fmax( w, h );
    glViewport( 0, 0, w, h );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    //glOrtho( -w, w, -h, h, -z, z );
    gluPerspective( 30, ( double )w / h, 1, DIST_BORDER );
    //glFrustum( -w, w, -h, h, 0.1, 10000 );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
}

void init()
{
    int w = glutGet( GLUT_WINDOW_WIDTH );
    int h = glutGet( GLUT_WINDOW_HEIGHT );

    glClearColor( 1.0, 1.0, 1.0, 0.0 );
    reshape( w, h );
    enableGLFuncs();
    Lighting::setLight();
    setMaterial();
    glShadeModel( GL_SMOOTH );
}

void display()
{

    static auto prevTime = std::chrono::system_clock::now();
    float dT = deltaTime( prevTime );
    if( dT < D_T )
        return;
    static float angle = 0;
    angle += 2;
    if( angle >= 360 )
        angle = 0;
    glDepthMask( 1 );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glLoadIdentity();
    gluLookAt( dist * sin( theta * M_PI / 180 ) * cos( beta * M_PI / 180 ) + x_0,
               dist * sin( beta * M_PI / 180 ) + y_0,
               dist * cos( beta * M_PI / 180 ) * cos( theta * M_PI / 180 ) + z_0,
               x_0, y_0, z_0,
               0, 1, 0 );
    drawCube( 100, 0, 0, 0 );
    drawCube( 100, +100, 0, 0 );
    drawCube( 100, -100, 0, 0 );
    drawCube( 100, 0, +100, 0 );
    drawCube( 100, 0, -100, 0 );

    Lighting::updateLight();
    Lighting::rotateLight( angle, 1.0, 0.0, 0.0 );
    Lighting::showLight();
    glFlush();
    prevTime = std::chrono::system_clock::now();
}

void keyboard( unsigned char key, int x, int y )
{
    if( glutGetModifiers() == GLUT_ACTIVE_SHIFT )
    {

        switch( key ) {
            case 'd':
            case 'D':
                x_0 -= movementSpeed * cos( theta * M_PI / 180 ) * MOVEMENT_SPEED_MULT;
                z_0 += movementSpeed * sin( theta * M_PI / 180 ) * MOVEMENT_SPEED_MULT;
                glutPostRedisplay();
                break;

            case 'a':
            case 'A':
                x_0 += movementSpeed * cos( theta * M_PI / 180 ) * MOVEMENT_SPEED_MULT;
                z_0 -= movementSpeed * sin( theta * M_PI / 180 ) * MOVEMENT_SPEED_MULT;
                glutPostRedisplay();
                break;

            case 'w':
            case 'W':
                y_0 += movementSpeed * MOVEMENT_SPEED_MULT;
                glutPostRedisplay();
                break;

            case 's':
            case 'S':
                y_0 -= movementSpeed * MOVEMENT_SPEED_MULT;
                glutPostRedisplay();
                break;

            case 27:
                glutLeaveMainLoop();
                break;
        }
    }
    else {
        switch( key ) {
            case 'd':
            case 'D':
                theta += rotatingSpeed;
                theta = fmod( theta, 360.0 );
                glutPostRedisplay();
                break;

            case 'a':
            case 'A':
                theta -= rotatingSpeed;
                if( theta < 0 )
                    theta = 360;
                glutPostRedisplay();
                break;

            case 'w':
            case 'W':
                beta += rotatingSpeed;
                beta = fmod( beta, 360.0 );
                glutPostRedisplay();
                break;

            case 's':
            case 'S':
                beta -= rotatingSpeed;
                if( beta < 0 )
                    beta = 360;
                glutPostRedisplay();
                break;

            case 27:
                glutLeaveMainLoop();
                break;
        }
    }
}

void update( int )
{
    glutPostRedisplay();
    glutTimerFunc( 30, update, 1 );
}

int main( int argc, char** argv )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH );
    //glutSetOption( GLUT_MULTISAMPLE, 8 );
    glutInitWindowSize( 500, 500 );
    glutInitWindowPosition( 500, 500 );
    glutCreateWindow( "Lesson 2" );
    init();
    glutDisplayFunc( display );
    glutReshapeFunc( reshape );
    glutKeyboardFunc( keyboard );
    glutMouseFunc( Mouse::mouse );
    glutMotionFunc( Mouse::mouseCursor );
    glutPassiveMotionFunc( Mouse::mouseCursor );
    glutTimerFunc( 30, update, 1 );
    glutShowWindow();
    glutMainLoop();
    return 0;
}
