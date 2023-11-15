#pragma once
#include <GL/freeglut.h>
#include <vector>
#include <memory>
#include "../Scenes/Scene.h"

class CSceneHandler
{
protected:
    std::vector<std::shared_ptr<CScene>> m_Scenes;
    size_t m_currentScene;
public:
    CSceneHandler();

    void PreUpdate()
    {
        if( m_Scenes.size() == 0 || m_Scenes.size() == m_currentScene )
            return;

        m_Scenes[m_currentScene]->PreUpdate();
    }

    void Update()
    {
        if( m_Scenes.size() == 0 || m_Scenes.size() == m_currentScene )
            return;

        m_Scenes[m_currentScene]->Update();
    };

    

    void Draw()
    {
        if( m_Scenes.size() == 0 || m_Scenes.size() == m_currentScene )
            return;

        m_Scenes[m_currentScene]->Draw();
    }

    void SwitchSceneTo( size_t sceneId )
    {
        if( IsSceneExist( sceneId ) )
            m_currentScene = sceneId;
    }

    bool IsSceneExist( size_t sceneId )
    {
        for( size_t i = 0; i < m_Scenes.size(); ++i )
            if( m_Scenes[i]->ID() == sceneId )
                return true;
    }

    void AddScene( std::shared_ptr<CScene> scene )
    {
        m_Scenes.push_back( scene );
    }

    std::shared_ptr<CScene> GetSceneByID( size_t id )
    {
        if( id >= m_Scenes.size() )
            return nullptr;

        return m_Scenes[id];
    }
};



