#include "MyUIControllerGameplay.h"
#include "MyGameBase/UI/I/Gameplay/UIControllerGameplayEvents.h"
#include "MyGameBase/Player/UI/MyUIControllerComponentEnv.h"
#include "MyGameBase/Player/UI/MyUIControllerComponent.h"

UMyUIControllerGameplay::UMyUIControllerGameplay()
{
	Events = CreateDefaultSubobject<UUIControllerGameplayEvents>(TEXT("Events"));
}

UMyUIControllerGameplay* UMyUIControllerGameplay::CreateInitializedDefaultSubobject
(
	const FName& InName, 
	const FMyUIControllerGameplayInitializer& InInitializer
)
{
	check(InInitializer.Env);

	UMyUIControllerGameplay* Obj = InInitializer.Env->GetUIControllerComponent()->CreateDefaultSubobject<UMyUIControllerGameplay>(InName);
	Obj->Env = InInitializer.Env;
	return Obj;
}

UMyUIControllerGameplay* UMyUIControllerGameplay::NewInitializedObject
(
	const FName& InName, 
	const FMyUIControllerGameplayInitializer& InInitializer
)
{
	check(InInitializer.Env);

	UMyUIControllerGameplay* Obj = NewObject<UMyUIControllerGameplay>(InInitializer.Env->GetUIControllerComponent(), UMyUIControllerGameplay::StaticClass(), InName);
	Obj->Env = InInitializer.Env;
	return Obj;
}

UUIControllerGameplayEvents* UMyUIControllerGameplay::GetEvents_Implementation() const
{
	return Events;
}

void UMyUIControllerGameplay::PlayerPawn_Ready()
{
	Events->PlayerPawnReady.Broadcast(FUIControllerGameplay_PlayerPawnReadyParams{this});
}