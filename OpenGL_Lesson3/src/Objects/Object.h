#pragma once
#include <vector>
#include "Components/Component.h"
#include "Components/ComponentTransform.h"
#include <memory>
#include "BaseEntity.h"

class CObject;

class CComponent;
class CComponentTransform;

class CObject : public CBaseEntity
{
public:
    std::vector<std::shared_ptr<CComponent>> m_Components;

    CObject()
        : CBaseEntity()
    {
        AddComponent( std::make_shared<CComponentTransform>( CComponentTransform{ *this } ) );
    };

    CObject( std::initializer_list<std::shared_ptr<CComponent>> components )
        : CBaseEntity()
        , m_Components { components }
    {
        AddComponent( std::make_shared<CComponentTransform>( CComponentTransform{ *this } ) );
    };

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

    size_t FindComponentID( std::shared_ptr<CComponent> component )
    {
        for( size_t i = 0; i < m_Components.size(); ++i )
            if( m_Components[i] == component )
                return i;
        return m_Components.size();
    };

    void AddComponent( std::shared_ptr<CComponent> component )
    {
        m_Components.push_back( component );
    }

    void RemoveComponent( std::shared_ptr<CComponent> component )
    {
        if( !m_Components.size() )
            return;

        size_t id = FindComponentID( component );
        if( id != m_Components.size() )
            m_Components.erase( m_Components.begin() + id );
    };

    template<typename type>
    std::shared_ptr<type> GetComponent()
    {
        for( auto& component : m_Components )
            if( std::dynamic_pointer_cast< type >( component ) )
                return std::dynamic_pointer_cast< type >( component );

        return nullptr;
    };

    // !< Попытаться получить компонент, если такого компонента нет, то добавить его
    template<typename type, class... _Types>
    std::shared_ptr<type> GetAddComponent( _Types... _Args)
    {
        std::shared_ptr<type> ptr = GetComponent<type>();

        if( !ptr ) {
            ptr = std::make_shared<type>( _Args... );
            AddComponent( ptr );
        }

        return ptr;
    };
};
