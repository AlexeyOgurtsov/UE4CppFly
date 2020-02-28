#pragma once

#include "UObject/Interface.h"
#include "Engine/EngineTypes.h"
#include "IMyController.generated.h"

/**
* Interface that pawn typically uses to notify its controller (whether it's player controller or ai controller).
*/

UINTERFACE()
class UMyController : public UInterface
{
	GENERATED_BODY()

public:
};

class IMyController
{
	GENERATED_BODY()

public:
	/**
	* Controlled pawn's BeginPlay function is called.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Pawn_BeginPlay();

	/**
	* Controlled pawn's EndPlay function is called.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Pawn_EndPlay(const EEndPlayReason::Type InReason);

	/**
	* Controlled pawn is started to destruct in the gameplay sense.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Pawn_DestructionStarted();

	/**
	* Controlled pawn characteristics updated (hit points, armor state etc.).
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Pawn_CharsUpdated();
};
