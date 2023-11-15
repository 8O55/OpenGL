#ifndef COMPONENT_TRANSFORM
#define COMPONENT_TRANSFORM
#include "Component.h"
#include "../../Utility/Math/Matrix.h"
#include "../../Utility/Math/Vector.h"

class CComponent;
class CBaseEntity;

class CComponentTransform : public CComponent
{
public:
    CVector<float> m_Position;
    CVector<float> m_Direction;

    CVector<float>  m_Rot;
    CVector<float>  m_Move;
    CVector<float>  m_Scale;

public:
    CComponentTransform( CBaseEntity& parent )
        : CComponent( parent )
        , m_Position{ 0, 0, 0 }
        , m_Direction{ 0, 0, -1 }
        , m_Rot{ 0, 0, 0 }
        , m_Move{ 0, 0, 0 }
        , m_Scale{ 1, 1, 1 }
    {

    }

    CComponentTransform( const CComponentTransform& ) = default;
    CComponentTransform( CComponentTransform&& )      = default;

    CComponentTransform& operator=( const CComponentTransform& ) = default;
    CComponentTransform& operator=( CComponentTransform&& )      = default;

    // Унаследовано через CComponent
    virtual void Update() override
    {
        CComponent::Update();

        m_Position  += ( CMatrix<float>::GetRotMatrix( m_Rot ) * CMatrix<float>{ m_Move }.Transposed() ).Transposed()[0];
        m_Direction  = ( CMatrix<float>::GetRotMatrix( m_Rot ) * CMatrix<float>{ CVector<float>{ 0, 0, -1 } }.Transposed()).Transposed()[0];

        m_Move    = CVector<float>{ 0, 0, 0 };
        m_Scale   = CVector<float>{ 0, 0, 0 };
    };

    virtual void PreUpdate() override
    {
        CComponent::PreUpdate();
    };
};
#endif