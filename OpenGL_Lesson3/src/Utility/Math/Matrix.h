#ifndef CMATRIX_H
#define CMATRIX_H
#define _USE_MATH_DEFINES
#include <stdexcept>
#include "Vector.h"
#include <typeinfo>
#include <math.h>

template<typename T = double>
class CMatrix
{
protected:
    CVector<CVector<T>> m_Matrix;
public:
    CMatrix( std::initializer_list<CVector<T>> lst );
    CMatrix( std::initializer_list<std::initializer_list<T>> lst );
    CMatrix( const CMatrix<T>&  );
    CMatrix( CMatrix<T>&& );
    CMatrix();

    inline void PushRow( CVector<T> row, size_t idx );
    inline void PushCol( CVector<T> col, size_t idx );
    inline void PopRow ( size_t idx );
    inline void PopCol ( size_t idx );
    inline void PopAt  ( size_t row, size_t col );
    inline T&   At     ( size_t row, size_t col );
    const inline T& At ( size_t row, size_t col ) const;

    inline void Clear();

    inline void Resize( size_t rows, size_t cols );
    inline void Resize( std::pair<size_t, size_t> newSize );

    inline std::pair<size_t, size_t> Size() const;
    inline size_t Rows() const;
    inline size_t Cols() const;

    CMatrix<T> Transpose();             //!< Транспонировать матрицу
    CMatrix<T> Transposed() const;      //!< Получить транспонированную матрицу
    CMatrix<T> Inverse();               //!< Обратиь матрицу
    CMatrix<T> Inversed() const;        //!< Получить обратную матрицу

    T AlgExt( size_t i, size_t j );     //!< Алгебраическое дополнение
    T Minor ( size_t i, size_t j );     //!< Минор
    T Det   ();                         //!< Определитель

    CVector<T>& operator[] ( size_t row );
    const CVector<T>& operator[] ( size_t row ) const;

    CMatrix<T> operator+ ( T number        );   //!< Сложение с числом
    CMatrix<T> operator+ ( CMatrix<T> mat2 );   //!< Сложение с матрицей
    CMatrix<T> operator- ( T number        );   //!< Вычитание числа
    CMatrix<T> operator- ( CMatrix<T> mat2 );   //!< Вычитание матрицы
    CMatrix<T> operator* ( T number        );   //!< Масштабирование
    CMatrix<T> operator* ( CMatrix<T> mat2 );   //!< Перемножение матриц
    CMatrix<T> operator/ ( T number );          //!< Масштабирование

    CMatrix<T> operator+=( T number );          //!< Сложение с числом
    CMatrix<T> operator+=( CMatrix<T> mat2 );   //!< Сложение с матрицей
    CMatrix<T> operator-=( T number );          //!< Вычитание числа
    CMatrix<T> operator-=( CMatrix<T> mat2 );   //!< Вычитание матрицы
    CMatrix<T> operator*=( T number );          //!< Масштабирование
    CMatrix<T> operator*=( CMatrix<T> mat2 );   //!< Перемножение матриц
    CMatrix<T> operator/=( T number );          //!< Масштабирование

    CMatrix<T> operator=( const CMatrix<T>& mat2 );   //!< Оператор копирования
    CMatrix<T> operator=( CMatrix<T>&& mat2 );  //!< Оператор перемещения

    static std::pair<size_t, size_t> AlignDims( CMatrix<T>& mat1, CMatrix<T>& mat2 );

    void Print();

    static CMatrix<T> GetRotMatrix( CVector<T> rot );
};

template<typename T>
CMatrix<T>::CMatrix( std::initializer_list<CVector<T>> lst )
    : CMatrix()
{
    m_Matrix.Resize( lst.size() );
    size_t maxSize = 0;

    for( auto vec : lst )
        if( maxSize < vec.Size() )
            maxSize = vec.Size();

    for( size_t i = 0; i < lst.size(); ++i ) {
        m_Matrix[i] = *( lst.begin() + i );
        m_Matrix[i].Resize( maxSize );
    }
}

