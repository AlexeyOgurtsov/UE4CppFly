#pragma once

#include "UIControllerComponentDebugConfigLib.generated.h"

USTRUCT(BlueprintType)
struct FUIControllerComponentDebugConfig
{
	GENERATED_BODY()

	// ~Input Begin
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
	bool bEnableInputModeStack = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
	bool bEnableMouseStack = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
	bool bCallSetInputModeManually_IfInputModeStackDisabled = true;

	bool ShouldSetInputModeManually() const
	{
		return ( ! bEnableInputModeStack ) && bCallSetInputModeManually_IfInputModeStackDisabled;
	}
	// ~Input End

	FUIControllerComponentDebugConfig()
	{
	}
};

UCLASS()
class UUIControllerComponentDebugConfigLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
};
