#pragma once

#include "Templates/SubclassOf.h"
#include "UObject/Interface.h"
#include "IUIControllerMenu.generated.h"

class UUserWidget;

class UUIControllerMenuEvents;

UINTERFACE(BlueprintType)
class UUIControllerMenu : public UInterface
{
	GENERATED_BODY()

public:
};

class IUIControllerMenu
{
	GENERATED_BODY()

public:
	// ~ Widgets Begin
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Events)
	UUIControllerMenuEvents* GetEvents() const;
	// ~ Widgets End

	/**
	* Opens a new menu widget.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Menu)
	void OpenMenu(TSubclassOf<UUserWidget> InWidgetClass);

	/**
	* Returns to the previous menu widget (closes the current widget).
	* If cannot return does nothing.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Menu)
	void Return();

	/**
	* @Returns: true if can return now, otherwise false.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Menu)
	bool CanReturn() const;

	/**
	* Returns to the start widget of the menu.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Menu)
	void ReturnToStart();

	/**
	* @Returns: true if can return to start now, otherwise false.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Menu)
	bool CanReturnToStart() const;
};
