#include "QuickWeaponComponent.h"
#include "QuickWeaponTypesLib.h"
#include "MyGameBase/Weapon/MyProjectileBase.h"
#include "Util/Core/LogUtilLib.h"

#include "Engine/World.h"

#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"

#include "Math/Transform.h"
#include "Math/Vector.h"
#include "Math/Rotator.h"

UQuickWeaponComponent::UQuickWeaponComponent()
{
}

void UQuickWeaponComponent::PostInitProperties()
{
	Super::PostInitProperties();

	Weapons.Reset();
	for(const TPair<FName, FQuickWeaponConfig>& NameConfig : Config.Weapons)
	{
		Weapons.Add(NameConfig.Key, UQuickWeaponTypesLib::CreateWeaponState(this, NameConfig.Key, NameConfig.Value));
	}
}

void UQuickWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UQuickWeaponComponent::ReAttachToSockets()
{
	check(GetOwner());
	UStaticMeshComponent* FirstStaticMesh = GetOwner()->FindComponentByClass<UStaticMeshComponent>();
	USkeletalMeshComponent* FirstSkeletalMesh = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();

	// Remove old sockets that are were added automatically!
	for(TMap<FName, FAttachedWeaponSocket>::TIterator SockIt = WeaponSockets.CreateIterator(); SockIt; ++SockIt)
	{
		if(SockIt->Value.GetAttachMode() == EWeaponSocketAttachMode::Automatic)
		{
			SockIt.RemoveCurrent();
		}
	}

	for(const FWeaponComponentSocketRef& SocketRef : SocketsToAttach)
	{
		UObject* SubobjectWithComponentName = nullptr;
		if(SocketRef.IsBindedToComponent())
		{
			SubobjectWithComponentName = GetOwner()->GetDefaultSubobjectByName(SocketRef.SocketName);
			if(SubobjectWithComponentName == nullptr)
			{
				M_LOG(TEXT("Component with name \"%s\" is not found"), *SocketRef.ComponentName.ToString());
			}
			else
			{
				checkf(SubobjectWithComponentName, TEXT("Subobject with component name is NOT nullptr (we are on the corresponding if branch)"));
				AttachSocketToComponent(SocketRef.SocketName, Cast<UActorComponent>(SubobjectWithComponentName));
			}
		}
		else
		{
			UMeshComponent* FirstMeshComponent = (FirstStaticMesh != nullptr) ? (Cast<UMeshComponent>(FirstStaticMesh)) : (Cast<UMeshComponent>(FirstSkeletalMesh));
			if(FirstMeshComponent == nullptr)
			{
				M_LOG(TEXT("Unable to attach socket by reference NON-binded to component: no socket-holding component found on the owning actor"));
			}
			else
			{
				AttachSocketToComponentImpl(EWeaponSocketAttachMode::Automatic, SocketRef.SocketName, FirstMeshComponent);
			}
		}
	}
}

void UQuickWeaponComponent::AttachSocketToComponent(FName InWeaponSocketName, UActorComponent* Component)
{
	AttachSocketToComponentImpl(EWeaponSocketAttachMode::Manual, InWeaponSocketName, Component);
}

void UQuickWeaponComponent::AttachSocketToComponentImpl(EWeaponSocketAttachMode InAttachMode, FName InWeaponSocketName, UActorComponent* Component)
{
	checkf(Component, TEXT("Passed component must be valid NON-null pointer"));
	if(Component->IsA(UStaticMeshComponent::StaticClass()))
	{
		AttachSocketToStaticMeshImpl(InAttachMode, InWeaponSocketName, CastChecked<UStaticMeshComponent>(Component));
	}
	else if(Component->IsA(USkeletalMeshComponent::StaticClass()))
	{
		AttachSocketToSkeletalMeshImpl(InAttachMode, InWeaponSocketName, CastChecked<USkeletalMeshComponent>(Component));
	}
	else
	{
		M_LOG(TEXT("Component with name \"%s\" has unsupported class \"%s\""), *Component->GetName(), *Component->GetClass()->GetName());
	}
}

