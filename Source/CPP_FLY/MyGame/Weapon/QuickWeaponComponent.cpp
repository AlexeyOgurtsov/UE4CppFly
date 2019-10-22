#include "QuickWeaponComponent.h"
#include "QuickWeaponTypesLib.h"
#include "Util/Core/LogUtilLib.h"

UQuickWeaponComponent::UQuickWeaponComponent()
{
}

void UQuickWeaponComponent::Fire_Implementation(int32 InWeaponIndex)
{
	M_TO_BE_IMPL(TEXT("Fire: WeaponIndex=%d"), InWeaponIndex);
}
