#pragma once
#include <GL/freeglut.h>
#include "../Object.h"
#include "../../Utility/Math/Matrix.h"
#include "../../Utility/Primitives/PointPrimitive.h"
#include "../Components/ComponentCameraKeyboard.h"
#include "../Components/ComponentCameraMouse.h"

class CCameraObject : public CObject
{
public:
    static size_t m_CurrentCameraID;
    size_t m_ID;

    float m_Fov;

    CCameraObject()
        : CObject()
        , m_Fov{ 30 }
        , m_ID{ ++m_CurrentCameraID }
    {
        InitComponents();
    }

    CCameraObject( const CCameraObject& ) = delete;
    CCameraObject( CCameraObject&& ) = delete;

    CCameraObject& operator=( const CCameraObject& ) = delete;
    CCameraObject& operator=( CCameraObject&& ) = delete;

    virtual void InitComponents() override
    {
        AddComponent( std::make_shared<CComponentCameraKeyboard>( *this ) );
        AddComponent( std::make_shared<CComponentCameraMouse>( *this ) );
    }

    virtual void PreUpdate() override
    {
        CObject::PreUpdate();
    }

    virtual void Update()
    {
        CObject::Update();        
    }

    virtual void Draw()
    {
        CObject::Draw();

        if( m_ID == m_CurrentCameraID && GetComponent<CComponentTransform>() )
        {
            std::shared_ptr<CComponentTransform> transform = GetComponent<CComponentTransform>();

            float x = transform->m_Position[0];
            float y = transform->m_Position[1];
            float z = transform->m_Position[2];

            float cx = x + transform->m_Direction[0];
            float cy = y + transform->m_Direction[1];
            float cz = z + transform->m_Direction[2];

            float ux = transform->m_Up[0];
            float uy = transform->m_Up[1];
            float uz = transform->m_Up[2];

            //gluLookAt( x, y, z, cx, cy, cz, 0, 1, 0 );

            gluLookAt( x, y, z, cx, cy, cz, ux, uy, uz );
        }
    }
};