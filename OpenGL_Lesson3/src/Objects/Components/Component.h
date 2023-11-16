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
    template<typename type>
    type* GetParent()
    {
        return dynamic_cast< type* >( &m_Parent );
    }

    template<typename componentType, typename parentType, class... _Types>
    std::shared_ptr<componentType> GetAddParentComponent( _Types&... _Args)
    {
        if( GetParent<parentType>() )
            return GetParent<parentType>()->GetAddComponent<componentType>( _Args... );
        return nullptr;
    }

    template<typename componentType, typename parentType>
    std::shared_ptr<componentType> GetParentComponent( )
    {
        if( GetParent<parentType>() )
            return GetParent<parentType>()->GetComponent<componentType>();
        return nullptr;
    }

    bool WasUpdated() const { return m_WasUpdated; }
    void MakeUpdated( bool state = true ) { m_WasUpdated = state; }
};
#endif