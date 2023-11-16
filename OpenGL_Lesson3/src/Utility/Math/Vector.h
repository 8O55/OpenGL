#ifndef CVECTOR_H
#define CVECTOR_H
#include <vector>
#include <iostream>
#include <initializer_list>
#include <stdexcept>
#include <math.h>

template<typename T = double>
class CVector
{
protected:
    std::vector<T> m_Vector;
public:
    class Iterator;
    CVector( const CVector<T>& );               //!< Конструктор копирования
    CVector( CVector<T>&& );                    //!< Конструктор перемещения
    CVector( std::initializer_list<T> lst );
    CVector();

    virtual ~CVector();

    Iterator begin() { return &( *m_Vector.begin() ); }
    Iterator end()   { return &( *m_Vector.end() );   }

    friend std::ostream& operator<< ( std::ostream& s, const CVector<T>& vec );

    class Iterator
    {
        T* cur;
    public:
        Iterator( T* first ) : cur( first ) {};

        T& operator+ ( int n ) { return *( cur + n ); }
        T& operator- ( int n ) { return *( cur - n ); }

        T& operator++( int ) { return *cur++; }
        T& operator--( int ) { return *cur--; }
        T& operator++()      { return *++cur; }
        T& operator--()      { return *--cur; }

        bool operator!= ( const Iterator& it) { return cur != it.cur; }
        bool operator== ( const Iterator& it) { return cur == it.cur; }
        T& operator* () { return *cur; }
    };

    inline void   PushBack ( T& elem );         //!< Вставить в конец
    inline void   PushFront( T& elem );         //!< Вставить в начало
    inline void   PushAt   ( T& elem,
                             size_t idx );      //!< Вставить в
    inline void   PopBack  ();                  //!< Удалить последний
    inline void   PopFront ();                  //!< Удалить первый
    inline void   PopAt    ( size_t idx  );     //!< Удалить в
    inline void   Resize   ( size_t size );     //!< Изменить размерность
    inline T&     At       ( size_t idx  );     //!< Доступ к элементу по индексу
    inline size_t Size     () const;            //!< Размер
    inline void   Clear    ();                  //!< Очистить вектор

    const inline T& At ( size_t idx  ) const;   //!< Доступ к элементу по индексу

    CVector<T> Scale ( T k );                   //!< Масштабирование
    CVector<T> Rotate( double angle,
                       CVector<T> dirVec );     //!< Поворот вектора

    CVector<T> Rotate( CVector<T> rot );        //!< Поворот вектора

    T Triple( const CVector<T> b,
              const CVector<T> c ) const;       //!< Смешанное произведение векторов

    T Dot( const CVector<T> ) const;            //!< Скалярное произведение векторов
    T Lenght() const;                           //!< Длина вектора

    double Angle( CVector<T> vec2 ) const;      //!< Угол между векторами

    static CVector<T> Rotate( CVector<T>& vec,
                              double angle,
                              CVector<T> dirVec );  //!< Поворот вектора

    static std::pair<size_t, size_t> Dimentions( CVector<T>& vec );
    static CVector<T> Scale ( CVector<T>& vec, T k );

    static T Triple( const CVector<T> a,
                     const CVector<T> b,
                     const CVector<T> c );      //!< Смешанное произведение векторов

    static T Dot( const CVector<T> a,
                  const CVector<T> b );         //!< Скалярное произведение векторов

    static T Lenght( const CVector<T> vec );    //!< Длина вектора

    static double Angle( const CVector<T> vec1,
                         const CVector<T> vec2 );  //!< Угол между векторами

    T &operator[]( size_t idx );                //!< Доступ к элементу
    const T &operator[]( size_t idx ) const;    //!< Доступ к элементу

    CVector<T> operator+ ( T number        );   //!< Сложение с числом
    CVector<T> operator+ ( CVector<T> vec2 );   //!< Сложение с вектором
    CVector<T> operator- ();                    //!< Инвертирование
    CVector<T> operator- ( T number        );   //!< Вычитание числа
    CVector<T> operator- ( CVector<T> vec2 );   //!< Вычитание вектора
    CVector<T> operator* ( T number        );   //!< Масштабирование
    CVector<T> operator* ( CVector<T> vec2 );   //!< Векторное произведение

    CVector<T> operator+=( T number );          //!< Сложение с числом
    CVector<T> operator+=( CVector<T> vec2 );   //!< Сложение с вектором
    CVector<T> operator-=( T number );          //!< Вычитание числа
    CVector<T> operator-=( CVector<T> vec2 );   //!< Вычитание вектора
    CVector<T> operator*=( T number );          //!< Масштабирование
    CVector<T> operator*=( CVector<T> vec2 );   //!< Векторное произведение

