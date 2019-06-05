#pragma once

/**
* Methods for saving and loading the game.
*/

#include "IUIControllerSaveLoad.generated.h"

class UUIControllerSaveLoadEvents;

UINTERFACE(BlueprintType)
class UUIControllerSaveLoad : public UInterface
{
	GENERATED_BODY()

public:
};

class IUIControllerSaveLoad
{
	GENERATED_BODY()

public:
	// ~Events Begin
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	UUIControllerSaveLoadEvents* GetEvents() const;
	// ~Events End

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = SaveLoad)
	void QuickSave();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = SaveLoad)
	void QuickLoad();
};