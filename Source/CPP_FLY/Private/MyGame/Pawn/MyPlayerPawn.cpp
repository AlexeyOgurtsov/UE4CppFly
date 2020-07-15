#include "MyPlayerPawn.h"

#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"

AMyPlayerPawn::AMyPlayerPawn()
{
	// ~ Capsule initialization (Root proximity component) Begin
	ProxCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("ProxCapsule"));
	ProxCapsule->InitCapsuleSize(100.0F, 700.0F);
	ProxCapsule->SetRelativeRotation(FRotator{/*Pitch=*/00.F, /*Yaw=*/0, /*Roll=*/0});
	// ~ Capsule initialization (Root proximity component) End
	
	// ~ Mesh initialization Begin
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));	
	// ~ Mesh initialization End
	
	SetupDefaultComponents(ProxCapsule, Mesh);
}

void AMyPlayerPawn::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}
