#include "MyGameModeBase.h"
#include "MyEngine/MyEngineHelperLib.h"

#include "MyGame/GameMode/MyGameState.h"
#include "MyGame/Pawn/MyPlayerPawn.h"
#include "MyGame/Player/PC.h"
#include "MyGame/Player/MyPlayerState.h"

AMyGameModeBase::AMyGameModeBase()
{
	bPauseable = true;

	DefaultPawnClass = AMyPlayerPawn::StaticClass();
	PlayerControllerClass = APC::StaticClass();
	GameStateClass = AMyGameState::StaticClass();
	PlayerStateClass = AMyPlayerState::StaticClass();
	// @TODO: GameSession
}

void AMyGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}

void AMyGameModeBase::InitGameState()
{
	Super::InitGameState();
}

bool AMyGameModeBase::ShouldStartInCinematicMode
(
	APlayerController* Player,
	bool& OutHidePlayer,
	bool& OutHideHud,
	bool& OutDisableMovement,
	bool& OutDIsableTurning 
)
{
	return Super::ShouldStartInCinematicMode(Player, OutHidePlayer, OutHideHud, OutDisableMovement, OutDIsableTurning);
}

void AMyGameModeBase::StartPlay()
{
	Super::StartPlay();
}