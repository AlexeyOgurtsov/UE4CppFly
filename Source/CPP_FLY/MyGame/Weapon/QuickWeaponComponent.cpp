#include "QuickWeaponComponent.h"
#include "QuickWeaponTypesLib.h"
#include "MyGameBase/Weapon/MyProjectileBase.h"
#include "Util/Core/LogUtilLib.h"

#include "Engine/World.h"

#include "Math/Transform.h"
#include "Math/Vector.h"
#include "Math/Rotator.h"

namespace
{
	class FImpl
	{
	public:
		static void CalcSocketLaunchLocationAndRotation(const FAttachedWeaponSocket& InSocket, FVector& OutLaunchLocation, FRotator& OutLaunchRotation)
		{
			M_TO_BE_IMPL(TEXT("CalcSocketLaunchLocationAndRotation"));
		}
	};
} // anonymous

UQuickWeaponComponent::UQuickWeaponComponent()
{
}

void UQuickWeaponComponent::Fire_Implementation(int32 InWeaponIndex)
{
	M_LOGFUNC_MSG(TEXT("Fire: WeaponIndex = %d"), InWeaponIndex);
	if(InWeaponIndex >= Config.UsedWeaponNames.Num() || InWeaponIndex < 0)
	{
		return;
	}

	FName const WeaponSocketName = Config.UsedWeaponNames[InWeaponIndex];
	M_LOG(TEXT("WeaponSocketName: %s"), *WeaponSocketName.ToString());

	const FQuickWeaponConfig& WeaponConfig = Config.GetWeaponBySocketName(WeaponSocketName);
	const FAttachedWeaponSocket& AttachedSocket = WeaponSockets[WeaponSocketName];

	if(CanFireWeapon(WeaponConfig))
	{
		FireWeaponFromSocket(WeaponConfig, AttachedSocket);
	}
}

bool UQuickWeaponComponent::CanFireWeapon(const FQuickWeaponConfig& InWeapon) const
{
	M_TO_BE_IMPL(TEXT("CanFireWeapon")); return true;
}

void UQuickWeaponComponent::FireWeaponFromSocket(const FQuickWeaponConfig& InWeapon, const FAttachedWeaponSocket& InSocket)
{
	FVector LaunchLocation;
	FRotator LaunchRotator;
	FImpl::CalcSocketLaunchLocationAndRotation(InSocket, LaunchLocation, LaunchRotator);

	FActorSpawnParameters SpawnParams;
	FTransform ProjectileTransform {LaunchRotator, LaunchLocation, FVector::OneVector};
	AMyProjectileBase* const Projectile = Cast<AMyProjectileBase>(GetWorld()->SpawnActor
	(
		InWeapon.ProjectileClass, 
		&ProjectileTransform,
		SpawnParams
	)); 

	if( ! IsValid(Projectile) )
	{
		M_LOG_ERROR(TEXT("IsValid returned false for the spawned projectile!"));
		return;
	}

	M_TO_BE_IMPL(TEXT("Initialize projectile!"));
}

void UQuickWeaponComponent::AttachSocketToMesh(FName InWeaponSocketName, UStaticMeshComponent* Mesh)
{
	M_NOT_IMPL();
}

void UQuickWeaponComponent::AttachSocketToSkeletalMesh(FName InWeaponSocketName, USkeletalMeshComponent* Mesh)
{
	M_NOT_IMPL();
}
