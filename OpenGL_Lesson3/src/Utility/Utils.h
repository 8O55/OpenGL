#ifndef UTILS_H
#define UTILS_H
#include <iostream>
#include <cmath>
#include <unordered_map>


class CColor
{
public:
    struct CHSV;

    enum Color
    {
        cNONE,
        cWHITE,
        cBLACK,
        cYELLOW,
        cGREEN,
        cPURPLE,
        cBLUE,
        cORANGE,
        cRED,

        cSIZE
    };

    struct CRGB
    {
        unsigned char R, G, B;
        CRGB( unsigned char R = 0, unsigned char G = 0, unsigned char B = 0 )
            : R{ R }
            , G{ G }
            , B{ B }
        {};

        CRGB( const CRGB& rgb )
            : R{ rgb.R }
            , G{ rgb.G }
            , B{ rgb.B }
        {}

        CRGB( CRGB&& rgb )
            : R{ rgb.R }
            , G{ rgb.G }
            , B{ rgb.B }
        {
            rgb.R = 0;
            rgb.G = 0;
            rgb.B = 0;
        }

        CRGB operator = ( const CRGB& rgb )
        {
            R = rgb.R;
            G = rgb.G;
            B = rgb.B;

            return *this;
        }
        CRGB operator = ( CRGB&& rgb )
        {
            R = rgb.R;
            G = rgb.G;
            B = rgb.B;

            rgb.R = 0;
            rgb.G = 0;
            rgb.B = 0;

            return *this;
        }

        operator CHSV () const
        {
            double r = R / 255.0;
            double g = G / 255.0;
            double b = B / 255.0;

            double c_max = std::fmax( std::fmax( r, g ), b );
            double c_min = std::fmin( std::fmin( r, g ), b );

            double delta = c_max - c_min;

            double h = 0;
            if( r == c_max && g >= b && delta != 0 )
                h = 60 * ( ( g - b ) / delta + 0 );
            else if( r == c_max && g < b && delta != 0 )
                h = 60 * ( ( g - b ) / delta + 6 );
            else if( g == c_max && delta != 0 )
                h = 60 * ( ( b - r ) / delta + 2 );
            else if( b == c_max && delta != 0  )
                h = 60 * ( ( r - g ) / delta + 4 );

            double s = 0;
            if( c_max != 0 )
                s = delta / c_max;

            double v = c_max;

            return CHSV{ h, s, v };
        }
    };
    struct CHSV
    {
        double H, S, V;
        CHSV( double H = 0, double S = 0, double V = 0 )
            : H{ H }
            , S{ S }
            , V{ V }
        {
            if( H < 0 || H > 360 ||
                S < 0 || S > 1   ||
                V < 0 || V > 1 )
                throw std::invalid_argument("H must be [0;360]; S must be [0;1]; V must be [0;1]!");
        }

        CHSV( const CHSV& hsv )
            : H{ hsv.H }
            , S{ hsv.S }
            , V{ hsv.V }
        {}

        CHSV( CHSV&& hsv )
            : H{ hsv.H }
            , S{ hsv.S }
            , V{ hsv.V }
        {
            hsv.H = 0;
            hsv.S = 0;
            hsv.V = 0;
        }

        CHSV operator = ( const CHSV& hsv )
        {
            H = hsv.H;
            S = hsv.S;
            V = hsv.V;

            return *this;
        }
        CHSV operator = ( CHSV&& hsv )
        {
            H = hsv.H;
            S = hsv.S;
            V = hsv.V;

            hsv.H = 0;
            hsv.S = 0;
            hsv.V = 0;

            return *this;
        }

        operator CRGB () const
        {
            double C = V * S;
            double X = C * ( 1.0 - fabs( std::fmod( ( H / 60.0 ), 6 ) - 1.0 ) );
            double m = V - C;

            double r = 0;
            double g = 0;
            double b = 0;

            if( 0 <= H && H < 60 ) {
                r = C;
                g = X;
                b = 0;
            }
            else if( 60 <= H && H < 120 ) {
                r = X;
                g = C;
                b = 0;
            }
            else if( 120 <= H && H < 180 ) {
                r = 0;
                g = C;
                b = X;
            }
            else if( 180 <= H && H < 240 ) {
                r = 0;
                g = X;
                b = C;
            }
            else if( 240 <= H && H < 300 ) {
                r = X;
                g = 0;
                b = C;
            }
            else if( 300 <= H && H < 360 ) {
                r = C;
                g = 0;
                b = X;
            }

            return CRGB{ static_cast<unsigned char>( ( r + m ) * 255 ),
                         static_cast<unsigned char>( ( g + m ) * 255 ),
                         static_cast<unsigned char>( ( b + m ) * 255 ) };
        }
    };