    CVector<T> operator=( const CVector<T>& vec2 );  //!< Оператор копирования
    CVector<T> operator=( CVector<T>&& vec2 );       //!< Оператор перемещения

    bool operator==( const CVector<T>& vec2 );

    void Print() {
        for( auto elem : m_Vector )
            std::cout << elem << " ";
        std::cout << std::endl;
    };
};

template<typename T>
std::ostream& operator<< ( std::ostream& s, const CVector<T>& vec )
{
    s << vec.m_Vector;
    return s;
}

template<typename T>
CVector<T>::CVector( const CVector<T> &vec2 )
    : m_Vector( vec2.m_Vector )
{

}

template<typename T>
CVector<T>::CVector( CVector<T> &&vec2 )
    : m_Vector( vec2.m_Vector )
{

}

template<typename T>
CVector<T>::CVector( std::initializer_list<T> lst )
    : m_Vector( 0 )
{
    for( auto elem : lst )
        m_Vector.push_back( elem );
}

template<typename T>
CVector<T>::CVector()
    : m_Vector( 0 )
{

}

template<typename T>
CVector<T>::~CVector()
{

}

template<typename T>
void CVector<T>::PushBack( T& elem )
{
    m_Vector.push_back( elem );
}

template<typename T>
void CVector<T>::PushFront( T& elem )
{
    m_Vector.insert( m_Vector.begin(), elem );
}

template<typename T>
void CVector<T>::PushAt( T& elem, size_t idx )
{
    if( idx > m_Vector.size() )
        throw std::out_of_range("Can't push value!");

    m_Vector.insert( m_Vector.begin() + idx, elem );
}

template<typename T>
void CVector<T>::PopBack()
{
    m_Vector.pop_back();
}

template<typename T>
void CVector<T>::PopFront()
{
    m_Vector.erase( m_Vector.begin() );
}

template<typename T>
void CVector<T>::PopAt( size_t idx )
{
    if( idx >= m_Vector.size() )
        throw std::out_of_range("Can't remove!");

    m_Vector.erase( m_Vector.begin() + idx );
}

template<typename T>
void CVector<T>::Resize( size_t size )
{
    m_Vector.resize( size );
}

template<typename T>
T &CVector<T>::At( size_t idx )
{
    if( idx >= m_Vector.size() )
        throw std::out_of_range("Can't find value!");

    return m_Vector.at( idx );
}

template<typename T>
const T &CVector<T>::At( size_t idx ) const
{
    if( idx >= m_Vector.size() )
        throw std::out_of_range("Can't find value!");

    return m_Vector.at( idx );
}

template<typename T>
size_t CVector<T>::Size() const
{
    return m_Vector.size();
}

template<typename T>
CVector<T> CVector<T>::Scale( T k )
{
    for( T& elem : m_Vector )
        elem *= k;

    return *this;
}

template<typename T>
void CVector<T>::Clear()
{
    m_Vector.clear();
}

template<typename T>
CVector<T> CVector<T>::Rotate( double angle, CVector<T> dirVec )
{

}

template<typename T>
CVector<T> CVector<T>::Rotate( CVector<T> rot )
{

}

template<typename T>
T CVector<T>::Triple(const CVector<T> b, const CVector<T> c) const
{
    CVector<T> a{*this};
    return a.Dot( b * c );
}

template<typename T>
T CVector<T>::Dot( const CVector<T> vec2 ) const
{
    T value = 0;
    CVector<T> vec1{ *this };

    for( size_t i = 0; i < std::fmin( vec1.Size(), vec2.Size() ); ++i )
        value += vec1[i] * vec2[i];

    return value;
}

template<typename T>
T CVector<T>::Lenght() const
{
    T lenght2 = 0;

    for( auto elem : m_Vector )
        lenght2 += elem * elem;

    return sqrt( lenght2 );
}

template<typename T>
double CVector<T>::Angle( CVector<T> vec2 ) const
{
    double angle = 0;
    CVector<T> vec1{ *this };

    angle = Dot( vec1, vec2 ) / ( vec1.Lenght() * vec2.Lenght() );

    return acos( angle );
}

template<typename T>
CVector<T> CVector<T>::Rotate( CVector<T>& vec, double angle, CVector<T> dirVec )
{
    return vec.Rotate( angle, dirVec );
}

template<typename T>
double CVector<T>::Angle( const CVector<T> vec1, const CVector<T> vec2 )
{
    return vec1.Angle( vec2 );
}

template<typename T>
T &CVector<T>::operator[]( size_t idx )
{
    return At( idx );
}

