#pragma once
#include "../Object.h"

class CBaseLight : public CObject
{
public:
    CBaseLight();
    virtual ~CBaseLight() = default;

    CBaseLight( const CBaseLight& ) = delete;
    CBaseLight( CBaseLight&& ) = delete;

    CBaseLight& operator=( const CBaseLight& ) = delete;
    CBaseLight& operator=( CBaseLight&& ) = delete;

    virtual void PreUpdate()
    {
        CObject::PreUpdate();
    }

    virtual void Update() override
    {
        CObject::Update();
    }

    virtual void InitComponents() override;
};


