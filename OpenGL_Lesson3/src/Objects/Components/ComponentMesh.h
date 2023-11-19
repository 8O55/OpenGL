#pragma once
#include <GL/freeglut.h>
#include "Component.h"
#include "../../Utility/Primitives/TrianglePrimitive.h"
#include "../../Main/OpenGLMainClass.h"
#include <vector>
#include <initializer_list>

template<typename T = float>
class CComponentMesh2D : public CComponent
{
public:
    enum MeshType
    {
        mtWired = 0,
        mtSolid,
    };

private:
    int m_MeshType;
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
    enum MeshType
    {
        mtWired = 1,
        mtSolid = 2,
    };

private:
    unsigned int m_ListNumber;
    int m_MeshType;
    std::vector<CTriangle3D<T>> m_Triangles;
    std::vector<CTriangle3D<T>> m_CurTriangles;
    float m_LineWidth;

    bool m_UpdateDrawing;
   
public:
    CComponentMesh3D( CBaseEntity& parent )
        : CComponent( parent )
        , m_MeshType{ mtSolid }
        , m_UpdateDrawing{ true }
        , m_ListNumber{ COpenGLMainClass::ObtainListNumber() }
        , m_LineWidth{ 2.0f } {}

    CComponentMesh3D( CBaseEntity& parent, std::initializer_list<std::initializer_list<std::initializer_list<T>>> lst )
        : CComponentMesh3D( parent )
    {
        if( lst.size() )
            AddTriangles( lst );
    }


    ~CComponentMesh3D()
    {
        COpenGLMainClass::FreeListNumber( m_ListNumber );
    }

    void AddTriangles( std::vector<CTriangle3D<T>> triangles )
    {
        for( auto& triangle : triangles )
            m_Triangles.push_back( triangle );
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

    void Subdivide()
    {
        std::vector<CTriangle3D<T>> newTriangles;
        
        for( const auto& triangle : m_Triangles ) {
            std::vector<CTriangle3D<T>> subdividedTriangles = triangle.Subdivided();
            for( const auto subdividedTriangle : subdividedTriangles )
                newTriangles.push_back( subdividedTriangle );
        }

        m_Triangles.clear();
        m_Triangles = newTriangles;
        MakeUpdated( true );
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

        std::shared_ptr<CComponentTransform> transform;

        if( !transform )
            transform = GetAddParentComponent<CComponentTransform, CObject>( m_Parent );
        
        if( !transform )
            transform = GetAddParentComponent<CComponentTransform, CComponent>( m_Parent );

        if( transform && ( transform->WasUpdated() || m_WasUpdated ) ) {
            m_CurTriangles.clear();
            for( CTriangle3D<T> triangle : m_Triangles ) {
                m_CurTriangles.push_back( triangle.RotMovScaled( transform->m_Rot, transform->m_Position, transform->m_Scale ) );
            }

            m_UpdateDrawing = true;
            m_WasUpdated = false;
        }
    };

    void DrawWiredTriangle( const CTriangle3D<T>& triangle )
    {
        glLineWidth( m_LineWidth );

        if( m_MeshType & mtWired ) {
            glPolygonOffset( 0.0f, 1.0f );
            glBegin( GL_LINE_LOOP );

            glColor3f( 0.0, 0.0, 0.0 );
            glVertex3f( triangle.m_p1.X(), triangle.m_p1.Y(), triangle.m_p1.Z() );

            glVertex3f( triangle.m_p2.X(), triangle.m_p2.Y(), triangle.m_p2.Z() );

            glVertex3f( triangle.m_p3.X(), triangle.m_p3.Y(), triangle.m_p3.Z() );

            glEnd();
            glPolygonOffset( 0.0, 0.0f );
        }

    }

    void DrawSolidTriangle( const CTriangle3D<T>& triangle )
    {
        glLineWidth( m_LineWidth );

        if( m_MeshType & mtSolid ) {
            glBegin( GL_POLYGON );

            glColor3f( triangle.m_p1.Color().GetRGB().R, triangle.m_p1.Color().GetRGB().G, triangle.m_p1.Color().GetRGB().B );
            glVertex3f( triangle.m_p1.X(), triangle.m_p1.Y(), triangle.m_p1.Z() );

            glColor3f( triangle.m_p2.Color().GetRGB().R, triangle.m_p2.Color().GetRGB().G, triangle.m_p2.Color().GetRGB().B );
            glVertex3f( triangle.m_p2.X(), triangle.m_p2.Y(), triangle.m_p2.Z() );

            glColor3f( triangle.m_p3.Color().GetRGB().R, triangle.m_p3.Color().GetRGB().G, triangle.m_p3.Color().GetRGB().B );
            glVertex3f( triangle.m_p3.X(), triangle.m_p3.Y(), triangle.m_p3.Z() );

            glEnd();
        }        
    }

    void Draw()
    {
        CComponent::Draw();

        if( !m_UpdateDrawing ) {
            glCallList( m_ListNumber );
            return;
        }

        glNewList( m_ListNumber, GL_COMPILE_AND_EXECUTE );
        glPushMatrix();
        if( m_MeshType & mtSolid )
            for( const CTriangle3D<T>& triangle : m_CurTriangles )
                DrawSolidTriangle( triangle );
        
        if( m_MeshType & mtWired )
            for( const CTriangle3D<T>& triangle : m_CurTriangles )
                DrawWiredTriangle( triangle );

        glPopMatrix();
        glEndList();

        m_UpdateDrawing = false;
    }

    void SetMeshType( int meshType )
    {
        m_MeshType = meshType;
    }

    void SetSolid()
    {
        m_MeshType = 1 << mtSolid;
    }

    void SetWired()
    {
        m_MeshType = 1 << mtWired;
    }

    int GetMeshType() const
    {
        return m_MeshType;
    }


};


