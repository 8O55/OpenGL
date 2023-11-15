#ifndef COMPONENT
#define COMPONENT

#include <memory>
#include <vector>
#include "../BaseEntity.h"

class CComponent : public CBaseEntity
{
protected:
    CBaseEntity& m_Parent;
    std::vector<std::shared_ptr<CComponent>> m_Components;
public:
    CComponent( CBaseEntity& parent ) : CBaseEntity(), m_Parent{ parent } {};

    CComponent( const CComponent& ) = default;
    CComponent( CComponent&& )      = default;

    CComponent& operator=( const CComponent& ) = default;
    CComponent& operator=( CComponent&& )      = default;

    virtual ~CComponent() = default;
    
    virtual void InitComponents()
    {}

    virtual void PreUpdate()
    {
        for( auto& component : m_Components )
            component->PreUpdate();
    };

    virtual void Update()
    {
        for( auto& component : m_Components )
            component->Update();
    };

    virtual void PostUpdate()
    {
        for (auto& component : m_Components)
            component->PostUpdate();
    };

    virtual void Draw()
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

    // !< Попытаться получить компонент
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

    // !< Попытаться преобразовать и получить объект родителя указанного типа
    template<typename type>
    type* GetParent()
    {
        return dynamic_cast< type* >( &m_Parent );
    }

    template<typename componentType, typename parentType, class... _Types>
    std::shared_ptr<componentType> GetAddParentComponent( _Types... _Args)
    {
        if( GetParent<parentType>() )
            return GetParent<parentType>()->GetAddComponent<componentType>( _Args... );
    }
};
#endif