#pragma once
#include <initializer_list>

#include "../Math/Matrix.h"
#include "../Math/Vector.h"
#include "../Utils.h"

template<typename T = float>
class CPoint2D : public CDrawableObject
{
protected:
    T m_X, m_Y;
public:
    CPoint2D( T x, T y, CColor color = CColor::cNONE, bool visible = false )
        : CDrawableObject{ color, visible }
        , m_X{ x }
        , m_Y{ y }
    {}

    CPoint2D( std::initializer_list<T> lst, CColor color = CColor::cNONE, bool visible = false )
        : CDrawableObject{ color, visible }
        , m_X{ *( lst.begin() + 0 ) }
        , m_Y{ *( lst.begin() + 1 ) }
    {}

    CPoint2D( const CPoint2D& point )
        : CDrawableObject{ point }
        , m_X{ point.m_X }
        , m_Y{ point.m_Y }
    {}

    CPoint2D( CPoint2D&& point )
        : CDrawableObject{ point }
        , m_X{ point.m_X }
        , m_Y{ point.m_Y }
    {
        point.m_X = 0;
        point.m_Y = 0;
    }

    CPoint2D( CVector<T> vec )
        : CDrawableObject{}
    {
        if( vec.Size() < 2 )
            throw std::invalid_argument( "Vector size must be 2 or more!" );

        m_X = vec[0];
        m_Y = vec[1];
    }

    CPoint2D( CMatrix<T> mat )
        : CDrawableObject{}
    {
        if( mat.Rows() < 1 || mat.Cols() < 2 )
            throw std::invalid_argument( "Matrix rows must be 1 or more! Matrix columns must be 2 or more!" );

        m_X = mat[0][0];
        m_Y = mat[0][1];
    }

    void Draw() override {};

    inline T& X() { return m_X; }
    inline T& Y() { return m_Y; }

    inline const T& X() const { return m_X; }
    inline const T& Y() const { return m_Y; }

    inline void SetX( T x ) { m_X = x; }
    inline void SetY( T y ) { m_Y = y; }

    inline void SetCords( const std::pair<T, T> cords )
    {
        m_X = cords.first;
        m_Y = cords.second;
    };
    inline void SetCords( const CVector<T> vec )
    {
        if( vec.Size() < 2 )
            throw std::invalid_argument( "Vector size must be 2 or more!" );

        m_X = vec[0];
        m_Y = vec[1];
    }

    inline std::pair<T, T> Cords() const { return std::make_pair( m_X, m_Y ); }

    inline void MoveTo( T x, T y ) { SetCords( std::make_pair( x, y ) ); }
    inline void MoveTo( const CPoint2D<T>& point ) { MoveTo( point.m_X, point.m_Y ); }

    inline void Scale( double scale ) { SetCords( std::make_pair( m_X * scale, m_Y * scale ) ); }

    inline double DistanceTo( CPoint2D<T> dst ) const { return DistanceTo( dst.m_X, dst.m_Y ); }
    inline double DistanceTo( T x, T y ) const {
        return sqrt( ( m_X - x ) * ( m_X - x ) +
            ( m_Y - y ) * ( m_Y - y ) );
    }

    CPoint2D<T> operator+=( const CPoint2D<T>& pnt2 )
    {
        m_X += pnt2.m_X;
        m_Y += pnt2.m_Y;

        return *this;
    }
    CPoint2D<T> operator-=( const CPoint2D<T>& pnt2 )
    {
        m_X -= pnt2.m_X;
        m_Y -= pnt2.m_Y;

        return *this;
    }
    CPoint2D<T> operator*=( float scale )
    {
        m_X *= scale;
        m_Y *= scale;

        return *this;
    }

    CPoint2D<T> operator+ ( const CPoint2D<T>& pnt2 ) const
    {
        CPoint2D<T> pnt1{ *this };

        return pnt1 += pnt2;
    }
    CPoint2D<T> operator- ( const CPoint2D<T>& pnt2 ) const
    {
        CPoint2D<T> pnt1{ *this };

        return pnt1 -= pnt2;
    }

    inline T& operator[] ( unsigned short idx )
    {
        if( idx > 1 )
            throw std::out_of_range( "Index out of range!" );

        switch( idx ) {
        case 0: return m_X;
        case 1: return m_Y;
        default: throw std::invalid_argument( "Can't find case!" );
        }
    }

    template<typename D>
    operator CPoint2D<D>() { return CPoint2D<D>{ static_cast< D >( m_X ), static_cast< D >( m_Y ), m_Color, m_IsVisible }; }

