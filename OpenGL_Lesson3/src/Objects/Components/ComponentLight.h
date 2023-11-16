#pragma once
#include "Component.h"
#include "../Object.h"
#include "ComponentMesh.h"
#include "ComponentTransform.h"
#include "../../Utility/Math/Vector.h"

class CComponentTransform;

template< class T >
class CComponentMesh3D;

class CComponentLight : public CComponent
{
public:
    bool m_ShowLightPosition;
public:
    std::shared_ptr<CObject> m_LightPositionObject;

    CComponentLight( CBaseEntity& parent )
        : CComponent{ parent }
        , m_ShowLightPosition{ true }
    {
        InitComponents();
    };

    virtual void InitComponents() override
    {
        AddAloneComponent<CComponentTransform>( *this );
        if( m_LightPositionObject )
            m_LightPositionObject->ReplaceComponent( GetComponent<CComponentTransform>() );
        GetComponent<CComponentTransform>()->MakeUpdated();
    }

    virtual void PreUpdate()
    {
        std::shared_ptr<CComponentTransform> transform;

        if( !transform )
            transform = GetParentComponent<CComponentTransform, CObject>();

        if( !transform )
            transform = GetParentComponent<CComponentTransform, CComponent>();

        if( transform ) {
            GetComponent<CComponentTransform>()->m_Rot += transform->m_Rot;
            GetComponent<CComponentTransform>()->m_Position += transform->m_Position - transform->m_PrevPosition;
        }
        CComponent::PreUpdate();
    }

    // Унаследовано через CComponent
    virtual void Update() override
    {
        CComponent::Update();

        std::shared_ptr<CComponentTransform> transform;

        if( !transform )
            transform = GetAddParentComponent<CComponentTransform, CObject>( m_Parent );

        if( !transform )
            transform = GetAddParentComponent<CComponentTransform, CComponent>( m_Parent );

        

        if( m_ShowLightPosition && m_LightPositionObject )
            m_LightPositionObject->Update();

        

        /*
        for( auto component : m_ParentObject.m_Components )
            if( std::dynamic_pointer_cast< CComponentTransform >( component ) ) {
                auto parentObjectTransformPtr = std::dynamic_pointer_cast< CComponentTransform >( component );

                //CVector<float> rot  = parentObjectTransformPtr->m_Rot  + m_Rot;
                CVector<float> move = parentObjectTransformPtr->m_Move + m_Move;

                for( auto component : m_LightPositionObject->m_Components ) {
                    if( std::dynamic_pointer_cast< CComponentTransform >( component ) ) {
                        auto positionObjectTransformPtr = std::dynamic_pointer_cast< CComponentTransform >( component );
                        //posObjRot  = positionObjectTransformPtr->m_Rot  + rot;
                        posObjMove = positionObjectTransformPtr->m_Move + move;
                    }
                }

                if( m_ShowLightPosition )
                    DrawLightPosition();
            }*/


    };

    virtual void Draw()
    {
        CComponent::Draw();

        if( m_ShowLightPosition && m_LightPositionObject )
            m_LightPositionObject->Draw();
    };

    inline void ShowLightPosition( bool state = true )
    {
        m_ShowLightPosition = state;
    }

    void SetLightPositionObject( std::shared_ptr<CObject> object )
    {
        m_LightPositionObject = object;
        if( m_LightPositionObject )
            m_LightPositionObject->ReplaceComponent<CComponentTransform>( GetComponent<CComponentTransform>() );
        GetComponent<CComponentTransform>()->MakeUpdated();
    }

    bool IsLightPositionShown() const { return m_ShowLightPosition; }
    std::shared_ptr<CObject> LightPositionObject() { return m_LightPositionObject; }
};

