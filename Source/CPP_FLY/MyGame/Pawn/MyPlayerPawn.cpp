#include "MyPlayerPawn.h"

#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"

AMyPlayerPawn::AMyPlayerPawn()
{
	// ~ Mesh initialization Begin
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootSceneComponent());
	// ~ Mesh initialization End

	// ~ Capsule initialization Begin
	ProxCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("ProxCapsule"));
	ProxCapsule->InitCapsuleSize(100.0F, 700.0F);
	ProxCapsule->SetRelativeRotation(FRotator{/*Pitch=*/90.F, /*Yaw=*/0, /*Roll=*/0});
	SetupProximityComponentAttachment(ProxCapsule);
	// ~ Capsule initialization End
	
	// @TODO: Setup components here
}

void AMyPlayerPawn::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}