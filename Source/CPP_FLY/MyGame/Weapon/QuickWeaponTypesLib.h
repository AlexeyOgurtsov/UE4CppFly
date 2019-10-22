#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "QuickWeaponTypes.h"
#include "QuickWeaponTypesLib.generated.h"

class UStaticMesh;
class USkeletalMesh;

UCLASS()
class UQuickWeaponTypesLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Weapon)
	static FAttachedWeaponSocket CreateAttachedSocketByName(UStaticMesh* Mesh, FName SocketName);

	UFUNCTION(BlueprintCallable, Category = Weapon)
	static FAttachedWeaponSocket CreateAttachedSkeletalSocketByName(USkeletalMesh* Mesh, FName SocketName);
};
