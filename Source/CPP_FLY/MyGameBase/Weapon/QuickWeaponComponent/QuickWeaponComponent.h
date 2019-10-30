#pragma once

#include "MyGameBase/Weapon/WeaponComponent.h"
#include "QuickWeaponTypes.h"
#include "QuickWeaponComponent.generated.h"


class UActorComponent;
class UStaticMeshComponent;
class USkeletalMeshComponent;

/**
* Usage scenario:
* 1. Fill Config : FQuickWeaponInventoryConfig (maybe declaratively)	
* 2. Fill SocketsToAttach with sockets (maybe declaratively)
* 	// Add socket on unknown component:
* 	Weapon->SocketsToAttach.Add(FWeaponComponentSocketRef{TEXT("FrontGun")});
* 	// Add socket on the given component:
* 	Weapon->SocketsToAttach.Add(FWeaponComponentSocketRef{MeshComp, TEXT("TopGun")});
* 3. Call ReAttachToSockets (typically inside the Actor's BeginPlay)
* 	Weapon->ReAttachToSockets();
*/
UCLASS(Category=Weapon, ClassGroup=(Weapon), meta=(BlueprintSpawnableComponent))
class UQuickWeaponComponent : 
	public UWeaponComponent
{
	GENERATED_BODY()
	
public:
	UQuickWeaponComponent();

	virtual void PostInitProperties() override;
	virtual void BeginPlay() override;
	
	// ~ Mesh attachment Begin
	UFUNCTION(BlueprintCallable, Category = MeshAttachment)
	void DetachFromMesh();

	/*
	* Attach socket to mesh component
	*
	* @see SocketsToAttach
	*/
	UFUNCTION(BlueprintCallable, Category = MeshAttachment)
	void AttachSocketToMesh(FName InWeaponSocketName, UStaticMeshComponent* Mesh);

	/*
	* Attach socket to mesh component
	*
	* @see AttachSocketToMesh
	* @see SocketsToAttach
	*/
	UFUNCTION(BlueprintCallable, Category = MeshAttachment)
	void AttachSocketToSkeletalMesh(FName InWeaponSocketName, USkeletalMeshComponent* Mesh);


	UFUNCTION(BlueprintCallable, Category = MeshAttachment)
	void AttachSocketToComponent(FName InWeaponSocketName, UActorComponent* Component);

	/**
	* This set of sockets is to be automatically attached on call to ReAttachToSockets.
	* So you can define them here declaratively.
	* @see: ReAttachToSockets
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon)
	TArray<FWeaponComponentSocketRef> SocketsToAttach;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon)
	FQuickWeaponInventoryConfig Config;

	/**
	* Reattach to sockets:
	* Attaches sockets enlisted within the SocketsToAttach.
	*
	* It does NOT clear sockets added manually!
	* 
	* WARNING! Must be called manually (typically inside the Actor's BeginPlay call)
	* (We could not call it inside this component's BeginPlay automatically
	* as the other components that are referenced inside the SocketsToAttach array
	* are not necessarily added yet)
	* @see SocketsToAttach
	*/
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void ReAttachToSockets();
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

	void AttachSocketToSkeletalMeshImpl(EWeaponSocketAttachMode InAttachMode, FName InWeaponSocketName, USkeletalMeshComponent* Mesh);
	void AttachSocketToStaticMeshImpl(EWeaponSocketAttachMode InAttachMode, FName InWeaponSocketName, UStaticMeshComponent* Mesh);
	void AttachSocketToComponentImpl(EWeaponSocketAttachMode InAttachMode, FName InWeaponSocketName, UActorComponent* Component);

	UPROPERTY()
	TMap<FName, FAttachedWeaponSocket> WeaponSockets;

	UPROPERTY()
	TMap<FName, FQuickWeaponState> Weapons;
};