template<typename T>
CMatrix<T>::CMatrix( std::initializer_list<std::initializer_list<T>> lst )
    : CMatrix()
{
    m_Matrix.Resize( lst.size() );
    size_t maxSize = 0;

    for( auto vec : lst )
        if( maxSize < vec.size() )
            maxSize = vec.size();

    for( size_t i = 0; i < lst.size(); ++i ) {
        m_Matrix[i] = CVector<T>{ *( lst.begin() + i ) };
        m_Matrix[i].Resize( maxSize );
    }
}

template<typename T>
CMatrix<T>::CMatrix( const CMatrix<T>& mat2 )
    : m_Matrix()
{
    m_Matrix.Resize( mat2.Rows() );

    for( size_t i = 0; i < mat2.Rows(); ++i ) {
        m_Matrix[i].Resize( mat2.Cols() );
        for( size_t j = 0; j < mat2.Cols(); ++j )
            m_Matrix[i][j] = mat2[i][j];
    }
}

template<typename T>
CMatrix<T>::CMatrix( CMatrix<T> && mat2 )
{
    m_Matrix.Resize( mat2.Rows() );

    for( size_t i = 0; i < mat2.Rows(); ++i ) {
        m_Matrix[i].Resize( mat2.Cols() );
        for( size_t j = 0; j < mat2.Cols(); ++j )
            m_Matrix[i][j] = mat2[i][j];
    }

    mat2.Clear();
    mat2.Resize( 0, 0 );
}

template<typename T>
CMatrix<T>::CMatrix() : m_Matrix()
{

}

template<typename T>
void CMatrix<T>::PushRow( CVector<T> row, size_t idx )
{
    if( idx > m_Matrix.Size() )
        throw std::out_of_range("Can't push row!");

    m_Matrix.PushAt( row, idx );
}

template<typename T>
void CMatrix<T>::PushCol( CVector<T> col, size_t idx )
{
    if( !m_Matrix.Size() || idx > m_Matrix[0].Size() )
        throw std::out_of_range("Can't push column!");

    col.Resize( m_Matrix.Size() );

    for( size_t i = 0; i < m_Matrix.Size(); ++i )
        m_Matrix[i].PushAt( col[i], idx );
}

template<typename T>
void CMatrix<T>::PopRow( size_t idx )
{
    if( idx >= m_Matrix.Size() )
        throw std::out_of_range("Can't pop row!");

    m_Matrix.PopAt( idx );
}

template<typename T>
void CMatrix<T>::PopCol( size_t idx )
{
    if( !m_Matrix.Size() || idx >= m_Matrix[0].Size() )
        throw std::out_of_range("Can't pop column!");

    for( size_t i = 0; i < m_Matrix.Size(); ++i )
        m_Matrix[i].PopAt( idx );
}

template<typename T>
T& CMatrix<T>::At( size_t row, size_t col )
{
    return m_Matrix[row][col];
}

template<typename T>
const T& CMatrix<T>::At( size_t row, size_t col ) const
{
    return m_Matrix[row][col];
}

template<typename T>
void CMatrix<T>::Clear()
{
    for( size_t i = 0; i < Rows(); i++ )
        m_Matrix[i].Clear();
}

template<typename T>
void CMatrix<T>::Resize( size_t rows, size_t cols )
{
    m_Matrix.Resize( rows );

    for( size_t i = 0; i < rows; ++i )
        m_Matrix[i].Resize( cols );
}

template<typename T>
void CMatrix<T>::Resize(std::pair<size_t, size_t> newSize)
{
    Resize( newSize.first, newSize.second );
}

template<typename T>
std::pair<size_t, size_t> CMatrix<T>::Size() const
{
    return std::make_pair( Rows(), Cols() );
}

template<typename T>
size_t CMatrix<T>::Rows() const
{
    return m_Matrix.Size();
}

template<typename T>
size_t CMatrix<T>::Cols() const
{
    return Rows() ? m_Matrix.At(0).Size() : 0LL;
}

template<typename T>
CMatrix<T> CMatrix<T>::Transpose()
{
    CMatrix<T> mat2;
    mat2.Resize( Cols(), Rows() );

    for( size_t row = 0; row < Rows(); ++row )
        for( size_t col = 0; col < Cols(); ++ col )
            mat2[col][row] = (*this)[row][col];

    *this = mat2;

    return *this;
}

