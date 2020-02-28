#pragma once

/**
* Base class of all game types.
*/

#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"

UCLASS()
class AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMyGameModeBase();

	// ~ Engine overrides Begin
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void InitGameState() override;

	virtual bool ShouldStartInCinematicMode
	(
		APlayerController* Player,
		bool& OutHidePlayer,
		bool& OutHideHud,
		bool& OutDisableMovement,
		bool& OutDIsableTurning 
	) override;

	virtual void StartPlay() override;
	// ~ Engine overrides End
};