#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "UIControllerComponentEnvBaseLib.generated.h"

class UUIControllerComponentEnvBase;

class UUserWidget;

UCLASS()
class UUIControllerComponentEnvBaseLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UUIControllerComponentEnvBaseLib();

	/**
	* Sets the Game Only Input Mode and Turns Off cursor.
	*/
	UFUNCTION(BlueprintCallable, Category = Input)
	static void PushInputAndCursor_GameOnly(UUIControllerComponentEnvBase* Env);

	/**
	* Sets the UI Only Input Mode and Turns On cursor.
	*/
	UFUNCTION(BlueprintCallable, Category = Input)
	static void PushInputAndCursor_UIOnly(UUIControllerComponentEnvBase* Env, UUserWidget* InWidget);

	/**
	* Sets the Game Only Input Mode and Turns On cursor.
	*/
	UFUNCTION(BlueprintCallable, Category = Input)
	static void PushInputAndCursor_GameAndUI(UUIControllerComponentEnvBase* Env, UUserWidget* InWidget);

	/**
	* Restores the Input Mode and cursor.
	*/
	UFUNCTION(BlueprintCallable, Category = Input)
	static void PopInputAndCursor(UUIControllerComponentEnvBase* Env);
};
