#pragma once

#include "Components/ActorComponent.h"
#include "I/ITestController.h"
#include "TestControllerComponentBase.generated.h"

UCLASS()
class UTestControllerComponentBase : 
	public UActorComponent
,	public ITestController
{
	GENERATED_BODY()

public:
	UTestControllerComponentBase();

protected:
	UFUNCTION(BlueprintPure)
	APCBase* GetPCBase() const;

private:
};