#pragma once

#include "UIControllerGameplayEvents.generated.h"

class IUIControllerGameplay;
class UUIControllerGameplayEvents;

USTRUCT(BlueprintType)
struct FUIControllerGameplayParamsBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Events)
	TScriptInterface<IUIControllerGameplay> Sender;

	FUIControllerGameplayParamsBase() = default;
	FUIControllerGameplayParamsBase(TScriptInterface<IUIControllerGameplay> InSender) 
	{
		Sender = InSender;
	}
};

USTRUCT(BlueprintType)
struct FUIControllerGameplay_PlayerPawnReadyParams : public FUIControllerGameplayParamsBase
{
	GENERATED_BODY()

	FUIControllerGameplay_PlayerPawnReadyParams() = default;
	FUIControllerGameplay_PlayerPawnReadyParams(TScriptInterface<IUIControllerGameplay> InSender) :
		FUIControllerGameplayParamsBase(InSender) {}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUIControllerGameplay_PlayerPawnReadySignature, const FUIControllerGameplay_PlayerPawnReadyParams&, InParams);

UCLASS()
class UUIControllerGameplayEvents : public UObject
{
	GENERATED_BODY()

public:
	UUIControllerGameplayEvents();

	/**
	* Player pawn is initialized, and it state can be used
	* (called when a new pawn is possessed).
	*/ 
	UPROPERTY(BlueprintAssignable, Category = Events)
	FUIControllerGameplay_PlayerPawnReadySignature PlayerPawnReady;
};