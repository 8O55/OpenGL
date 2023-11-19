#include "CCube.h"
#include "../Components/ComponentTransform.h"
#include "../Components/ComponentMesh.h"
#include "../Components/ComponentLight.h"

CCube::CCube( float a ) : CObject(), m_A{ a }
{
    InitComponents();
    MakeMesh();
}

void CCube::InitComponents()
{
    AddAloneComponent<CComponentTransform>( *this );
    AddAloneComponent<CComponentMesh3D<float>>( *this );
}

void CCube::MakeMesh()
{
    std::shared_ptr<CComponentMesh3D<float>> mesh = GetComponent<CComponentMesh3D<float>>();

    if( !mesh )
        return;

    std::vector<CTriangle3D<float>> triangles = {   // FRONT
                                                    CTriangle3D<float>{ { { +m_A, +m_A, +m_A }, { -m_A, +m_A, +m_A }, { -m_A, -m_A, +m_A } }, CColor{ CColor::cRED } },
                                                    CTriangle3D<float>{ { { -m_A, -m_A, +m_A }, { +m_A, -m_A, +m_A }, { +m_A, +m_A, +m_A } }, CColor{ CColor::cRED } },
                                                    // RIGHT
                                                    CTriangle3D<float>{ { { +m_A, +m_A, -m_A }, { +m_A, +m_A, +m_A }, { +m_A, -m_A, +m_A } }, CColor{ CColor::cRED } },
                                                    CTriangle3D<float>{ { { +m_A, -m_A, +m_A }, { +m_A, -m_A, -m_A }, { +m_A, +m_A, -m_A } }, CColor{ CColor::cRED } },
                                                    // TOP
                                                    CTriangle3D<float>{ { { +m_A, +m_A, -m_A }, { -m_A, +m_A, -m_A }, { -m_A, +m_A, +m_A } }, CColor{ CColor::cRED } },
                                                    CTriangle3D<float>{ { { -m_A, +m_A, +m_A }, { +m_A, +m_A, +m_A }, { +m_A, +m_A, -m_A } }, CColor{ CColor::cRED } },
                                                    // BACK
                                                    CTriangle3D<float>{ { { -m_A, +m_A, -m_A }, { +m_A, +m_A, -m_A }, { +m_A, -m_A, -m_A } }, CColor{ CColor::cRED } },
                                                    CTriangle3D<float>{ { { +m_A, -m_A, -m_A }, { -m_A, -m_A, -m_A }, { -m_A, +m_A, -m_A } }, CColor{ CColor::cRED } },
                                                    // LEFT
                                                    CTriangle3D<float>{ { { -m_A, +m_A, +m_A }, { -m_A, +m_A, -m_A }, { -m_A, -m_A, -m_A } }, CColor{ CColor::cRED } },
                                                    CTriangle3D<float>{ { { -m_A, -m_A, -m_A }, { -m_A, -m_A, +m_A }, { -m_A, +m_A, +m_A } }, CColor{ CColor::cRED } },
                                                    // BOTTOM
                                                    CTriangle3D<float>{ { { +m_A, -m_A, -m_A }, { +m_A, -m_A, +m_A }, { -m_A, -m_A, +m_A } }, CColor{ CColor::cRED } },
                                                    CTriangle3D<float>{ { { -m_A, -m_A, +m_A }, { -m_A, -m_A, -m_A }, { +m_A, -m_A, -m_A } }, CColor{ CColor::cRED } },
                                                };

    for( const auto& triangle : triangles )
        mesh->AddTriangle( triangle );

    mesh->SetMeshType( CComponentMesh3D<float>::MeshType::mtSolid | CComponentMesh3D<float>::MeshType::mtWired );
    mesh->SetLineWidth( 2.0f );
    mesh->Subdivide();
    mesh->Subdivide();



    GetComponent<CComponentTransform>()->MakeUpdated();
    //GetComponent<CComponentMesh3D<float>>()->Update();
}



