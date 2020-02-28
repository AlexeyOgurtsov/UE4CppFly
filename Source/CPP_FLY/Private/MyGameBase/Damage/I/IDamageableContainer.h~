#pragma once

/**
* This class provides access to the IDamageable interface.
* Typically some Actor implements this interface to provide access to the UDamageableComponent.
*/

#include "IDamageableContainer.generated.h"

class IDamageable;

UINTERFACE()
class UDamageableContainer : public UInterface
{
	GENERATED_BODY()
public:
};

class IDamageableContainer
{
	GENERATED_BODY()

public:
	/**
	* Returns IDamageable interface.
	* DO may return nullptr;
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	TScriptInterface<IDamageable> GetDamageable() const;
};