#pragma once

#include "UIControllerComponentConfigLib.h"
#include "UIControllerComponentDebugConfigLib.h"

/**
* Base class of UI Controller environments.
*
* UI Controller environment contains objects shared between all UI controller subobjects.
*/

#include "UIControllerComponentEnvBase.generated.h"

class UShowMouseStack;
class UInputModeStack;

UCLASS()
class UUIControllerComponentEnvBase : public UObject
{
	GENERATED_BODY()

public:
	UUIControllerComponentEnvBase();

	/**
	* To be called when the Play is started (aka the AActor::BeginPlay).
	*/
	UFUNCTION(BlueprintCallable, Category = Play)
	virtual void MyBeginPlay();

	/**
	* Must be called from the Controller Base to initialize it (never should be called manually from other places).
	*/
	UFUNCTION(BlueprintCallable, Category = Initialization)
	virtual void BindController(UUIControllerComponentBase* InUIControllerComponent);

	UFUNCTION(BlueprintPure)
	UUIControllerComponentBase* GetUIControllerComponentBase() const { return UIControllerComponent; }
	
	UFUNCTION(BlueprintPure)
	APlayerController* GetPC() const;

	UFUNCTION(BlueprintPure, Category = UI)
	UShowMouseStack* GetShowMouseStack() const { return ShowMouseStack; }

	UFUNCTION(BlueprintPure, Category = UI)
	UInputModeStack* GetInputModeStack() const { return InputModeStack; }

	// ~Editable properties getters Begin
	UFUNCTION(BlueprintPure, Category = Params)
	const FUIControllerComponentConfig& GetParams() const;

	UFUNCTION(BlueprintPure, Category = DebugParams)
	const FUIControllerComponentDebugConfig& GetDebugParams() const;
	// ~Editable properties getters End

private:
	UPROPERTY()
	UUIControllerComponentBase* UIControllerComponent = nullptr;

	// ~Input Begin
	void InitializeInput();

	UPROPERTY()
	UShowMouseStack* ShowMouseStack = nullptr;

	UPROPERTY()
	UInputModeStack* InputModeStack = nullptr;
	// ~Input End
};