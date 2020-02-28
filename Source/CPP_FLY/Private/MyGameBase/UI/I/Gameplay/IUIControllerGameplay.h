#pragma once

/**
* Methods for sending gameplay commands for the gameplay objects.
*/

#include "UObject/Interface.h"
#include "IUIControllerGameplay.generated.h"

class UUIControllerGameplayEvents;

UINTERFACE(BlueprintType)
class UUIControllerGameplay : public UInterface
{
	GENERATED_BODY()

public:
};

class IUIControllerGameplay
{
	GENERATED_BODY()

public:
	// ~Events Begin
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	UUIControllerGameplayEvents* GetEvents() const;
	// ~Events End
};