template<typename T>
CMatrix<T> CMatrix<T>::Transposed() const
{
    CMatrix<T> mat{*this};

    return mat.Transpose();
}

template<typename T>
CMatrix<T> CMatrix<T>::Inverse()
{
    T det = Det();

    if( det == 0 )
        throw std::invalid_argument("Determinant is zero in calculating inverted matrix!");

    CMatrix<T> mat2{ *this };

    for( size_t row = 0; row < Rows(); ++row )
        for( size_t col = 0; col < Cols(); ++col )
            At( row, col ) = mat2.AlgExt( row, col );

    Transpose();
    *this /= det;
    return *this;
}

template<typename T>
CMatrix<T> CMatrix<T>::Inversed() const
{
    CMatrix<T> mat2{ *this };

    return mat2.Invert();
}

template<typename T>
T CMatrix<T>::AlgExt( size_t row, size_t col )
{
    return ( row + col ) % 2 ? -Minor( row, col )
                             :  Minor( row, col );
}

template<typename T>
T CMatrix<T>::Minor( size_t row, size_t col )
{
    CMatrix<T> mat2{*this};
    T minor = 0;

    mat2.PopRow( row );
    mat2.PopCol( col );

    if( mat2.Rows() == 1 && mat2.Cols() == 1 )
        minor = mat2.At( 0, 0 );
    else
        minor = mat2.Det();

    return minor;
}

template<typename T>
T CMatrix<T>::Det()
{
    T det = 0;

    if( Rows() != Cols() )
        throw std::invalid_argument("Matrix must be squared!");

    if( Rows() != 2 )
        for( size_t row = 0; row < Rows(); ++row )
                det += At( row , 0 ) * AlgExt( row, 0 );
    else
        det = At( 0, 0 ) * At( 1, 1 ) - At( 0, 1 ) * At( 1, 0 );

    return det;
}

template<typename T>
CVector<T>& CMatrix<T>::operator[] ( size_t row )
{
    return m_Matrix[row];
}

template<typename T>
const CVector<T>& CMatrix<T>::operator[] ( size_t row ) const
{
    return m_Matrix[row];
}

template<typename T>
CMatrix<T> CMatrix<T>::operator+=( T number )
{
    for( CVector<T>& row : m_Matrix )
        for( T& elem : row )
            elem += number;

    return *this;
}

template<typename T>
CMatrix<T> CMatrix<T>::operator+=( CMatrix<T> mat2 )
{
    AlignDims( *this, mat2 );

    for( size_t row = 0; row < Rows(); ++row )
        for( size_t col = 0; col < Cols(); ++col )
            At( row, col ) += mat2.At( row, col );

    return *this;
}

template<typename T>
CMatrix<T> CMatrix<T>::operator-=(T number)
{
    for( CVector<T>& row : m_Matrix )
        for( T& elem : row )
            elem -= number;

    return *this;
}

template<typename T>
CMatrix<T> CMatrix<T>::operator-=( CMatrix<T> mat2 )
{
    AlignDims( *this, mat2 );

    for( size_t row = 0; row < Rows(); ++row )
        for( size_t col = 0; col < Cols(); ++col )
            At( row, col ) -= mat2.At( row, col );

    return *this;
}

template<typename T>
CMatrix<T> CMatrix<T>::operator*=(T number)
{
    for( CVector<T>& row : m_Matrix )
        for( T& elem : row )
            elem *= number;

    return *this;
}

template<typename T>
CMatrix<T> CMatrix<T>::operator*=( CMatrix<T> mat2 )
{
    if( Cols() != mat2.Rows() )
        throw std::invalid_argument("Rows != Cols");

    CMatrix<T> mat1{*this};

    size_t resultRows = mat1.Rows();
    size_t resultCols = mat2.Cols();

    Resize( resultRows, resultCols );

    mat2.Transpose();

    for( size_t row = 0; row < resultRows; ++row )
        for( size_t col = 0; col < resultCols; ++col )
            At( row, col ) = mat1[row].Dot( mat2[col] );

    return *this;
}

