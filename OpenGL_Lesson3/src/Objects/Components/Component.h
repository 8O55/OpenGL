#ifndef COMPONENT
#define COMPONENT

#include <memory>
#include <vector>
#include "../BaseEntity.h"

class CComponent : public CBaseEntity
{
protected:
    CBaseEntity& m_Parent;
    bool m_WasUpdated;
public:
    CComponent( CBaseEntity& parent ) : CBaseEntity(), m_Parent{ parent }, m_WasUpdated{ true } {};

    CComponent( const CComponent& ) = delete;
    CComponent( CComponent&& )      = delete;

    CComponent& operator=( const CComponent& ) = delete;
    CComponent& operator=( CComponent&& )      = delete;

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
        m_WasUpdated = false;
        for (auto& component : m_Components)
            component->PostUpdate();
    };

    virtual void Draw()
    {
        for( auto& component : m_Components )
            component->Draw();
    };

    // !< Попытаться преобразовать и получить объект родителя указанного типа
    template<typename _parentType>
    _parentType* GetParent()
    {
        if( dynamic_cast< _parentType* >( &m_Parent ) )
            return dynamic_cast< _parentType* >( &m_Parent );
        return nullptr;
    }

    template<typename componentType, class... _Types>
    std::shared_ptr<componentType> GetAddParentComponent( _Types&... _Args )
    {
        return nullptr;
    }

    template<typename componentType, typename _parentType, typename... _parentTypes, class... _Types>
    std::shared_ptr<componentType> GetAddParentComponent( _Types&... _Args )
    {
        if( GetParent<_parentType>() )
            return GetParent<_parentType>()->GetAddComponent<componentType>( _Args... );
        else
            return GetAddParentComponent<componentType, _parentTypes...>( _Args... );
        return nullptr;
    }

    template<typename componentType>
    std::shared_ptr<componentType> GetParentComponent()
    {
        return nullptr;
    }

    template<typename componentType, typename _parentType, typename... _parentTypes>
    std::shared_ptr<componentType> GetParentComponent()
    {
        if( GetParent<_parentType>() )
            return GetParent<_parentType>()->GetComponent<componentType>();
        else
            return GetParentComponent<componentType, _parentTypes...>();
        return nullptr;
    }

    template<typename componentType, typename... _ParentsTypes> 
    std::shared_ptr<componentType> GetComponentThrowParents( bool isFirstCall = true )
    {
        
    }

    bool WasUpdated() const { return m_WasUpdated; }
    void MakeUpdated( bool state = true ) { m_WasUpdated = state; }
};
#endif