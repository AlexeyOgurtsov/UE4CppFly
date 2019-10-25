#include "QuickWeaponComponent.h"
#include "QuickWeaponTypesLib.h"
#include "MyGameBase/Weapon/MyProjectileBase.h"
#include "Util/Core/LogUtilLib.h"

#include "Engine/World.h"

#include "Math/Transform.h"
#include "Math/Vector.h"
#include "Math/Rotator.h"

UQuickWeaponComponent::UQuickWeaponComponent()
{
}

void UQuickWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	Weapons.Reset();
	for(const TPair<FName, FQuickWeaponConfig>& NameConfig : Config.Weapons)
	{
		Weapons.Add(NameConfig.Key, UQuickWeaponTypesLib::CreateWeaponState(this, NameConfig.Key, NameConfig.Value));
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
	checkf(Mesh, TEXT("Passed Mesh pointer must be valid"));
	const FWeaponSocketConfig& SocketConfig = Config.Sockets[InWeaponSocketName];
	FAttachedWeaponSocket const AttachedSocket = UQuickWeaponTypesLib::CreateAttachedSocketByName(Mesh, InWeaponSocketName, SocketConfig);
	WeaponSockets.Add(InWeaponSocketName, AttachedSocket);
}

void UQuickWeaponComponent::AttachSocketToSkeletalMesh(FName InWeaponSocketName, USkeletalMeshComponent* Mesh)
{
	checkf(Mesh, TEXT("Passed Mesh pointer must be valid"));
	const FWeaponSocketConfig& SocketConfig = Config.Sockets[InWeaponSocketName];
	FAttachedWeaponSocket const AttachedSocket = UQuickWeaponTypesLib::CreateAttachedSkeletalSocketByName(Mesh, InWeaponSocketName, SocketConfig);
	WeaponSockets.Add(InWeaponSocketName, AttachedSocket);
}
