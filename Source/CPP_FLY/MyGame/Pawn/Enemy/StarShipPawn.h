#pragma once

/**
* Pawn that is used for the player by default.
*/

#include "MyGameBase/Pawn/TrackFlyPawn.h"
#include "StarShipPawn.generated.h"

class UStaticMeshComponent;
class UCameraComponent;
class USpringArmComponent;
class UCapsuleComponent;

UCLASS()
class AStarShipPawn : public ATrackFlyPawn
{
	GENERATED_BODY()

public:
	AStarShipPawn();

	virtual void PostInitializeComponents() override;

private:
	// ~ Components Begin
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = true), Category = Visual)
	UStaticMeshComponent* Mesh = nullptr;

	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = true), Category = Collision)
	UCapsuleComponent* ProxCapsule = nullptr;
	// ~ Components End
};
