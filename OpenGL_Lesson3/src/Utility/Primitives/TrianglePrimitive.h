#pragma once
#include "PointPrimitive.h"
#include <initializer_list>

template<typename T = double>
class CTriangle2D
{
public:
    CPoint2D<T> m_p1, m_p2, m_p3;
    CTriangle2D( CPoint2D<T> p1, CPoint2D<T> p2, CPoint2D<T> p3 ) : m_p1{ p1 }, m_p2{ p2 }, m_p3{ p3 } {};
    CTriangle2D( std::initializer_list<std::initializer_list<T>> lst )
        : m_p1{ *( lst.begin() + 0 ) }
        , m_p2{ *( lst.begin() + 1 ) }
        , m_p3{ *( lst.begin() + 2 ) }
    {};

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
    CTriangle3D( std::initializer_list<std::initializer_list<T>> lst )
        : m_p1{ *( lst.begin() + 0 )}
        , m_p2{ *( lst.begin() + 1 )}
        , m_p3{ *( lst.begin() + 2 )}
    {};

    CTriangle3D( const CTriangle3D<T>& ) = default;
    CTriangle3D( CTriangle3D<T>&& )      = default;

    CTriangle3D<T>& operator=( const CTriangle3D<T>& ) = default;
    CTriangle3D<T>& operator=( CTriangle3D<T>&& )      = default;

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
};
