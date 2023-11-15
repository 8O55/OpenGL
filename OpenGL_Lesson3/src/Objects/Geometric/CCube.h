#pragma once
#include "../Object.h"

class CCube : public CObject
{
public:
    float m_A;
    CCube( float a );
    virtual ~CCube() = default;

    CCube( const CCube& ) = default;
    CCube( CCube&& ) = default;

    CCube& operator=( const CCube& ) = default;
    CCube& operator=( CCube&& ) = default;

    virtual void Update() override
    {
        //CObject::Update();
        m_Components[2]->Update();
        m_Components[1]->Update();
    }

    void MakeMesh();
};


