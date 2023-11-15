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

    // !< �������� ����� � �������
    void PushEvent( EventType event )
    {
        if( !m_MaxSize )
            return;

        while( m_Queue.size() >= m_MaxSize )
            RemoveFirst();

        m_Queue.push_back( event );
    }

    // !< ������� ����� �� ������� �� �������
    void RenoveEventAt( size_t idx )
    {
        if( idx >= m_Queue.size() )
            throw std::out_of_range("Index out of range!");

        m_Queue.erase( m_Queue.begin() + idx );
    }

    // !< ������� ������ ����� �� �������
    void RemoveFirst()
    {
        if( m_Queue.size() )
            m_Queue.erase( m_Queue.begin() );
    }

    // !< ������ �������
    size_t Size() const
    {
        return m_Queue.size();
    }
    
    // !< ������ � ����� ������� �� �������
    EventType& GetEventAt( size_t idx )
    {
        if( idx >= m_Queue.size() )
            throw std::out_of_range( "Index out of range!" );

        return m_Queue[idx];
    }

    // !< ������ � ������� ������ � �������
    EventType* Event()
    {
        return m_Queue.size() ? &m_Queue[0] : nullptr;
    }

    // !< �������� �������
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