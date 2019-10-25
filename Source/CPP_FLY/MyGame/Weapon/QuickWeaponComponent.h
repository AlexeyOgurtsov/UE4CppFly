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

	virtual void BeginPlay() override;
	
	// ~ Mesh attachment Begin
	UFUNCTION(BlueprintCallable, Category = MeshAttachment)
	void DetachFromMesh();

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
	FQuickWeaponState* GetWeaponBySocketName(FName InSocketName);
	const FQuickWeaponState* GetWeaponBySocketName(FName InSocketName) const;

	void FireWeaponFromSocket(const FQuickWeaponState& InWeapon, const FAttachedWeaponSocket& InSocket);
	bool CanFireWeapon(const FQuickWeaponState& InWeapon) const;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, Meta=(AllowPrivateAccess = true))
	FQuickWeaponInventoryConfig Config;

	UPROPERTY()
	TMap<FName, FAttachedWeaponSocket> WeaponSockets;

	UPROPERTY()
	TMap<FName, FQuickWeaponState> Weapons;
};

