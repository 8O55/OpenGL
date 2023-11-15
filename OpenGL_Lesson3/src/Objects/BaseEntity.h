#pragma once
#include <string>

class CBaseEntity
{
public:
    CBaseEntity() {};

    virtual ~CBaseEntity() = default;

    CBaseEntity( const CBaseEntity& entity ) = default;
    CBaseEntity( CBaseEntity&& entity ) = default;

    virtual CBaseEntity& operator=( const CBaseEntity& ) = default;
    virtual CBaseEntity& operator=( CBaseEntity&& )      = default;

    virtual void PreUpdate() {};
    virtual void Update() {};
    virtual void PostUpdate() {};
    virtual void Draw()   {};
};