template<typename T>
const T &CVector<T>::operator[]( size_t idx ) const
{
    return At( idx );
}

template<typename T>
CVector<T> CVector<T>::operator+=( T number )
{
    CVector<T> vec1{ *this };

    for( T& elem : vec1.m_Vector )
        elem += number;

    *this = vec1;

    return *this;
}

template<typename T>
CVector<T> CVector<T>::operator+=( CVector<T> vec2 )
{
    CVector<T> vec1{ *this };
    size_t newSize = std::fmax( vec1.Size(), vec2.Size() );

    vec1.Resize( newSize );
    vec2.Resize( newSize );

    for( size_t i = 0; i < newSize; ++i )
        vec1[i] += vec2[i];

    *this = vec1;

    return *this;
}

template<typename T>
CVector<T> CVector<T>::operator-=( T number )
{
    CVector<T> vec1{ *this };

    for( T& elem : vec1.m_Vector )
        elem -= number;

    *this = vec1;

    return *this;
}

template<typename T>
CVector<T> CVector<T>::operator-=( CVector<T> vec2 )
{
    CVector<T> vec1{ *this };
    size_t newSize = std::max( vec1.Size(), vec2.Size() );

    vec1.Resize( newSize );
    vec2.Resize( newSize );

    for( size_t i = 0; i < newSize; ++i )
        vec1[i] -= vec2[i];

    *this = vec1;

    return *this;
}

template<typename T>
CVector<T> CVector<T>::operator*=( T number )
{
    CVector<T> vec1{ *this };

    vec1.Scale( number );

    *this = vec1;

    return *this;
}

// Пока что работает только для трехмерного пространства
template<typename T>
CVector<T> CVector<T>::operator*=( CVector<T> vec2 )
{
    if( m_Vector.size() != 3 || vec2.Size() != 3 )
        throw std::logic_error("Can't multiply vectors!");

    CVector<T> base{ 1, 1, 1 };
    CVector<T> vec1{ *this };
    CVector<T> res;
    size_t newSize = 3;

    //base.Resize( newSize );
    vec1.Resize( newSize );
    vec2.Resize( newSize );
    res.Resize ( newSize );

    for( size_t i = 0; i < newSize; ++i )
        base[i] = 1;

    res[0] =  ( vec1[1] * vec2[2] - vec1[2] * vec2[1] ) * base[0];
    res[1] = -( vec1[0] * vec2[2] - vec1[2] * vec2[0] ) * base[1];
    res[2] =  ( vec1[0] * vec2[1] - vec1[1] * vec2[0] ) * base[2];

    *this = res;

    return *this;
}

template<typename T>
CVector<T> CVector<T>::operator+( T number )
{
    CVector<T> vec1{ *this };

    return vec1 += number;
}

template<typename T>
CVector<T> CVector<T>::operator+( CVector<T> vec2 )
{
    CVector<T> vec1{ *this };

    return vec1 += vec2;
}

template<typename T>
CVector<T> CVector<T>::operator-()
{
    CVector<T> vec1{ *this };

    for( T& elem : vec1.m_Vector )
        elem = -elem;

    return vec1;
}

template<typename T>
CVector<T> CVector<T>::operator-( T number )
{
    CVector<T> vec1{ *this };

    return vec1 -= number;
}

template<typename T>
CVector<T> CVector<T>::operator-( CVector<T> vec2 )
{
    CVector<T> vec1{ *this };

    return vec1 -= vec2;
}

template<typename T>
CVector<T> CVector<T>::operator*( T number )
{
    CVector<T> vec1{ *this };

    return vec1 *= number;
}

// Пока что работает только для трехмерного пространства
template<typename T>
CVector<T> CVector<T>::operator*( CVector<T> vec2 )
{
    CVector<T> vec1{ *this };

    return vec1 *= vec2;
}

template<typename T>
CVector<T> CVector<T>::operator=( const CVector<T>& vec2 )
{
    Resize( vec2.Size() );
    for( size_t i = 0; i < vec2.Size(); ++i )
        m_Vector[i] = vec2[i];

    return *this;
}

template<typename T>
CVector<T> CVector<T>::operator=( CVector<T>&& vec2 )
{
    Resize( vec2.Size() );
    for( size_t i = 0; i < vec2.Size(); ++i )
        m_Vector[i] = vec2[i];

    vec2.Clear();

    return *this;
}

template<typename T>
bool CVector<T>::operator==( const CVector<T>& vec2 )
{
    if( Size() != vec2.Size() )
        return false;

    for( size_t i = 0; i < vec2.Size(); i++ )
        if( operator[](i) != vec2[i] )
            return false;

    return true;
}

#endif // CVECTOR_H

