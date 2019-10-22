#include "QuickWeaponTypesLib.h"
#include "Util/Core/LogUtilLib.h"

#include "Engine/StaticMesh.h"
#include "Engine/StaticMeshSocket.h"
#include "Engine/SkeletalMesh.h"
#include "Engine/SkeletalMeshSocket.h"

FAttachedWeaponSocket UQuickWeaponTypesLib::CreateAttachedSocketByName(UStaticMesh* Mesh, FName SocketName)
{
	M_NOT_IMPL(); return FAttachedWeaponSocket();
}

FAttachedWeaponSocket UQuickWeaponTypesLib::CreateAttachedSkeletalSocketByName(USkeletalMesh* Mesh, FName SocketName)
{
	M_NOT_IMPL(); return FAttachedWeaponSocket();
}
