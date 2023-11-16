#ifndef BASE_ENTITY
#define BASE_ENTITY
#include <memory>
#include <string>

class CComponent;

class CBaseEntity
{
public:
    std::vector<std::shared_ptr<CComponent>> m_Components;

    CBaseEntity() {};

    virtual ~CBaseEntity() = default;

    CBaseEntity( const CBaseEntity& entity ) = delete;
    CBaseEntity( CBaseEntity&& entity ) = delete;

    virtual CBaseEntity& operator=( const CBaseEntity& ) = delete;
    virtual CBaseEntity& operator=( CBaseEntity&& )      = delete;

    virtual void PreUpdate() {};
    virtual void Update() {};
    virtual void PostUpdate() {};
    virtual void Draw()   {};

    size_t FindComponentID( std::shared_ptr<CComponent> component )
    {
        for( size_t i = 0; i < m_Components.size(); ++i )
            if( m_Components[i] == component )
                return i;
        return m_Components.size();
    };

    template<typename componentType, class... _Types>
    void AddComponent( _Types&... _Args )
    {
        m_Components.push_back( std::make_shared<componentType>( _Args... ) );
    }

    template<typename componentType>
    void AddComponent( std::shared_ptr<componentType> component )
    {
        m_Components.push_back( std::dynamic_pointer_cast< CComponent >( component ) );
    }

    // Добавить компонент, который должен быть единственный в своем роде
    template<typename componentType, class... _Types>
    void AddAloneComponent( _Types&... _Args )
    {
        if( !GetComponent<componentType>() )
            m_Components.push_back( std::make_shared<componentType>( _Args... ) );
    }

    // Добавить компонент, который должен быть единственный в своем роде
    template<typename componentType>
    void AddAloneComponent( std::shared_ptr<componentType> component )
    {
        if( !GetComponent<componentType>() )
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

    // Заменяет компонент указанного типа, если такого нет, то добавляет его
    template<typename componentType, class... _Types>
    void ReplaceComponent( _Types&... _Args )
    {
        std::shared_ptr<componentType> source = std::make_shared<componentType>( _Args... );
        for( auto& component : m_Components ) {
            if( std::dynamic_pointer_cast< componentType >( component ) ) {
                component = source;
                return;
            }
        }
        AddComponent( _Args... );
    }

    template<typename componentType>
    void ReplaceComponent( std::shared_ptr<componentType> source )
    {
        for( auto& component : m_Components ) {
            if( std::dynamic_pointer_cast< componentType >( component ) ) {
                component = source;
                return;
            }
        }
        AddComponent( source );
    }

    // Заменяет компонент dest на source в списке компонентов, если dest не существует, то добавляет source в спсок
    template<typename componentType>
    void ReplaceComponent( std::shared_ptr<componentType> dest, std::shared_ptr<componentType> source )
    {
        for( auto& component : m_Components ) {
            if( component.get() == source.get() ) {
                component = source;
                return;
            }
        }
        AddComponent( source );
    }

    template<typename type>
    std::shared_ptr<type> GetComponent()
    {

        for( auto& component : m_Components ) {
            if( std::dynamic_pointer_cast< type >( component ) )
                return std::dynamic_pointer_cast< type >( component );
        }
        return nullptr;
    };

    // !< Попытаться получить компонент, если такого компонента нет, то добавить его
    template<typename type, class... _Types>
    std::shared_ptr<type> GetAddComponent( _Types&... _Args )
    {
        std::shared_ptr<type> ptr = GetComponent<type>();

        if( !ptr ) {
            ptr = std::make_shared<type>( _Args... );
            AddComponent( ptr );
        }

        return ptr;
    };
};
#endif
