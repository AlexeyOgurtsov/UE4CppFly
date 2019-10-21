#pragma once

#include "Components/ActorComponent.h"
#include "MyGameBase/I/IWeaponInventory.h"
#include "WeaponComponent.generated.h"

UCLASS(Category=Weapon, ClassGroup=(Weapon), meta=(BlueprintSpawnableComponent))
class UWeaponComponent : 
	public UActorComponent
,	public IWeaponInventory
{
	GENERATED_BODY()
	
public:
	UWeaponComponent();
	
	// ~ IWeaponInventory Begin
	virtual void Fire_Implementation(int32 InWeaponIndex) override;
	// ~ IWeaponInventory End

protected:
private:
};

