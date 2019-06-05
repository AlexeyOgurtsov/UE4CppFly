#pragma once

/**
* Interface that all pawns moving on the track must implement.
*/

#include "ITrackPawnMovement.generated.h"

UINTERFACE()
class UTrackPawnMovement : public UInterface
{
	GENERATED_BODY()

public:	
};

class ITrackPawnMovement
{
	GENERATED_BODY()

public:
	/**
	* Commands to perform a single strafe horizontally.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void StrafeHorz(float InAmount);

	/**
	* Command to perform a single strafe vertically.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void StrafeVertical(float InAmount);

	/**
	* Command to add a single thrust forward or backward.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Thrust(float InAmount);

	/**
	* Command to perform a single roll.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void RotateRoll(float InAmount);
};
