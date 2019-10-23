#pragma once

#include "MyGameBase/Weapon/WeaponComponent.h"
#include "QuickWeaponTypes.h"
#include "QuickWeaponComponent.generated.h"


class UStaticMeshComponent;
class USkeletalMeshComponent;

UCLASS(Category=Weapon, ClassGroup=(Weapon), meta=(BlueprintSpawnableComponent))
class UQuickWeaponComponent : 
	public UWeaponComponent
{
	GENERATED_BODY()
	
public:
	UQuickWeaponComponent();
	
	// ~ Mesh attachment Begin
	UFUNCTION(BlueprintCallable, Category = MeshAttachment)
	void AttachSocketToMesh(FName InWeaponSocketName, UStaticMeshComponent* Mesh);

	UFUNCTION(BlueprintCallable, Category = MeshAttachment)
	void AttachSocketToSkeletalMesh(FName InWeaponSocketName, USkeletalMeshComponent* Mesh);
	// ~ Mesh attachment End
	
	// ~ IWeaponInventory Begin
	virtual void Fire_Implementation(int32 InWeaponIndex) override;
	// ~ IWeaponInventory End

protected:
private:
	void FireWeaponFromSocket(const FQuickWeaponConfig& InWeapon, const FAttachedWeaponSocket& InSocket);
	bool CanFireWeapon(const FQuickWeaponConfig& InWeapon) const;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, Meta=(AllowPrivateAccess = true))
	FQuickWeaponInventoryConfig Config;

	UPROPERTY()
	TMap<FName, FAttachedWeaponSocket> WeaponSockets;
};

