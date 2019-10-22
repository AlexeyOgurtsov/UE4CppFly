#pragma once

/**
* All weapon inventory components are to be inherited from this class.
*/

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
	
	// ~ IWeaponInventory DEFAULT implementation Begin
	// Super NEVER to be called!
	virtual void Fire_Implementation(int32 InWeaponIndex) override;
	// ~ IWeaponInventory DEFAULT End

protected:
private:
};

