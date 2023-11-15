#include <iostream>
#include <chrono>
#include <GL/freeglut.h>
#define CUR Test1
#define D_T 30
using namespace std;

double deltaTime( std::chrono::system_clock::time_point prevTime )
{
	return std::chrono::duration_cast< std::chrono::milliseconds >( std::chrono::system_clock::now() - prevTime ).count();
}

namespace Test1
{
	void draw()
	{
		static auto prevTime = std::chrono::system_clock::now();
		static float angle = 0.0f;
		float dT = deltaTime( prevTime );
		glPushMatrix();
		glRotatef( angle, 1, 1, 1 );
		glutWireCube( 100 );
		glPopMatrix();

		glPushMatrix();
		glRotatef( -angle, 1, 1, 1 );
		glutWireCube( 50 );
		glPopMatrix();

		if( dT < D_T )
			return;
		
		angle += 0.1f * dT;
		angle = fmod( angle, 360 );
		prevTime = std::chrono::system_clock::now();
	}
};


void init()
{
	glClearColor( 0.0, 0.0, 0.0, 0.0 );
	glShadeModel( GL_SMOOTH );
}



void display()
{
	glClear( GL_COLOR_BUFFER_BIT );
	glLoadIdentity();
	gluLookAt( 0, 0, 500, 0, 0, 0, 0, 1, 0 );
	CUR::draw();

	glFlush();
}

void update( int )
{
	display();
	glutTimerFunc( 25, update, 0 );
}

void reshape( int w, int h )
{
	glViewport( 0, 0, w, h );
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-w, w, -h, h, -500, 500);
	//glFrustum( -0.5, 0.5, -0.5, 0.5, 1, 1000 );
	gluPerspective( 30, (double)w/h, 1, 1000 );
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main( int argc, char** argv )
{
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB );
	glutInitWindowSize( 500, 500 );
	glutInitWindowPosition( 100, 100 );
	glutCreateWindow( "Lesson 1" );
	glutDisplayFunc( display );
	glutReshapeFunc( reshape );
	glutTimerFunc( 25, update, 0 );
	glutMainLoop();
	return 0;
}