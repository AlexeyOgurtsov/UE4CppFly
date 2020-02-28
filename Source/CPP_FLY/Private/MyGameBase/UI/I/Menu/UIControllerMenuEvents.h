#pragma once

#include "UIControllerMenuEvents.generated.h"

class IUIControllerMenu;
class UUIControllerMenuEvents;

USTRUCT(BlueprintType)
struct FUIControllerMenuParamsBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Events)
	TScriptInterface<IUIControllerMenu> Sender;

	FUIControllerMenuParamsBase() = default;
	FUIControllerMenuParamsBase(TScriptInterface<IUIControllerMenu> InSender) 
	{
		Sender = InSender;
	}
};

USTRUCT(BlueprintType)
struct FUIControllerMenu_CanReturnChangedParams : public FUIControllerMenuParamsBase
{
	GENERATED_BODY()

	FUIControllerMenu_CanReturnChangedParams() = default;
	FUIControllerMenu_CanReturnChangedParams(TScriptInterface<IUIControllerMenu> InSender) :
		FUIControllerMenuParamsBase(InSender) {}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUIControllerMenu_CanReturnChangedSignature, const FUIControllerMenu_CanReturnChangedParams&, InParams);

UCLASS()
class UUIControllerMenuEvents : public UObject
{
	GENERATED_BODY()

public:
	UUIControllerMenuEvents();

	/**
	* X
	*/ 
	UPROPERTY(BlueprintAssignable, Category = Events)
	FUIControllerMenu_CanReturnChangedSignature CanReturnChanged;
};