    const std::unordered_map<Color, CRGB> ColorsMapRGB
    {
        { cNONE,    CRGB{ static_cast<unsigned char>(   0 ), static_cast<unsigned char>(   0 ), static_cast<unsigned char>(   0 ) } },
        { cWHITE,   CRGB{ static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) } },
        { cBLACK,   CRGB{ static_cast<unsigned char>(   0 ), static_cast<unsigned char>(   0 ), static_cast<unsigned char>(   0 ) } },
        { cYELLOW,  CRGB{ static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>(   0 ) } },
        { cGREEN,   CRGB{ static_cast<unsigned char>(   0 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>(   0 ) } },
        { cPURPLE,  CRGB{ static_cast<unsigned char>( 128 ), static_cast<unsigned char>(   0 ), static_cast<unsigned char>( 128 ) } },
        { cBLUE,    CRGB{ static_cast<unsigned char>(   0 ), static_cast<unsigned char>(   0 ), static_cast<unsigned char>( 255 ) } },
        { cORANGE,  CRGB{ static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 165 ), static_cast<unsigned char>(   0 ) } },
        { cRED,     CRGB{ static_cast<unsigned char>( 255 ), static_cast<unsigned char>(   0 ), static_cast<unsigned char>(   0 ) } },
    };
protected:
    CRGB m_RGB;

public:
    CColor( Color color )
    {
        m_RGB = ColorsMapRGB.at( color );
    }

    CColor( CRGB rgb )
        : m_RGB{ rgb }
    {}

    CColor( CHSV hsv )
        : m_RGB{ static_cast< CRGB >( hsv ) }
    {}

    CColor()
        : m_RGB{ 0, 0, 0 }
    {}

    CColor( const CColor& color )
        : m_RGB{ color.m_RGB }
    {}

    CColor( CColor&& color )
        : m_RGB{ color.m_RGB }
    {
        color.m_RGB = CRGB{ 0, 0, 0 };
    }

    virtual ~CColor() = default;

    inline CRGB GetRGB() const { return m_RGB; }
    inline CHSV GetHSV() const { return static_cast<CHSV>( m_RGB ); }

    operator CRGB () const { return GetRGB(); }
    operator CHSV () const { return GetHSV(); }

    inline void SetRGB( CRGB rgb ) { m_RGB = rgb; }
    inline void SetHSV( CHSV hsv ) { m_RGB = static_cast<CRGB>( hsv ); }
    inline void SetColor( CColor color ) { *this = color; }

    CColor operator= ( const CColor& color )
    {
        m_RGB = color.m_RGB;

        return *this;
    }
    CColor operator= ( CColor&& color )
    {
        m_RGB = color.m_RGB;

        color.m_RGB = CRGB{ 0, 0, 0 };

        return *this;
    }
};

class CDrawableObject
{
protected:
    bool m_IsVisible;
    CColor m_Color;
public:
    CDrawableObject()
        : m_IsVisible{ false }
        , m_Color{ CColor::cNONE }
    {};

    CDrawableObject( CColor color, bool isVisible = false )
         : m_IsVisible{ isVisible }
         , m_Color{ color }
    {}

    CDrawableObject( const CDrawableObject& obj )
        : m_IsVisible{ obj.m_IsVisible }
        , m_Color{ obj.m_Color }
    {};

    CDrawableObject( CDrawableObject&& obj )
        : m_IsVisible{ obj.m_IsVisible }
        , m_Color{ obj.m_Color }
    {
        obj.m_IsVisible = false;
        obj.m_Color = CColor{ CColor::cNONE };
    };

    virtual ~CDrawableObject() = default;

    inline bool   IsVisible() const { return m_IsVisible; }
    inline CColor Color()     const { return m_Color; }

    inline void SetVisible( bool isVisible = true ) { m_IsVisible = isVisible; }
    inline void SetColor( CColor color ) { m_Color = color; }

    void operator = ( const CDrawableObject& obj )
    {
        m_IsVisible = obj.m_IsVisible;
        m_Color = obj.m_Color;
    }
    void operator = ( CDrawableObject&& obj )
    {
        m_IsVisible = obj.m_IsVisible;
        m_Color = obj.m_Color;

        obj.m_IsVisible = false;
        obj.m_Color = CColor{ CColor::cNONE };
    }

    virtual void Draw() = 0;

};

#endif // UTILS_H