void UQuickWeaponComponent::Fire_Implementation(int32 const InWeaponIndex)
{
	M_LOGFUNC_MSG(TEXT("Fire: WeaponIndex = %d"), InWeaponIndex);
	if(InWeaponIndex >= Config.UsedWeaponNames.Num() || InWeaponIndex < 0)
	{
		return;
	}

	FName const WeaponSocketName = Config.UsedWeaponNames[InWeaponIndex];
	M_LOG(TEXT("WeaponSocketName: %s"), *WeaponSocketName.ToString());

	FQuickWeaponState* Weapon = GetWeaponBySocketName(WeaponSocketName);
	const FAttachedWeaponSocket& AttachedSocket = WeaponSockets[WeaponSocketName];

	if(CanFireWeapon(*Weapon))
	{
		FireWeaponFromSocket(*Weapon, AttachedSocket);
		Weapon->LastShootTime = GetWorld()->GetTimeSeconds();
	}
}

const FQuickWeaponState* UQuickWeaponComponent::GetWeaponBySocketName(FName const InSocketName) const
{
	FName const WeaponName = Config.SocketWeaponNames[InSocketName];
	return &Weapons[WeaponName];
}

FQuickWeaponState* UQuickWeaponComponent::GetWeaponBySocketName(FName const InSocketName)
{
	FName const WeaponName = Config.SocketWeaponNames[InSocketName];
	return &Weapons[WeaponName];
}

bool UQuickWeaponComponent::CanFireWeapon(const FQuickWeaponState& InWeapon) const
{
	if(InWeapon.LastShootTime + InWeapon.Config.MinFireInterval > GetWorld()->GetTimeSeconds())
	{
		return false;
	}
	return true;
}

void UQuickWeaponComponent::FireWeaponFromSocket(const FQuickWeaponState& InWeapon, const FAttachedWeaponSocket& InSocket)
{
	FActorSpawnParameters SpawnParams;
	FTransform ProjectileTransform {InSocket.GetLaunchRotator(), InSocket.GetLaunchLocation()};
	AMyProjectileBase* const Projectile = Cast<AMyProjectileBase>(GetWorld()->SpawnActor
	(
		InWeapon.Config.ProjectileClass, 
		&ProjectileTransform,
		SpawnParams
	)); 

	if( ! IsValid(Projectile) )
	{
		M_LOG_ERROR(TEXT("IsValid returned false for the spawned projectile!"));
		return;
	}

	Projectile->Launch();
}

void UQuickWeaponComponent::DetachFromMesh()
{
	WeaponSockets.Reset();
}

void UQuickWeaponComponent::AttachSocketToMesh(FName InWeaponSocketName, UStaticMeshComponent* Mesh)
{
	return AttachSocketToStaticMeshImpl(EWeaponSocketAttachMode::Manual, InWeaponSocketName, Mesh);
}

void UQuickWeaponComponent::AttachSocketToSkeletalMesh(FName InWeaponSocketName, USkeletalMeshComponent* Mesh)
{
	return AttachSocketToSkeletalMeshImpl(EWeaponSocketAttachMode::Manual, InWeaponSocketName, Mesh);
}

void UQuickWeaponComponent::AttachSocketToStaticMeshImpl(EWeaponSocketAttachMode InAttachMode, FName InWeaponSocketName, UStaticMeshComponent* Mesh)
{
	checkf(Mesh, TEXT("Passed Mesh pointer must be valid"));
	const FWeaponSocketConfig& SocketConfig = Config.Sockets[InWeaponSocketName];
	FAttachedWeaponSocket const AttachedSocket = UQuickWeaponTypesLib::CreateAttachedSocketByName(InAttachMode, Mesh, InWeaponSocketName, SocketConfig);
	WeaponSockets.Add(InWeaponSocketName, AttachedSocket);
}

void UQuickWeaponComponent::AttachSocketToSkeletalMeshImpl(EWeaponSocketAttachMode InAttachMode, FName InWeaponSocketName, USkeletalMeshComponent* Mesh)
{
	checkf(Mesh, TEXT("Passed Mesh pointer must be valid"));
	const FWeaponSocketConfig& SocketConfig = Config.Sockets[InWeaponSocketName];
	FAttachedWeaponSocket const AttachedSocket = UQuickWeaponTypesLib::CreateAttachedSkeletalSocketByName(InAttachMode, Mesh, InWeaponSocketName, SocketConfig);
	WeaponSockets.Add(InWeaponSocketName, AttachedSocket);
}
