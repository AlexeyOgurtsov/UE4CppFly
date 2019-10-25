#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "QuickWeaponTypes.h"
#include "QuickWeaponTypesLib.generated.h"

class UStaticMeshComponent;
class USkeletalMeshComponent;

UCLASS()
class UQuickWeaponTypesLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Weapon)
	static FAttachedWeaponSocket CreateAttachedSocketByName(UStaticMeshComponent* Mesh, FName SocketName, const FWeaponSocketConfig& InConfig);

	UFUNCTION(BlueprintCallable, Category = Weapon)
	static FAttachedWeaponSocket CreateAttachedSkeletalSocketByName(USkeletalMeshComponent* Mesh, FName SocketName, const FWeaponSocketConfig& InConfig);

	UFUNCTION(BlueprintCallable, Category = Weapon, Meta=(WorldContext = WorldContextObject))
	static FQuickWeaponState CreateWeaponState(UObject* WorldContextObject, FName InName, const FQuickWeaponConfig& InConfig);
};
