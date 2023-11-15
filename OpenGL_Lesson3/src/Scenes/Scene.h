#pragma once
#include "../Objects/Object.h"
#include <vector>

class CScene
{
protected:
    std::vector<std::shared_ptr<CObject>> m_Objects;
    static size_t m_ScenesCount;
    size_t m_ID;
public:
    CScene();

    virtual void PreUpdate();
    virtual void Update();
    virtual void Draw();

    size_t ID() const { return m_ID; };
    static size_t ScenesCount() { return m_ScenesCount; };

    size_t FindObjectID( std::shared_ptr<CObject> object );
    void AddObject( std::shared_ptr<CObject> object );
    void RemoveObject( std::shared_ptr<CObject> object );

    std::shared_ptr<CObject> GetObjectByID( size_t objectID );
};