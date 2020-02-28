#pragma once

#include "UIControllerEvents.generated.h"

class IUIController;
class UUIControllerEvents;

USTRUCT(BlueprintType)
struct FUIControllerParamsBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Events)
	TScriptInterface<IUIController> Sender;

	FUIControllerParamsBase() = default;
	FUIControllerParamsBase(TScriptInterface<IUIController> InSender) 
	{
		Sender = InSender;
	}
};

USTRUCT(BlueprintType)
struct FUIControllerReadyParams : public FUIControllerParamsBase
{
	GENERATED_BODY()

	FUIControllerReadyParams() = default;
	FUIControllerReadyParams(TScriptInterface<IUIController> InSender) :
		FUIControllerParamsBase(InSender) {}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUIControllerReadySignature, const FUIControllerReadyParams&, InParams);

UCLASS()
class UUIControllerEvents : public UObject
{
	GENERATED_BODY()

public:
	UUIControllerEvents();

	/**
	* Controller is initialized, ant it's state can be used for gameplay.
	* To be called only in the game mode (not in the editor).
	*/ 
	UPROPERTY(BlueprintAssignable, Category = Events)
	FUIControllerReadySignature Ready;
};