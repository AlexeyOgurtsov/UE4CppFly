#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "QuickWeaponTypes.h"
#include "QuickWeaponTypesLib.generated.h"

class UStaticMeshComponent;
class USkeletalMeshComponent;
class UQuickWeaponComponent;
class UMeshComponent;

UCLASS()
class UQuickWeaponTypesLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Weapon)
	static FAttachedWeaponSocket CreateAttachedSocketByName(EWeaponSocketAttachMode InAttachMode, UStaticMeshComponent* Mesh, FName SocketName, const FWeaponSocketConfig& InConfig);

	UFUNCTION(BlueprintCallable, Category = Weapon)
	static FAttachedWeaponSocket CreateAttachedSkeletalSocketByName(EWeaponSocketAttachMode InAttachMode, USkeletalMeshComponent* Mesh, FName SocketName, const FWeaponSocketConfig& InConfig);

	UFUNCTION(BlueprintCallable, Category = Weapon, Meta=(WorldContext = WorldContextObject))
	static FQuickWeaponState CreateWeaponState(UObject* WorldContextObject, FName InName, const FQuickWeaponConfig& InConfig);

	/**
	* If NAME_None is used for the component name, then the first component will be used.
	*
	* WeaponName will be used as name both for socket and the weapon.
	*/
	UFUNCTION(BlueprintCallable, Category = Weapon)
	static void AddSocketWithWeapon(UQuickWeaponComponent* WeaponComponent, FName InWeaponName, const FQuickWeaponConfig& InWeapon, const FWeaponSocketConfig& InSocket, FName InComponentName = NAME_None);
};