    operator CVector<T>() { return CVector<T>{   m_X, m_Y   }; }
    operator CMatrix<T>() { return CMatrix<T>{ { m_X, m_Y } }; }

    CPoint2D operator= ( const CPoint2D& point )
    {
        m_X = point.m_X;
        m_Y = point.m_Y;

        CDrawableObject::operator=( point );

        return *this;
    }
    CPoint2D operator= ( CPoint2D&& point )
    {
        m_X = point.m_X;
        m_Y = point.m_Y;

        point.m_X = 0;
        point.m_Y = 0;

        CDrawableObject::operator=( point );

        return *this;
    }
};

template<typename T = float>
class CPoint3D : public CDrawableObject
{
protected:
    T m_X, m_Y, m_Z;
public:
    CPoint3D( T x, T y, T z, CColor color = CColor::cNONE, bool visible = false )
        : CDrawableObject{ color, visible }
        , m_X{ x }
        , m_Y{ y }
        , m_Z{ z }
    {}

    CPoint3D( std::initializer_list<T> lst, CColor color = CColor::cNONE, bool visible = false )
        : CDrawableObject{ color, visible }
        , m_X{ *( lst.begin() + 0 ) }
        , m_Y{ *( lst.begin() + 1 ) }
        , m_Z{ *( lst.begin() + 2 ) }
    {}

    CPoint3D( const CPoint3D& point )
        : CDrawableObject{ point }
        , m_X{ point.m_X }
        , m_Y{ point.m_Y }
        , m_Z{ point.m_Z }
    {}

    CPoint3D( CPoint3D&& point )
        : CDrawableObject{ point }
        , m_X{ point.m_X }
        , m_Y{ point.m_Y }
        , m_Z{ point.m_Z }
    {
        point.m_X = 0;
        point.m_Y = 0;
        point.m_Z = 0;
    }

    CPoint3D( const CPoint3D& point, CColor color )
        : CPoint3D( point )
    {
        m_Color = color;
    }

    CPoint3D( CVector<T> vec )
        : CDrawableObject{}
    {
        if( vec.Size() < 3 )
            throw std::invalid_argument( "Vector size must be 3 or more!" );

        m_X = vec[0];
        m_Y = vec[1];
        m_Z = vec[2];
    }

    CPoint3D( CMatrix<T> mat )
        : CDrawableObject{}
    {
        if( mat.Rows() < 1 || mat.Cols() < 3 )
            throw std::invalid_argument( "Matrix rows must be 1 or more! Matrix columns must be 3 or more!" );

        m_X = mat[0][0];
        m_Y = mat[0][1];
        m_Z = mat[0][2];
    }

    operator CVector<T>() const { return CVector<T>{   m_X, m_Y, m_Z   }; }
    operator CMatrix<T>() const { return CMatrix<T>{ { m_X, m_Y, m_Z } }; }

    void Draw() override {};

    inline T& X() { return m_X; }
    inline T& Y() { return m_Y; }
    inline T& Z() { return m_Z; }

    inline const T& X() const { return m_X; }
    inline const T& Y() const { return m_Y; }
    inline const T& Z() const { return m_Z; }

    inline void SetX( T x ) { m_X = x; }
    inline void SetY( T y ) { m_Y = y; }
    inline void SetZ( T z ) { m_Z = z; }

    inline void SetCords( const CVector<T> vec )
    {
        if( vec.Size() < 3 )
            throw std::invalid_argument( "Vector size must be 3 or more!" );

        m_X = vec[0];
        m_Y = vec[1];
        m_Z = vec[2];
    }
    inline void SetCords( const T x, const T y, const T z )
    {
        m_X = x;
        m_Y = y;
        m_Z = z;
    }

    inline void MoveTo( T x, T y, T z ) { SetCords( x, y, z ); }
    inline void MoveTo( const CPoint3D<T>& point ) { MoveTo( point.m_X, point.m_Y, point.m_Z ); }

    inline CPoint3D<T> MovedTo( T x, T y, T z ) { CPoint3D<T> result = *this; result.SetCords( x, y, z ); return result; }
    inline CPoint3D<T> MovedTo( const CPoint3D<T>& point ) { return MovedTo( point.m_X, point.m_Y, point.m_Z ); }


    inline CPoint3D<T> Scale( double scale ) { SetCords( m_X * scale, m_Y * scale, m_Z * scale ); return *this; }
    inline const CPoint3D<T> Scaled( double scale ) { CPoint3D<T> point = *this; return point.scale( scale ); }

