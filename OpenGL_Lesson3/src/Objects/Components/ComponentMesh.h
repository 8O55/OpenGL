#pragma once
#include <GL/freeglut.h>
#include "Component.h"
#include "../../Utility/Primitives/TrianglePrimitive.h"
#include <vector>
#include <initializer_list>

template<typename T = float>
class CComponentMesh2D : public CComponent
{
public:
    std::vector<CTriangle2D<T>> m_Triangles;
public:
    CComponentMesh2D( CBaseEntity& parent, std::initializer_list<std::initializer_list<std::initializer_list<T>>> lst )
        : CComponent( parent )
    {
        for( auto triangleList : lst )
            m_Triangles.push_back( CTriangle2D<T>{ triangleList } );
    }

    // Унаследовано через CComponent
    virtual void Update() override {};

    void Draw()
    {
        glPushMatrix();

        for( const CTriangle2D<T>& triangle : m_Triangles ) {
            glBegin( GL_POLYGON );

            glVertex2f( triangle.m_p1.X(), triangle.m_p1.Y() );
            glVertex2f( triangle.m_p2.X(), triangle.m_p2.Y() );
            glVertex2f( triangle.m_p3.X(), triangle.m_p3.Y() );

            glEnd();
        }

        glPopMatrix();
    }
};

template<typename T = float>
class CComponentMesh3D : public CComponent
{
public:
    std::vector<CTriangle3D<T>> m_Triangles;

    std::vector<CTriangle3D<T>> m_CurTriangles;
    float m_LineWidth;
public:
    CComponentMesh3D( CBaseEntity& parent )
        : CComponent( parent )
        , m_LineWidth{ 2.0f } {}

    CComponentMesh3D( CBaseEntity& parent, std::initializer_list<std::initializer_list<std::initializer_list<T>>> lst )
        : CComponentMesh3D( parent )
    {
        if( lst.size() )
            AddTriangles( lst );
    }

    void AddTriangles( std::initializer_list<std::initializer_list<std::initializer_list<T>>> lst )
    {
        for( auto triangleList : lst )
            m_Triangles.push_back( CTriangle3D<T>{ triangleList } );
    }

    void AddTriangle( CTriangle3D<T> triangle )
    {
        m_Triangles.push_back( triangle );
    }

    void Clear()
    {
        m_Triangles.clear();
    }

    void SetLineWidth( float width ) { m_LineWidth = width; };

    // Унаследовано через CComponent
    virtual void Update() override
    {
        CComponent::Update();

        m_CurTriangles = m_Triangles;
        std::shared_ptr<CComponentTransform> ptr;

        //CComponent* obj = dynamic_cast< CComponent* >( m_Parent );


        if( dynamic_cast< CObject* >( &m_Parent ) != NULL )
            ptr = dynamic_cast< CObject* >( &m_Parent )->GetComponent<CComponentTransform>();

        if( dynamic_cast< CComponent* >( &m_Parent ) != NULL )
            ptr = dynamic_cast< CComponent* >( &m_Parent )->GetComponent<CComponentTransform>();

        if( ptr ) {
            for( CTriangle3D<T>& triangle : m_CurTriangles )
                triangle.RotMovScale( ptr->m_Rot, ptr->m_Move, ptr->m_Scale );
        }
    };

    void DrawTriangle( const CTriangle3D<T>& triangle )
    {
        glLineWidth( m_LineWidth );
        glBegin( GL_LINE_LOOP );

        glColor3f( triangle.m_p1.Color().GetRGB().R, triangle.m_p1.Color().GetRGB().G, triangle.m_p1.Color().GetRGB().B );
        glVertex3f( triangle.m_p1.X(), triangle.m_p1.Y(), triangle.m_p1.Z() );

        glColor3f( triangle.m_p2.Color().GetRGB().R, triangle.m_p2.Color().GetRGB().G, triangle.m_p2.Color().GetRGB().B );
        glVertex3f( triangle.m_p2.X(), triangle.m_p2.Y(), triangle.m_p2.Z() );

        glColor3f( triangle.m_p3.Color().GetRGB().R, triangle.m_p3.Color().GetRGB().G, triangle.m_p3.Color().GetRGB().B );
        glVertex3f( triangle.m_p3.X(), triangle.m_p3.Y(), triangle.m_p3.Z() );

        glEnd();
    }

    void Draw()
    {
        CComponent::Draw();

        glPushMatrix();
        for( const CTriangle3D<T>& triangle : m_CurTriangles ) {
            DrawTriangle( triangle );
        }
        glPopMatrix();
    }
};

