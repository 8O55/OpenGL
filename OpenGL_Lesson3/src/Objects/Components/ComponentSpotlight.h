#pragma once
#include "ComponentLight.h"
#include "../../Utility/Math/Vector.h"

class CComponentSpotlight : public CComponentLight
{

public:
    CComponentSpotlight( CBaseEntity& parent ) : CComponentLight{ parent } {};

    // Унаследовано через CComponent
    virtual void Update() override {};
    

    

    
};

