#pragma once

/**
* Base class of all widgets in the game.
*/

#include "Blueprint/UserWidget.h"
#include "MyWidgetBase.generated.h"

UCLASS()
class UMyWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = Widgets)
	int32 GetNumWidgetsInViewport() const { return NumWidgetsInViewport; }

protected:
	virtual bool Initialize() override;

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	/**
	* Each user widget must implement to unbind all binded delegates.
	* WARNING! Call Super when override.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Delegates, Meta = (AllowPrivateAccess = true))
	void MyUnbindDelegates();

	/**
	* Each user widget must implement to bind necessary delegates.
	* WARNING! Call Super when override.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Delegates, Meta = (AllowPrivateAccess = true))
	void MyBindDelegates();

private:
	/**
	* PrefixString for logging.
	*/
	FString PrefixString;

	/**
	* Count of widgets added to viewport.
	*/
	UPROPERTY()
	int32 NumWidgetsInViewport = 0;
};