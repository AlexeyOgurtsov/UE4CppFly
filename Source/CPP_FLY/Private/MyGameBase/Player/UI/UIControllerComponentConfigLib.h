#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "UIControllerComponentConfigLib.generated.h"

USTRUCT(BlueprintType)
struct FUIControllerComponentConfig
{
	GENERATED_BODY()

	FUIControllerComponentConfig()
	{
	}
};

UCLASS()
class UUIControllerComponentConfigLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
};
