#pragma once
#include "../Object.h"

class CCube : public CObject
{
public:
    float m_A;
    CCube( float a );
    virtual ~CCube() = default;

    CCube( const CCube& ) = delete;
    CCube( CCube&& ) = delete;

    CCube& operator=( const CCube& ) = delete;
    CCube& operator=( CCube&& ) = delete;

    virtual void Update() override
    {
        CObject::Update();
    }

    void MakeMesh();

    virtual void InitComponents() override;
};


