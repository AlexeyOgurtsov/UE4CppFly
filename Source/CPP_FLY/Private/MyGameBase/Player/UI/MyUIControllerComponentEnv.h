#pragma once

/**
* Environment of the UI Controller.
*/

#include "UIControllerComponentEnvBase.h"
#include "MyUIControllerComponentEnv.generated.h"

class APlayerController;

class UMyUIControllerComponent;

UCLASS()
class UMyUIControllerComponentEnv : public UUIControllerComponentEnvBase
{
	GENERATED_BODY()

public:
	UMyUIControllerComponentEnv();

	virtual void BindController(UUIControllerComponentBase* InUIControllerComponent) override;

	UFUNCTION(BlueprintPure, Category = Environment)
	UMyUIControllerComponent* GetUIControllerComponent() const;
};
