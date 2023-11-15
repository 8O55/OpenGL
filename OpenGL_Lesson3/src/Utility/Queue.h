#pragma once
#include <vector>
#include <initializer_list>
#include <stdexcept>

template <typename EventType>
class CQueue
{
#define DEFAULT_MAX_SIZE    10

    std::vector<EventType> m_Queue;
    size_t m_MaxSize;

public:
    CQueue()
        : m_Queue{}
        , m_MaxSize{ DEFAULT_MAX_SIZE }
    {}

    CQueue( std::initializer_list<EventType> lst )
        : m_Queue{ lst }
        , m_MaxSize{ DEFAULT_MAX_SIZE }
    {}

    virtual ~CQueue() = default;

    // !< Добавить эвент в очереди
    void PushEvent( EventType event )
    {
        if( !m_MaxSize )
            return;

        while( m_Queue.size() >= m_MaxSize )
            RemoveFirst();

        m_Queue.push_back( event );
    }

    // !< Удалить эвент из очереди по индексу
    void RenoveEventAt( size_t idx )
    {
        if( idx >= m_Queue.size() )
            throw std::out_of_range("Index out of range!");

        m_Queue.erase( m_Queue.begin() + idx );
    }

    // !< Удалить первый эвент из очереди
    void RemoveFirst()
    {
        if( m_Queue.size() )
            m_Queue.erase( m_Queue.begin() );
    }

    // !< Размер очереди
    size_t Size() const
    {
        return m_Queue.size();
    }
    
    // !< Доступ к эвент очереди по индексу
    EventType& GetEventAt( size_t idx )
    {
        if( idx >= m_Queue.size() )
            throw std::out_of_range( "Index out of range!" );

        return m_Queue[idx];
    }

    // !< Доступ к первому эвенту в очереди
    EventType* Event()
    {
        return m_Queue.size() ? &m_Queue[0] : nullptr;
    }

    // !< Очистить очередь
    void Clear()
    {
        m_Queue.clear();
    }

    void SetMaxSize( size_t size )
    {
        m_MaxSize = size;

        while( m_Queue.size() > m_MaxSize )
            RemoveFirst();
    }

    size_t GetMaxSize()
    {
        return m_MaxSize;
    }
};