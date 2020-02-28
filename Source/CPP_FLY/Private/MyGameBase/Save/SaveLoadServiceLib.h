#pragma once

/**
* Entry point for working with Save/Load system.
*
* Controls the entire process of loading level's saved games into the world,
* but (!) without interfering with the UI;
*/

#include "Kismet/BlueprintFunctionLibrary.h"
#include "SaveLoadServiceLib.generated.h"

UCLASS()
class USaveLoadServiceLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = SaveLoad)
	static void QuickSave();

	UFUNCTION(BlueprintCallable, Category = SaveLoad)
	static void QuickLoad();
};
