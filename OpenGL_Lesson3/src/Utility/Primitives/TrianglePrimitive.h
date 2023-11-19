#pragma once
#include "PointPrimitive.h"
#include <initializer_list>
#include <vector>

template<typename T = double>
class CTriangle2D
{
public:
    CPoint2D<T> m_p1, m_p2;
    CTriangle2D( CPoint2D<T> p1, CPoint2D<T> p2, CPoint2D<T> p3, CColor color = CColor{ CColor::cNONE } ) : m_p1{ p1, color }, m_p2{ p2, color } {};
    CTriangle2D( std::initializer_list<std::initializer_list<T>> lst )
        : m_p1{ *( lst.begin() + 0 ) }
        , m_p2{ *( lst.begin() + 1 ) }
    {
    };

    CTriangle2D( const CTriangle2D<T>& ) = default;
    CTriangle2D( CTriangle2D<T>&& ) = default;

    CTriangle2D<T>& operator=( const CTriangle2D<T>& ) = default;
    CTriangle2D<T>& operator=( CTriangle2D<T>&& ) = default;
};

template<typename T = double>
class CTriangle3D
{
public:
    CPoint3D<T> m_p1, m_p2, m_p3;

    CTriangle3D( CPoint3D<T> p1, CPoint3D<T> p2, CPoint3D<T> p3 ) : m_p1{ p1 }, m_p2{ p2 }, m_p3{ p3 } {};
    CTriangle3D( CPoint3D<T> p1, CPoint3D<T> p2, CPoint3D<T> p3, CColor color ) : m_p1{ p1, color }, m_p2{ p2, color }, m_p3{ p3, color } {};
    CTriangle3D( std::initializer_list<std::initializer_list<T>> lst, CColor color = CColor{ CColor::cNONE } )
        : m_p1{ *( lst.begin() + 0 ), color }
        , m_p2{ *( lst.begin() + 1 ), color }
        , m_p3{ *( lst.begin() + 2 ), color }
    {
    };

    CTriangle3D( const CTriangle3D<T>& ) = default;
    CTriangle3D( CTriangle3D<T>&& ) = default;

    CTriangle3D<T>& operator=( const CTriangle3D<T>& ) = default;
    CTriangle3D<T>& operator=( CTriangle3D<T>&& ) = default;

    CTriangle3D<T> Rotate( float aX, float aY, float aZ )
    {
        m_p1.Rotate( aX, aY, aZ );
        m_p2.Rotate( aX, aY, aZ );
        m_p3.Rotate( aX, aY, aZ );

        return *this;
    }
    CTriangle3D<T> Rotated( float aX, float aY, float aZ ) const
    {
        CTriangle3D<T> result = *this;

        return result.Rotate( aX, aY, aZ );
    }

    CTriangle3D<T> RotMovScale( CVector<T> rot, CVector<T> mov, CVector<T> scale )
    {
        m_p1.RotMovScale( rot, mov, scale );
        m_p2.RotMovScale( rot, mov, scale );
        m_p3.RotMovScale( rot, mov, scale );

        return *this;
    }
    CTriangle3D<T> RotMovScaled( CVector<T> rot, CVector<T> mov, CVector<T> scale ) const
    {
        CTriangle3D<T> result = *this;

        return result.RotMovScale( rot, mov, scale );
    }

    CTriangle3D<T> Scale( CVector<T> scale )
    {
        m_p1.Scale( scale[0] );
        m_p2.Scale( scale[1] );
        m_p3.Scale( scale[2] );

        return *this;
    }
    CTriangle3D<T> Scaled( CVector<T> scale ) const
    {
        CTriangle3D<T> result = *this;

        return result.Scale( scale );
    }

    std::vector<CTriangle3D<T>> Subdivided() const
    {
        CPoint3D<T> _p1{ m_p1.MiddlePoint( m_p2 ), CColor::Middle( m_p1.Color(), m_p2.Color() ) };
        CPoint3D<T> _p2{ m_p2.MiddlePoint( m_p3 ), CColor::Middle( m_p1.Color(), m_p2.Color() ) };
        CPoint3D<T> _p3{ m_p3.MiddlePoint( m_p1 ), CColor::Middle( m_p1.Color(), m_p2.Color() ) };


        std::vector<CTriangle3D<T>> subdivided{ CTriangle3D<T>{ m_p1,   _p1, _p3 },
                                                CTriangle3D<T>{  _p1,  m_p2, _p2 },
                                                CTriangle3D<T>{  _p2,  m_p3, _p3 },
                                                CTriangle3D<T>{  _p1,   _p2, _p3 } };

        return subdivided;

    }
};
