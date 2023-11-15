#pragma once
#include <GL/freeglut.h>

#include "../Objects/Geometric/CCube.h"

class CDisplayHandler
{
public:
    enum ProjectTypes
    {
        ptPerspective = 0,
        ptOrtho,

        ptSIZE
    };
private:
    ProjectTypes m_ProjectType;

public:
    CDisplayHandler();

    void InitDisplay( int mode );
    void InitWindow( const char* name, int sizeX, int sizeY, int posX = 0, int posY = 0 );
    void DisplayFunc();
    void ReshapeFunc( int w, int h );
    void ShowWindow();

    bool IsBlendEnabled() const;
    void EnableBlend( bool state = true );
    void DisableBlend( bool state = true );

    bool IsLineSmoothEnabled() const;
    void EnableLineSmooth( bool state = true );
    void DisableLineSmooth( bool state = true );

    bool IsPolygonSmoothEnabled() const;
    void EnablePolygonSmooth( bool state = true );
    void DisablePolygonSmooth( bool state = true );

    bool IsDepthTestEnabled() const;
    void EnableDepthTest( bool state = true );
    void DisableDepthTest( bool state = true );


    void SetProjection( ProjectTypes pt );

};

