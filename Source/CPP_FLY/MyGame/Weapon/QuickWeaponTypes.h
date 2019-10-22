#pragma once

#include "Containers/Map.h"
#include "QuickWeaponTypes.generated.h"

class AMyProjectileBase;

USTRUCT(BlueprintType, Category=Weapon)
struct FQuickWeaponConfig
{
	GENERATED_BODY()

	/** ProjectileClass*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AMyProjectileBase> ProjectileClass;

	/** MinFireInterval*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinFireInterval = 1.0F;
	
};

USTRUCT(BlueprintType, Category=Weapon)
struct FWeaponSocketConfig
{
	GENERATED_BODY()

	/**
	* Name of the socket on the mesh
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName SocketName;

	/** SocketOffset*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector SocketOffset;
	
	/** SocketRotation*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator SocketRotation;
};

class UStaticMeshSocket;
class USkeletalMeshSocket;

/** ESocketType*/
UENUM(BlueprintType, Category=Misc)
enum class EWeaponSocketType : uint8
{
	/** StaticMesh*/
	StaticMesh UMETA(DisplayName="StaticMesh")

	/** SkeletalMesh*/
	, SkeletalMesh UMETA(DisplayName="SkeletalMesh")
};

/**
* Weapon socket info dependent on the attached actor
* (should be updated when the mesh or actor is changed!)
*/
USTRUCT(BlueprintType, Category = Weapon)
struct FAttachedWeaponSocket
{
	GENERATED_BODY()

	/**
	* Default Ctor: Creates UNINITIALIZED socket;
	*/
	FAttachedWeaponSocket();

	/**
	* Creates static mesh socket;
	*/
	FAttachedWeaponSocket(UStaticMeshSocket* InSocket);

	/**
	* Creates skeletal mesh socket;
	*/
	FAttachedWeaponSocket(USkeletalMeshSocket* InSocket);

	EWeaponSocketType GetSocketType() const { return SocketType; }
	UStaticMeshSocket* GetStaticMeshSocket() const { return StaticMeshSocket; }
	USkeletalMeshSocket* GetSkeletalMeshSocket() const { return SkeletalMeshSocket; }

private:
	UPROPERTY(EditAnywhere)
	EWeaponSocketType SocketType;

	/** The static mesh socket we are attached to*/
	UPROPERTY(EditAnywhere)
	UStaticMeshSocket* StaticMeshSocket = nullptr;

	UPROPERTY(EditAnywhere)
	USkeletalMeshSocket* SkeletalMeshSocket = nullptr;
};

/*
* Quick version of weapon inventory configuration
*/
USTRUCT(BlueprintType, Category=Weapon)
struct FQuickWeaponInventoryConfig
{
	GENERATED_BODY()
	
	/** Weapon sockets keyed by name*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName, FWeaponSocketConfig> Sockets;

	/** Weapon sockets keyed by name*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName, FQuickWeaponConfig> Weapons;

	/** Maps socket names to weapon names */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName, FName> SocketWeaponNames;

	/**
	* Mapping of weapons to indices
	*/
	TArray<FName> UsedWeaponNames;

	void RegisterSocket(FName InUniqueName, const FWeaponSocketConfig& InConfig);
	void RegisterWeapon(FName InUniqueName, const FQuickWeaponConfig& InConfig);
	const FWeaponSocketConfig& GetWeaponBySocketName(FName InSocket) const;
	void SetWeaponToSocketChecked(const FWeaponSocketConfig& InSocket, const FQuickWeaponConfig& InWeapon);
	void SetWeaponToSocketChecked(FName InSocketName, FName InWeaponName);
	const FQuickWeaponConfig& GetWeaponByIndex(int32 InIndex) const;
};
