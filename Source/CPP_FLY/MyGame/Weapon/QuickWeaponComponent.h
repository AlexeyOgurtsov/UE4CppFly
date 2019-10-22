#pragma once

#include "MyGameBase/Weapon/WeaponComponent.h"
#include "QuickWeaponTypes.h"
#include "QuickWeaponComponent.generated.h"

UCLASS(Category=Weapon, ClassGroup=(Weapon), meta=(BlueprintSpawnableComponent))
class UQuickWeaponComponent : 
	public UWeaponComponent
{
	GENERATED_BODY()
	
public:
	UQuickWeaponComponent();
	
	// ~ IWeaponInventory Begin
	virtual void Fire_Implementation(int32 InWeaponIndex) override;
	// ~ IWeaponInventory End

protected:
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, Meta=(AllowPrivateAccess = true))
	FQuickWeaponInventoryConfig Config;
};

