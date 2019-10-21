#include "StarShipPawn.h"

#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"

AStarShipPawn::AStarShipPawn()
{
	// ~ Capsule initialization (Root proximity component) Begin
	ProxCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("ProxCapsule"));
	ProxCapsule->InitCapsuleSize(100.0F, 700.0F);
	ProxCapsule->SetRelativeRotation(FRotator{/*Pitch=*/90.F, /*Yaw=*/0, /*Roll=*/0});
	// ~ Capsule initialization (Root proximity component) End
	SetupDefaultComponents_RootProximityAndOthers(ProxCapsule);
	
	// ~ Mesh initialization Begin
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootSceneComponent());
	// ~ Mesh initialization End
	
	// @TODO: Setup components here
}

void AStarShipPawn::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}