template<typename T>
CMatrix<T> CMatrix<T>::operator/=(T number)
{
    for( CVector<T>& row : m_Matrix )
        for( T& elem : row )
            elem /= number;

    return *this;
}

template<typename T>
CMatrix<T> CMatrix<T>::operator+( T number )
{
    CMatrix<T> mat1{*this};

    return mat1 += number;
}

template<typename T>
CMatrix<T> CMatrix<T>::operator+( CMatrix<T> mat2 )
{
    CMatrix<T> mat1{*this};

    return mat1 += mat2;
}

template<typename T>
CMatrix<T> CMatrix<T>::operator-( T number )
{
    CMatrix<T> mat1{*this};

    return mat1 -= number;
}

template<typename T>
CMatrix<T> CMatrix<T>::operator-( CMatrix<T> mat2 )
{
    CMatrix<T> mat1{*this};

    return mat1 -= mat2;
}

template<typename T>
CMatrix<T> CMatrix<T>::operator*( T number )
{
    CMatrix<T> mat1{*this};

    return mat1 *= number;
}

template<typename T>
CMatrix<T> CMatrix<T>::operator*( CMatrix<T> mat2 )
{
    CMatrix<T> mat1{*this};

    return mat1 *= mat2;
}

template<typename T>
CMatrix<T> CMatrix<T>::operator=( const CMatrix<T>& mat2 )
{
    Resize( mat2.Size() );

    for( size_t row = 0; row < Rows(); ++row )
        (*this)[row] = mat2[row];

    return *this;
}

template<typename T>
CMatrix<T> CMatrix<T>::operator=( CMatrix<T>&& mat2 )
{
    Resize( mat2.Size() );

    for( size_t row = 0; row < Rows(); ++row )
        (*this)[row] = mat2[row];

    mat2.Clear();
    mat2.Resize( 0, 0 );

    return *this;
}

template<typename T>
CMatrix<T> CMatrix<T>::operator/( T number )
{
    CMatrix<T> mat1{*this};

    return mat1 /= number;
}

template<typename T>
std::pair<size_t, size_t> CMatrix<T>::AlignDims(CMatrix<T> &mat1, CMatrix<T> &mat2)
{
    size_t maxRows = std::max( mat1.Rows(), mat2.Rows() );
    size_t maxCols = std::max( mat1.Cols(), mat2.Cols() );

    mat1.Resize( maxRows, maxCols );
    mat2.Resize( maxRows, maxCols );

    return std::make_pair( maxRows, maxCols );
}

template<typename T>
void CMatrix<T>::Print()
{
    for( auto row : m_Matrix )
        row.Print();
    std::cout << std::endl;
}

template<typename T>
inline CMatrix<T> CMatrix<T>::GetRotMatrix( CVector<T> rot )
{

    rot *= M_PI / 180;

    float s1 = sin( rot[0]);
    float c1 = cos( rot[0] );

    float s2 = sin( rot[1] );
    float c2 = cos( rot[1] );

    float s3 = sin( rot[2] );
    float c3 = cos( rot[2] );

    CMatrix<T> result{ { c2 * c3,   c3 * s1 * s2 - c1 * s3,   c1 * c3 * s2 + s1 * s3 },
                       { c2 * s3,   c1 * c3 + s1 * s2 * s3,  -c3 * s1 + c1 * s2 * s3 },
                       { -s2,       c2 * s1,                  c1 * c2                } };

    return result;

    /*
    CMatrix<T> rotX{ { 1,              0,               0 },
                     { 0, cosf( rot[0] ), -sinf( rot[0] ) },
                     { 0, sinf( rot[0] ),  cosf( rot[0] ) } };

    CMatrix<T> rotY{ {  cosf( rot[1] ), 0, sinf( rot[1] ) },
                     {               0, 1,              0 },
                     { -sinf( rot[1] ), 0, cosf( rot[1] ) } };

    CMatrix<T> rotZ{ { cosf( rot[2] ), -sinf( rot[2] ), 0 },
                     { sinf( rot[2] ),  cosf( rot[2] ), 0 },
                     {              0,               0, 1 } };

    
    return rotZ * rotY * rotX;
    */
}

#endif // CMATRIX_H
