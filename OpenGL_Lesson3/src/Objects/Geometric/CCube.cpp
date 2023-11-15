#include "CCube.h"
#include "../Components/ComponentTransform.h"
#include "../Components/ComponentMesh.h"
#include "../Components/ComponentLight.h"

CCube::CCube( float a ) : CObject(), m_A{ a }
{
    AddComponent( std::make_shared<CComponentMesh3D<float>>( *this ) );
    GetComponent<CComponentMesh3D<float>>()->Update();
    AddComponent( std::make_shared<CComponentLight>( CComponentLight{ *this } ) );

    MakeMesh();
}

void CCube::MakeMesh()
{
    std::shared_ptr<CComponentMesh3D<float>> mesh;

    for( auto ptr : m_Components )
        if( std::dynamic_pointer_cast<CComponentMesh3D<float>>( ptr ) ) {
            mesh = std::dynamic_pointer_cast< CComponentMesh3D<float> >( ptr );
            break;
        }
    if( !mesh )
        return;

    std::vector<CTriangle3D<float>> triangles = {   // FRONT
                                                    CTriangle3D<float>{ { +m_A, +m_A, +m_A }, { -m_A, +m_A, +m_A }, { -m_A, -m_A, +m_A } },
                                                    CTriangle3D<float>{ { -m_A, -m_A, +m_A }, { +m_A, -m_A, +m_A }, { +m_A, +m_A, +m_A } },
                                                    // RIGHT
                                                    CTriangle3D<float>{ { +m_A, +m_A, -m_A }, { +m_A, +m_A, +m_A }, { +m_A, -m_A, +m_A } },
                                                    CTriangle3D<float>{ { +m_A, -m_A, +m_A }, { +m_A, -m_A, -m_A }, { +m_A, +m_A, -m_A } },
                                                    // TOP
                                                    CTriangle3D<float>{ { +m_A, +m_A, -m_A }, { -m_A, +m_A, -m_A }, { -m_A, +m_A, +m_A } },
                                                    CTriangle3D<float>{ { -m_A, +m_A, +m_A }, { +m_A, +m_A, +m_A }, { +m_A, +m_A, -m_A } },
                                                    // BACK
                                                    CTriangle3D<float>{ { -m_A, +m_A, -m_A }, { +m_A, +m_A, -m_A }, { +m_A, -m_A, -m_A } },
                                                    CTriangle3D<float>{ { +m_A, -m_A, -m_A }, { -m_A, -m_A, -m_A }, { -m_A, +m_A, -m_A } },
                                                    // LEFT
                                                    CTriangle3D<float>{ { -m_A, +m_A, +m_A }, { -m_A, +m_A, -m_A }, { -m_A, -m_A, -m_A } },
                                                    CTriangle3D<float>{ { -m_A, -m_A, -m_A }, { -m_A, -m_A, +m_A }, { -m_A, +m_A, +m_A } },
                                                    // BOTTOM
                                                    CTriangle3D<float>{ { +m_A, -m_A, -m_A }, { +m_A, -m_A, +m_A }, { -m_A, -m_A, +m_A } },
                                                    CTriangle3D<float>{ { -m_A, -m_A, +m_A }, { -m_A, -m_A, -m_A }, { +m_A, -m_A, -m_A } },
                                                };

    for( const auto& triangle : triangles )
        mesh->AddTriangle( triangle );
}

