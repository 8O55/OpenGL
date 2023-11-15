#include "Scene.h"
#include "../Objects/Components/ComponentMesh.h"
#include <memory>

size_t CScene::m_ScenesCount = 0;

CScene::CScene()
    : m_ID{ m_ScenesCount }
{
    m_ScenesCount++;
}

void CScene::PreUpdate()
{
    for( const auto& object : m_Objects )
        object->PreUpdate();
}

void CScene::Update()
{
    for( const auto& object : m_Objects )
        object->Update();
}

void CScene::Draw()
{
    for( const auto& object : m_Objects )
        object->Draw();
}

void CScene::AddObject( std::shared_ptr<CObject> object )
{
    m_Objects.push_back( std::dynamic_pointer_cast<CObject>( object ) );
}

size_t CScene::FindObjectID( std::shared_ptr<CObject> component )
{
    for( size_t i = 0; i < m_Objects.size(); ++i )
        if( m_Objects[i] == component )
            return i;
    return m_Objects.size();
};

void CScene::RemoveObject( std::shared_ptr<CObject> object )
{
    if( !m_Objects.size() )
        return;

    size_t id = FindObjectID( object );
    if( id != m_Objects.size() )
        m_Objects.erase( m_Objects.begin() + id );
}

std::shared_ptr<CObject> CScene::GetObjectByID( size_t objectID )
{
    if( objectID >= m_Objects.size() )
        return nullptr;

    return m_Objects[objectID];
}
