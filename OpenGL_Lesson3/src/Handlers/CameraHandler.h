#pragma once
#include <GL/freeglut.h>
#include <vector>
#include <memory>
#include "../Objects/Cameras/CameraObject.h"

class CCameraHandler
{
protected:
    std::vector<std::shared_ptr<CCameraObject>> m_Cameras;
    size_t m_currentScene;
public:
    CCameraHandler();

    void PreUpdate()
    {
        if( m_Cameras.size() == 0 || m_Cameras.size() == m_currentScene )
            return;

        m_Cameras[m_currentScene]->PreUpdate();
    }

    void Update()
    {
        if( m_Cameras.size() == 0 )
            return;

        for( auto& camera : m_Cameras )
            camera->Update();
    };

    void PostUpdate()
    {
        if( m_Cameras.size() == 0 )
            return;

        for( auto& camera : m_Cameras )
            camera->PostUpdate();
    };

    void Draw()
    {
        if( m_Cameras.size() == 0 )
            return;

        for( auto& camera : m_Cameras )
            camera->Draw();
    }

    void SwitchCameraTo( size_t cameraId )
    {
        if( IsCameraExist( cameraId ) )
            CCameraObject::m_CurrentCameraID = cameraId;
    }

    bool IsCameraExist( size_t cameraId )
    {
        for( size_t i = 0; i < m_Cameras.size(); ++i )
            if( m_Cameras[i]->m_ID == cameraId )
                return true;
        return false;
    }

    void AddCamera( std::shared_ptr<CCameraObject> scene )
    {
        m_Cameras.push_back( scene );
    }

    std::shared_ptr<CCameraObject> GetCameraByID( size_t id )
    {
        if( !IsCameraExist( id ) )
            return nullptr;

        return m_Cameras[id];
    }
};



