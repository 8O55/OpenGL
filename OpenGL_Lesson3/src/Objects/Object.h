#pragma once
#include <vector>

#include "Components/ComponentTransform.h"
#include <memory>
#include "BaseEntity.h"

class CObject;

class CComponent;
class CComponentTransform;

class CObject : public CBaseEntity
{
public:
    

    CObject()
        : CBaseEntity()
    {
        InitComponents();
    };

    virtual void InitComponents()
    {
        AddAloneComponent<CComponentTransform>( *this );
    }

    virtual void PreUpdate() override
    {
        for( auto& component : m_Components )
            component->PreUpdate();
    };

    virtual void Update() override
    {
        for( auto& component : m_Components )
            component->Update();
    };

    virtual void PostUpdate() override
    {
        for (auto& component : m_Components)
            component->PostUpdate();
    };

    virtual void Draw() override
    {
        for( auto& component : m_Components )
            component->Draw();
    }; 
};
