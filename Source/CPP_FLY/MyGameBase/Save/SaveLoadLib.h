#pragma once

/**
* SaveGame save/load functions that do NO interfere with UI .
*/

#include "SaveLoadLib.generated.h"

UCLASS()
class USaveLoadLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = SaveLoad)
	static void QuickSave();

	UFUNCTION(BlueprintCallable, Category = SaveLoad)
	static void QuickLoad();
};                                   