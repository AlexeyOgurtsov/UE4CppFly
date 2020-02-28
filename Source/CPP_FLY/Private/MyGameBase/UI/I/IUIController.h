#pragma once

#include "UObject/Interface.h"
#include "IUIController.generated.h"

class UUserWidget;

class UUIControllerEvents;

class IUIControllerGameplay;
class IUIControllerMenu;
class IUIControllerSaveLoad;
class IUIControllerLevels;

UINTERFACE()
class UUIController : public UInterface 
{
	GENERATED_BODY()

public:
};

class IUIController 
{
	GENERATED_BODY()

public:
	// ~ Events Begin
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	UUIControllerEvents* GetEvents() const;
	// ~ Events End

	// ~Subordinate interfaces Begin
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	TScriptInterface<IUIControllerGameplay> GetGameplay() const;

	/**
	* The main menu.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	TScriptInterface<IUIControllerMenu> GetMenu() const;
	// ~Subordinate interfaces End

	/**
	* The save/load.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	TScriptInterface<IUIControllerSaveLoad> GetSaveLoad() const;

	/**
	* Levels.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	TScriptInterface<IUIControllerLevels> GetLevels() const;

	/**
	* Close current opened UI (Main menu, inventory etc.) immediately.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void CloseCurrentUI(UUserWidget* InSender);
};
