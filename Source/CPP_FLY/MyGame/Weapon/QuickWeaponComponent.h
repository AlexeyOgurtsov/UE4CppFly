#pragma once

#include "MyGameBase/Weapon/WeaponComponent.h"
#include "QuickWeaponTypes.h"
#include "QuickWeaponComponent.generated.h"


class UActorComponent;
class UStaticMeshComponent;
class USkeletalMeshComponent;

USTRUCT(BlueprintType)
struct FWeaponComponentSocketRef
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ComponentName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName SocketName;

	bool IsBindedToComponent() const { return ! ComponentName.IsNone(); }

	/**
	* Default ctor: Constructs reference that is NOT binded to any socket
	*/
	FWeaponComponentSocketRef() {}

	FWeaponComponentSocketRef(FName InComponentName, FName InSocketName)
	: ComponentName(InComponentName)
	, SocketName(InSocketName) {}

	/**
	* Constructs reference that is binded to the socket of the given name on the first component.
	*/
	FWeaponComponentSocketRef(FName InSocketName)
	: ComponentName(NAME_None)
	, SocketName(InSocketName) {}
};

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

	/**
	* Reattach to sockets:
	* Attaches both sockets added manually via AttachSocketTo*Mesh 
	* and sockets enlisted within the SocketsToAttach.
	* 
	* WARNING! Must be called manually (typically inside the Actor's BeginPlay call)
	* (We could not call it inside this component's BeginPlay automatically
	* as the other components that are referenced inside the SocketsToAttach array
	* are not necessarily added already)
	* @see SocketsToAttach
	*/
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, Meta=(AllowPrivateAccess = true))
	FQuickWeaponInventoryConfig Config;

	UPROPERTY()
	TMap<FName, FAttachedWeaponSocket> WeaponSockets;

	UPROPERTY()
	TMap<FName, FQuickWeaponState> Weapons;
};

