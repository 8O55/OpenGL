#include "BaseLight.h"
#include "../Components/ComponentTransform.h"
#include "../Components/ComponentLight.h"

CBaseLight::CBaseLight() : CObject()
{
    InitComponents();
}

void CBaseLight::InitComponents()
{
    AddAloneComponent<CComponentTransform>( *this );
    AddAloneComponent<CComponentLight>( *this );
}





