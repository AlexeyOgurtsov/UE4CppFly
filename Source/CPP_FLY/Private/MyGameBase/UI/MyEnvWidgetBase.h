#pragma once

/**
* Base class of all widgets that interact with the environment
* (send commands to the UI Controller, get state of pawns etc).
*/

#include "MyWidgetBase.h"
#include "I/UIControllerEvents.h"
#include "MyEnvWidgetBase.generated.h"

class IUIController;

class IUIControllerLevels;
class IUIControllerMenu;
class IUIControllerSaveLoad;

class IDamageable;
class IWeaponInventory;
class ITrackPawnMovement;

UCLASS()
class UMyEnvWidgetBase : public UMyWidgetBase
{
	GENERATED_BODY()

public:
	UMyEnvWidgetBase();

protected:
	// ~System overrides Begin
	/**
	* Called at the widget initialization time.
	*/
	virtual bool Initialize() override;
	
	/**
	* Called when widget is Added to the viewport.
	*/
	virtual void NativeConstruct() override;
	// ~System overrides End

	// ~Helper getters Begin
	/**
	* Interface to the UI controller, that is to be receiving UI commands.
	* All commands to the UI are to be done through this UI controller.
	*/
	UFUNCTION(BlueprintPure, Category = "AccessHelper")
	TScriptInterface<IUIController> GetUIController() const;

	/**
	* Interface to the UI Controller Levels.
	*/
	UFUNCTION(BlueprintPure, Category = "AccessHelper")
	TScriptInterface<IUIControllerLevels> GetControllerLevels() const;

	//UFUNCTION(BlueprintPure, Category = "AccessHelper")
	//UUIControllerLevelsEvents* GetLevelsEvents() const;

	/**
	* Interface to the UI Controller Menu.
	*/
	UFUNCTION(BlueprintPure, Category = "AccessHelper")
	TScriptInterface<IUIControllerMenu> GetControllerMenu() const;

	UFUNCTION(BlueprintPure, Category = "AccessHelper")
	UUIControllerMenuEvents* GetMenuEvents() const;

	/**
	* Interface to the UI Controller SaveLoad.
	*/
	UFUNCTION(BlueprintPure, Category = "AccessHelper")
	TScriptInterface<IUIControllerSaveLoad> GetControllerSaveLoad() const;

	UFUNCTION(BlueprintPure, Category = "AccessHelper")
	UUIControllerSaveLoadEvents* GetSaveLoadEvents() const;

	/**
	* Getting Events object for the UI Controller.
	*/
	UFUNCTION(BlueprintPure, Category = "AccessHelper")
	UUIControllerEvents* GetUIControllerEvents() const;
	// ~Helper getters End

	// ~Helper system Begin
	/**
	* Override this function to register the event helpers.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Framework")
	void RegisterEventHelpers();
	// ~Helper system End

	// ~Helper events Begin
	/**
	* Called when the controller is ready.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AccessHelper")
	void UIControllerReady(const FUIControllerReadyParams& InParams);
	// ~Helper events End
};