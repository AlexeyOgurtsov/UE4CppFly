#include "QuickWeaponTypesLib.h"
#include "QuickWeaponComponent.h"
#include "Util/Core/LogUtilLib.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/StaticMeshSocket.h"
#include "Engine/SkeletalMeshSocket.h"

#include "Math/Transform.h"
#include "Math/Vector.h"
#include "Math/Rotator.h"

void UQuickWeaponTypesLib::AddSocketWithWeapon(UQuickWeaponComponent* WeaponComponent, FName InWeaponName, const FQuickWeaponConfig& InWeapon, const FWeaponSocketConfig& InSocket, FName InComponentName)
{
	//checkf(WeaponComponent, TEXT("Passed weapon component must be valid NON-null pointer"));

	WeaponComponent->Config.Sockets.Add(InWeaponName, InSocket);
	WeaponComponent->Config.Weapons.Add(InWeaponName, InWeapon);
	WeaponComponent->Config.UsedWeaponNames.Add(InWeaponName);
	WeaponComponent->Config.SocketWeaponNames.Add(InWeaponName, InWeaponName);
	WeaponComponent->SocketsToAttach.Add(FWeaponComponentSocketRef{InSocket.SocketName, InComponentName});
}

FAttachedWeaponSocket UQuickWeaponTypesLib::CreateAttachedSocketByName(EWeaponSocketAttachMode InAttachMode, UStaticMeshComponent* Mesh, FName SocketName, const FWeaponSocketConfig& InConfig)
{
	checkf(Mesh, TEXT("Mesh must be valid"));
	const UStaticMeshSocket* Socket = Mesh->GetSocketByName(SocketName);
	checkf(Socket, TEXT("Socket \"%SocketName\" must exist"), *SocketName.ToString());
	FAttachedWeaponSocket AttachedSocket{InAttachMode, InConfig, Socket, Mesh};
	AttachedSocket.UpdateFromSocket();
	return AttachedSocket;
}

FAttachedWeaponSocket UQuickWeaponTypesLib::CreateAttachedSkeletalSocketByName(EWeaponSocketAttachMode InAttachMode, USkeletalMeshComponent* Mesh, FName SocketName, const FWeaponSocketConfig& InConfig)
{
	checkf(Mesh, TEXT("Mesh must be valid"));
	const USkeletalMeshSocket* Socket = Mesh->GetSocketByName(SocketName);
	checkf(Socket, TEXT("Socket \"%SocketName\" must exist"), *SocketName.ToString());
	FAttachedWeaponSocket AttachedSocket{InAttachMode, InConfig, Socket, Mesh};
	AttachedSocket.UpdateFromSocket();
	return AttachedSocket;
}

FQuickWeaponState UQuickWeaponTypesLib::CreateWeaponState(UObject* WorldContextObject, FName InName, const FQuickWeaponConfig& InConfig)
{
	return FQuickWeaponState(InName, InConfig);
}

void FAttachedWeaponSocket::UpdateFromSocket()
{
	UpdateBaseSocketTransform();
	FTransform const FinalTransform = FTransform{SocketConfig.SocketRotation, SocketConfig.SocketOffset} * BaseSocketTransform;
	LaunchLocation = FinalTransform.GetTranslation();
	LaunchRotator = FinalTransform.Rotator();
}

void FAttachedWeaponSocket::UpdateBaseSocketTransform()
{
	bool bSucceeded = false;
	UStaticMeshComponent* StaticMeshComponent = nullptr;
	USkeletalMeshComponent* SkeletalMeshComponent = nullptr;
	switch(SocketType)
	{
	case EWeaponSocketType::StaticMesh:
		StaticMeshComponent = CastChecked<UStaticMeshComponent>(MeshComponent);
		bSucceeded = StaticMeshSocket->GetSocketTransform(BaseSocketTransform, StaticMeshComponent);
		checkf(bSucceeded, TEXT("UStaticMeshSocket::GetSocketTransform() must succeed!"));
		break;

	case EWeaponSocketType::SkeletalMesh:
		SkeletalMeshComponent = CastChecked<USkeletalMeshComponent>(MeshComponent);
		BaseSocketTransform = SkeletalMeshSocket->GetSocketTransform(SkeletalMeshComponent);
		break;

	default:
		checkNoEntry();
	}

}

const FRotator& FAttachedWeaponSocket::GetLaunchRotator() const
{
	return LaunchRotator;
}

const FVector& FAttachedWeaponSocket::GetLaunchLocation() const
{
	return LaunchLocation;
}

const FTransform& FAttachedWeaponSocket::GetBaseSocketTransform() const
{
	return BaseSocketTransform;
}

FAttachedWeaponSocket::FAttachedWeaponSocket()
{
}

FAttachedWeaponSocket::FAttachedWeaponSocket(EWeaponSocketAttachMode InAttachMode, const FWeaponSocketConfig& InSocketConfig, const UStaticMeshSocket* InSocket, UMeshComponent* InMeshComponent)
: AttachMode {InAttachMode}
, SocketConfig {InSocketConfig}
, SocketType {EWeaponSocketType::StaticMesh}
, StaticMeshSocket {InSocket}
, MeshComponent {InMeshComponent}
{
	checkf(InSocket, TEXT("Passed socket must be valid NON-null pointer"));
	checkf(InMeshComponent, TEXT("Passed mesh component must be valid NON-null pointer"));
}

FAttachedWeaponSocket::FAttachedWeaponSocket(EWeaponSocketAttachMode InAttachMode, const FWeaponSocketConfig& InSocketConfig, const USkeletalMeshSocket* InSocket, UMeshComponent* InMeshComponent)
: AttachMode {InAttachMode}
, SocketConfig {InSocketConfig}
, SocketType {EWeaponSocketType::SkeletalMesh}
, SkeletalMeshSocket {InSocket}
, MeshComponent {InMeshComponent}
{
	checkf(InSocket, TEXT("Passed socket must be valid NON-null pointer"));
	checkf(InMeshComponent, TEXT("Passed mesh component must be valid NON-null pointer"));
}

FQuickWeaponState::FQuickWeaponState()
{
}

FQuickWeaponState::FQuickWeaponState(FName InWeaponName, const FQuickWeaponConfig& InConfig)
: WeaponName{InWeaponName}
, Config {InConfig}
{
}
