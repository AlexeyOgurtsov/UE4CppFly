#pragma once

/**
* Interface that PC uses to interact with the UI Controller component.
*/

#include "IUIControllerComponent.generated.h"

class APlayerController;

UINTERFACE()
class UUIControllerComponent : public UInterface
{
	GENERATED_BODY()
public:
};

class IUIControllerComponent
{
	GENERATED_BODY()

public:
	// ~Player constroller notifications Begin
	/**
	* When the player controller state is fully initialized, and ready to be reflected by the UI.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void PlayerPawnReady();
	// ~Player constroller notifications End

	// ~Commands Begin
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ToggleMenu();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ToggleDebugMenu();
	// ~Commands End
};