    inline double DistanceTo( CPoint3D<T> dst ) const { return DistanceTo( dst.m_X, dst.m_Y, dst.m_Z ); }
    inline double DistanceTo( T x, T y, T z )   const {
        return sqrt( ( m_X - x ) * ( m_X - x ) +
            ( m_Y - y ) * ( m_Y - y ) +
            ( m_Z - z ) * ( m_Z - z ) );
    }

    inline CPoint3D<T> MiddlePoint( const CPoint3D<T>& point ) const
    {
        return CPoint3D<T>{ static_cast< CVector<T> >( *this ) + ( static_cast< CVector<T> >( point ) - static_cast< CVector<T> >( *this ) ) / 2 };
    }

    CPoint3D<T> Rotate( T aX, T aY, T aZ )
    {
        CMatrix<T> matrix{ { m_X }, { m_Y }, { m_Z } };

        CMatrix<T> rotationMatrix = CMatrix<T>::GetRotMatrix( CVector<T>{ aX, aY, aZ } );

        CMatrix<T> result = rotationMatrix * matrix;
        m_X = result[0][0];
        m_Y = result[1][0];
        m_Z = result[2][0];
        return *this;
    }
    CPoint3D<T> RotMovScale( CVector<T> rot, CVector<T> mov, CVector<T> scale )
    {
        CMatrix<T> matrix{ { m_X }, { m_Y }, { m_Z }, { 1 } };

        CMatrix<T> rotationMatrix = CMatrix<T>::GetRotMatrix( rot );
        rotationMatrix.PushCol( mov, 3 );
        rotationMatrix.Resize( 4, 4 );
        rotationMatrix[3][3] = 1;



        CMatrix<T> rotMoved = rotationMatrix * matrix;
        m_X = rotMoved[0][0] * scale[0];
        m_Y = rotMoved[1][0] * scale[1];
        m_Z = rotMoved[2][0] * scale[2];

        return *this;
    }

    CPoint3D<T> Rotated( float aX, float aY, float aZ ) const
    {
        CPoint3D<T> result = *this;

        return result.Rotate( aX, aY, aZ );
    }
    CPoint3D<T> RotMovScaled( CVector<T> rot, CVector<T> mov, CVector<T> scale ) const
    {
        CPoint3D<T> result = *this;

        return result.RotMovScale( rot, mov, scale );
    }

    CPoint3D<T> operator+=( const CPoint3D<T>& pnt2 )
    {
        m_X += pnt2.m_X;
        m_Y += pnt2.m_Y;
        m_Z += pnt2.m_Z;

        return *this;
    }
    CPoint3D<T> operator-=( const CPoint3D<T>& pnt2 )
    {
        m_X -= pnt2.m_X;
        m_Y -= pnt2.m_Y;
        m_Z += pnt2.m_Z;

        return *this;
    }
    CPoint3D<T> operator*=( float scale )
    {
        m_X *= scale;
        m_Y *= scale;
        m_Z *= scale;

        return *this;
    }

    CPoint3D<T> operator+ ( const CPoint3D<T>& pnt2 ) const
    {
        CPoint3D<T> pnt1{ *this };

        return pnt1 += pnt2;
    }
    CPoint3D<T> operator- ( const CPoint3D<T>& pnt2 ) const
    {
        CPoint3D<T> pnt1{ *this };

        return pnt1 -= pnt2;
    }

    inline T& operator[] ( unsigned short idx )
    {
        if( idx > 2 )
            throw std::out_of_range( "Index out of range!" );

        switch( idx ) {
        case 0: return m_X;
        case 1: return m_Y;
        case 2: return m_Z;
        default: throw std::invalid_argument( "Can't find case!" );
        }
    }

    template<typename D>
    operator CPoint3D<D>() { return CPoint3D<D>{ static_cast< D >( m_X ), static_cast< D >( m_Y ), static_cast< D >( m_Z ), m_Color, m_IsVisible }; }

    CPoint3D operator= ( const CPoint3D& point )
    {
        m_X = point.m_X;
        m_Y = point.m_Y;
        m_Z = point.m_Z;

        CDrawableObject::operator=( point );

        return *this;
    }
    CPoint3D operator= ( CPoint3D&& point )
    {
        m_X = point.m_X;
        m_Y = point.m_Y;
        m_Z = point.m_Z;

        point.m_X = 0;
        point.m_Y = 0;
        point.m_Z = 0;

        CDrawableObject::operator=( point );

        return *this;
    }
};

