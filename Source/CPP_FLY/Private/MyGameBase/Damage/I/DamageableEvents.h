#pragma once

/**
* Contains delegates for the IDamageable interface (as interfaces cannot have delegates).
*/

#include "DamageableEvents.generated.h"

class IDamageable;

// ~ Delegates Begin
USTRUCT(BlueprintType)
struct FDamageableStateChangedParams
{
	GENERATED_BODY()

	/**
	* Sender
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TScriptInterface<IDamageable> Sender;

	/**
	* True, if the given component was damaged fatally
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bFatallyDamaged = false;

	/**
	* True if called inside Activate() with bReset = true
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bFromActivateReset = false;

};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDamageableStateChangedSignature, const FDamageableStateChangedParams&, InParams);
// ~ Delegates End

UCLASS()
class UDamageableEvents : public UObject
{
	GENERATED_BODY()

public:
	UDamageableEvents();

	// ~ Delegates Begin
	UPROPERTY(BlueprintAssignable, Category = Events)
	FDamageableStateChangedSignature StateChanged;
	// ~ Delegates End
};