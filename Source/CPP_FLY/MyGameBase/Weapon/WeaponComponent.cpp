#include "WeaponComponent.h"
#include "Util/Core/LogUtilLib.h"

UWeaponComponent::UWeaponComponent()
{
	bAutoRegister = true;
}

void UWeaponComponent::Fire_Implementation(int32 InWeaponIndex)
{
	M_TO_BE_IMPL(TEXT("Fire: WeaponIndex=%d"), InWeaponIndex);
}
