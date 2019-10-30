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
	FVector SocketOffset = FVector::ZeroVector;
	
	/** SocketRotation*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator SocketRotation = FRotator::ZeroRotator;
};

class UStaticMeshSocket;
class USkeletalMeshSocket;
class UMeshComponent;

/** ESocketType*/
UENUM(BlueprintType, Category=Misc)
enum class EWeaponSocketType : uint8
{
	None UMETA(DisplayName="None"),

	/** StaticMesh*/
	StaticMesh UMETA(DisplayName="StaticMesh")

	/** SkeletalMesh*/
	, SkeletalMesh UMETA(DisplayName="SkeletalMesh")
};

/** EWeaponSocketAttachMode*/
UENUM(BlueprintType, Category=Misc)
enum class EWeaponSocketAttachMode : uint8
{
	/** Manual*/
	Manual UMETA(DisplayName="Manual")

	/** Automatic*/
	, Automatic UMETA(DisplayName="Automatic")
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
	FAttachedWeaponSocket(const EWeaponSocketAttachMode InAttachMode, const FWeaponSocketConfig& InSocketConfig, const UStaticMeshSocket* InSocket, UMeshComponent* InMeshComponent);

	/**
	* Creates skeletal mesh socket;
	*/
	FAttachedWeaponSocket(const EWeaponSocketAttachMode InAttachMode, const FWeaponSocketConfig& InSocketConfig, const USkeletalMeshSocket* InSocket, UMeshComponent* InMeshComponent);

	FName GetWeaponName() const { return WeaponName; }
	EWeaponSocketAttachMode GetAttachMode() const { return AttachMode; }
	const FWeaponSocketConfig& GetSocketConfig() const { return SocketConfig; }
	EWeaponSocketType GetSocketType() const { return SocketType; }
	UMeshComponent* GetMeshComponent() const { return MeshComponent; }
	const UStaticMeshSocket* GetStaticMeshSocket() const { return StaticMeshSocket; }
	const USkeletalMeshSocket* GetSkeletalMeshSocket() const { return SkeletalMeshSocket; }

	/**
	* Final rotation of the socket transform, affected by offset and rotation.
	* In World Space.
	* Must be updated from socket!
	*
	* @see: UpdateFromSocket
	*/
	const FRotator& GetLaunchRotator() const;

	/**
	* Final location of the socket transform, affected by offset and rotation.
	* In World Space.
	* Must be updated from socket!
	*
	* @see: UpdateFromSocket
	*/
	const FVector& GetLaunchLocation() const;

	/**
	* Base transform of the socket.
	* In World Space.
	* Must be updated from socket!
	*
	* @see: UpdateFromSocket
	*/
	const FTransform& GetBaseSocketTransform() const;

	/**
	* This function to be called each time before calling GetLaunchRotator()/GetLaunchLocation()/GetBaseSocketTransform()
	*/
	void UpdateFromSocket();

private:
	void UpdateBaseSocketTransform();

	UPROPERTY()
	FName WeaponName;

	/** AttachMode*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(AllowPrivateAccess=true))
	EWeaponSocketAttachMode AttachMode = EWeaponSocketAttachMode::Manual;
	
	UPROPERTY()
	FWeaponSocketConfig SocketConfig;

	UPROPERTY()
	EWeaponSocketType SocketType = EWeaponSocketType::None;

	UPROPERTY()
	mutable FVector LaunchLocation = FVector::ZeroVector;

	UPROPERTY()
	mutable FRotator LaunchRotator = FRotator::ZeroRotator;

	UPROPERTY()
	mutable FTransform BaseSocketTransform;

	/** The static mesh socket we are attached to*/
	UPROPERTY()
	const UStaticMeshSocket* StaticMeshSocket = nullptr;

	UPROPERTY()
	const USkeletalMeshSocket* SkeletalMeshSocket = nullptr;

	UPROPERTY()
	UMeshComponent* MeshComponent = nullptr;
};


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

USTRUCT(BlueprintType, Category = Weapon)
struct FQuickWeaponState
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName WeaponName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FQuickWeaponConfig Config;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LastShootTime = 0.0F;

	/**
	* Default ctor: Creates uninitialized weapon state
	*/
	FQuickWeaponState();

	/**
	* Default ctor: Creates uninitialized weapon state
	*/
	FQuickWeaponState(FName InWeaponName, const FQuickWeaponConfig& InConfig);
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

	/** Weapons keyed by name*/
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
	void SetWeaponToSocketChecked(const FWeaponSocketConfig& InSocket, const FQuickWeaponConfig& InWeapon);
	void SetWeaponToSocketChecked(FName InSocketName, FName InWeaponName);
	const FQuickWeaponConfig& GetWeaponByIndex(int32 InIndex) const;
};
