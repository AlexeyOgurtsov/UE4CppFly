#pragma once

#include "TestControllerComponentBase.h"
#include "ActorTestComponentBase.generated.h"

class AActor;

UCLASS()
class UActorTestComponentBase : public UTestControllerComponentBase
{
	GENERATED_BODY()

public:
	UActorTestComponentBase();

protected:
	/**
	* Actor to work with.
	*/
	UFUNCTION(BlueprintPure)
	AActor* GetMyActor() const;

	/**
	* Tag to find the actor by.
	*/
	UFUNCTION(BlueprintPure)
	FName GetMyActorTag() const;

private:
	UPROPERTY(EditDefaultsOnly)
	FName MyActorTag;
};