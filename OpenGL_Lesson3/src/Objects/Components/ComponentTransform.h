#ifndef COMPONENT_TRANSFORM
#define COMPONENT_TRANSFORM
#include "Component.h"
#include "../../Utility/Math/Matrix.h"
#include "../../Utility/Math/Vector.h"

class CObject;
class CComponent;
class CBaseEntity;

class CComponentTransform : public CComponent
{
private:
    CVector<float> m_PrevRot;
public:
    CVector<float> m_PrevPosition;
    CVector<float> m_Position;
    CVector<float> m_Direction;
    CVector<float> m_Right;
    CVector<float> m_Up;

    CVector<float>  m_Rot;
    CVector<float>  m_Move;
    CVector<float>  m_Scale;

public:
    CComponentTransform( CBaseEntity& parent )
        : CComponent( parent )
        , m_PrevPosition{ 0, 0, 0 }
        , m_Position{ 0, 0, 0 }
        , m_Direction{ 0, 0, -1 }
        , m_Up{ 0, 1, 0 }
        , m_Right{ 1, 0, 0 }
        , m_Rot{ 0, 0, 0 }
        , m_Move{ 0, 0, 0 }
        , m_Scale{ 1, 1, 1 }
    {

    }

    CComponentTransform( const CComponentTransform& ) = delete;
    CComponentTransform( CComponentTransform&& )      = delete;

    CComponentTransform& operator=( const CComponentTransform& ) = delete;
    CComponentTransform& operator=( CComponentTransform&& )      = delete;

    virtual void PreUpdate() override;

    // Унаследовано через CComponent
    virtual void Update() override
    {
        CComponent::Update();

        if( !m_WasUpdated && m_PrevRot == m_Rot && m_Move == CVector<float>{ 0, 0, 0 } && m_Scale == CVector<float>{ 1, 1, 1 } )
            return;

        m_WasUpdated = true;

        if( m_Rot[0] < 0 ) m_Rot[0] = 360 + m_Rot[0];
        if( m_Rot[1] < 0 ) m_Rot[1] = 360 + m_Rot[1];
        if( m_Rot[2] < 0 ) m_Rot[2] = 360 + m_Rot[2];

        m_Rot[0] = fmod( m_Rot[0], 360 );
        m_Rot[1] = fmod( m_Rot[1], 360 );
        m_Rot[2] = fmod( m_Rot[2], 360 );

        CMatrix<float> newMove  = CMatrix<float>{ m_Move }.Transposed();
        CMatrix<float> newDir   = CMatrix<float>{ CVector<float>{ 0, 0, -1 } }.Transposed();
        CMatrix<float> newUp    = CMatrix<float>{ CVector<float>{ 0, 1,  0 } }.Transposed();
        CMatrix<float> newRight = CMatrix<float>{ CVector<float>{ 1, 0,  0 } }.Transposed();

        CMatrix<float> rotation = CMatrix<float>::GetRotMatrix( m_Rot );

        newMove  = ( rotation * newMove ).Transposed();
        newDir   = ( rotation * newDir  ).Transposed();
        newUp    = ( rotation * newUp   ).Transposed();
        newRight = ( rotation * newRight).Transposed();

        m_Move    = CVector<float>{ 0, 0, 0 };
        //m_Rot     = CVector<float>{ 0, 0, 0 };
        m_Scale   = CVector<float>{ 1, 1, 1 };

        m_PrevPosition = m_Position;
        m_Position += newMove[0];
        m_Direction = newDir[0];
        m_Up        = newUp[0];
        m_Right     = newRight[0];

        m_PrevRot = m_Rot;
    };

    virtual void PostUpdate() override
    {
        CComponent::PostUpdate();

        m_WasUpdated = false;
    };

    void a() 
    { 
        m_Rot = m_Rot; 
        m_Position = m_Position;
    };
};
#endif